#include "Perform.h"

#define NPC_ACTIVATE_DISTANCE_X 30
#define NPC_ACTIVATE_DISTANCE_Y 50
#define MAP_SCROLL_DISTANCE 100
#define MAP_SCROLL_STEP 300
#define MAP_EDGE 15
#define SWITCH_SCENE_TIME 0.5

void Perform::setMainCharacter(Character *_mainCharacter)
{
	mainCharacter = _mainCharacter;
}

void Perform::setStage(Stage *_stage)
{
	stage = _stage;
}

void Perform::setDialog(Dialog *_dialog)
{
	dialog = _dialog;
}


void Perform::initializeMainCharacter(std::string filename)
{
	mainCharacter = new Character(filename);
}
void Perform::putinCharacter(Node *node, Point position, Character *character)
{
	character->setPosition(position);
	//node->addChild(character->character);
	stage->putInCharacter(character->character);
	
	NPCList.push_back(character);
	updateNPCPositionList();
	if (stage != NULL)
	{
		
		stage->setUnavailablePositions(&NPCPositionList);
	}
		
}
void Perform::putinMainCharacter(Node *node, Point position)
{
	if (NULL != mainCharacter){
		mainCharacter->setPosition(position);
		//node->addChild(mainCharacter->character);
		stage->putInMainCharacter(mainCharacter->character);
	}
	
}
void Perform::onMovingCallback()
{
	//CCLOG("action  end!!!!!");
	startMovingMainCharacter(mainCharacter->movingDirection);
}
void Perform::startMovingMainCharacter(Character_Direction direction)
{
	
	Point nextPosition;
	Point currentPosition;
	mainCharacter->isMoving = true;
	mainCharacter->movingDirection = direction;
	
	if (isNextPositionBlocked(mainCharacter->movingDirection))
	{
		mainCharacter->isMoving = false;
		mainCharacter->stopMoving();
		stage->stopScrolling();
	}
		
	if (mainCharacter->isMoving)
	{
		if (mapShouldScroll(mainCharacter->movingDirection))
		{
			int scrollDistance;
			int remainingDistanceToMapEdge = this->remainingDistanceToMapEdge(mainCharacter->movingDirection);
				if (remainingDistanceToMapEdge > MAP_SCROLL_STEP)
				scrollDistance = MAP_SCROLL_STEP;
			else
				scrollDistance = remainingDistanceToMapEdge;
			stage->isScrolling = true;
			stage->scrollToDirectionBy(CharacterDirectionToDirection(mainCharacter->movingDirection), scrollDistance);
		}
		else
		mainCharacter->moveToDirectionBy(mainCharacter->movingDirection, STEP_DISTANCE);
	}
	
}

Direction Perform::CharacterDirectionToDirection(Character_Direction cd)
{
	Direction direction;
	switch (cd)
	{
	case up:
		direction = UP;
		break;
	case down:
		direction = DOWN;
		break;
	case left:
		direction = LEFT;
		break;
	case right:
		direction = RIGHT;
		break;
	default:
		break;
	}
	return direction;
}
void Perform::stopMovingMainCharacter(Character_Direction direction)
{
	if (direction == mainCharacter->movingDirection)
		stopMovingMainCharacter();
}
void Perform::stopMovingMainCharacter()
{
	mainCharacter->isMoving = false;
	stage->isScrolling = false;
	mainCharacter->stopMoving();
	stage->stopScrolling();
}

void Perform::onArrowButtonPressed(Character_Direction direction)
{
	if (operationStatus == freeMoving)
	{
		stage->stopScrolling();
		mainCharacter->stopMoving();
		mainCharacter->changeFacingDirection(direction);
		mainCharacter->playMovingAnimation(direction);
		startMovingMainCharacter(direction);
	}
		
}
void Perform::onArrowButtonReleased(Character_Direction direction)
{
	if (operationStatus == freeMoving)
		stopMovingMainCharacter(direction);
}
void Perform::onActionButtonPressed()
{
	bool dialogEnded;
	switch (operationStatus)
	{
	case freeMoving:
		activate();
		break;
	case DisplayingDialog:
		dialogEnded = dialog->nextPage();
		if (dialogEnded)
			operationStatus = freeMoving;
		break;
	default:
		break;
	}
}

bool Perform::isNextPositionBlocked(Character_Direction direction)
{
	Point nextPosition;
	Point currentPosition;
	currentPosition = mainCharacter->getPosition();
//	currentPosition = stage->convertToNodeSpace(mainCharacter->getPosition());
	int x = currentPosition.x;
	int y = currentPosition.y;


	Size mapSize = stage->getContentSize();
	if (((direction == left) && x<MAP_EDGE) ||
		((direction == right) && x>mapSize.width - MAP_EDGE) ||
		((direction == down) && y<MAP_EDGE) ||
		((direction == up) && y>mapSize.height - MAP_EDGE))
		return true;
	if (NULL == stage)
		return false;
	switch (direction)
	{
	case up:
		nextPosition = ccp(x, y + STEP_DISTANCE);
		break;
	case down:
		nextPosition = ccp(x, y - STEP_DISTANCE);
		break;
	case left:
		nextPosition = ccp(x - STEP_DISTANCE, y);
		break;
	case right:
		nextPosition = ccp(x + STEP_DISTANCE, y);
		break;
	default:
		break;
	}
	std::string sceneId = "", mcPosition = "";
	if (stage->getPositionBridgeInfo(nextPosition,sceneId,mcPosition))
	{
		auto scene = SceneBuilder::BuildScene(sceneId,mcPosition);
		Director::getInstance()->replaceScene(CCTransitionFade::create(SWITCH_SCENE_TIME, scene));
		return true;
	}
	return stage->isPositionBlocked(nextPosition);
}
void Perform::setCameraPosition(Point position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size mapSize = stage->getContentSize();
	Point mapPostion = stage->getPosition();
	int y = 0.5*mapSize.height-position.y;
	int x = 0.5*mapSize.width-position.x;
	if (position.x <= visibleSize.width)
		x = 0.5*mapSize.width - 0.5*visibleSize.width;
	if (position.y <= visibleSize.height)
		y = 0.5*mapSize.height - 0.5*visibleSize.height;
	if (position.x + 0.5*visibleSize.width>=mapSize.width)
		x = 0.5*visibleSize.width - 0.5*mapSize.width;
	if (position.y + 0.5*visibleSize.height >= mapSize.height)
		y = 0.5*visibleSize.height - 0.5*mapSize.height;

	stage->setPosition(ccp(x, y));


}
bool Perform::mapShouldScroll(Character_Direction direction)
{
	Point position = mainCharacter->character->convertToWorldSpace(ccp(0,0));//main character's world position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size mapSize = stage->getContentSize();
	Point mapPostion = stage->getPosition();
	int y = mapPostion.y;
	int x = mapPostion.x;
	
	switch (direction)
	{
	case up:
		if (position.y > visibleSize.height - MAP_SCROLL_DISTANCE && (0.5*mapSize.height + y - 0.5*visibleSize.height)>STEP_DISTANCE)
			return true;
		break;
	case down:
		if (position.y < MAP_SCROLL_DISTANCE && (0.5*mapSize.height-y-0.5*visibleSize.height)>STEP_DISTANCE)
			return true;
		break;
	case left:
		if (position.x < MAP_SCROLL_DISTANCE && (0.5*mapSize.width -x -0.5*visibleSize.width)>STEP_DISTANCE)
			return true;
		break;
	case right:
		if (position.x > visibleSize.width - MAP_SCROLL_DISTANCE && (0.5*mapSize.width + x - 0.5*visibleSize.width)>STEP_DISTANCE)
			return true;
		break;
	default:
		break;
	}
	return false;
}
int Perform::remainingDistanceToMapEdge(Character_Direction direction)
{
	Point position = mainCharacter->character->convertToWorldSpace(ccp(0, 0));//main character's world position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size mapSize = stage->getContentSize();
	Point mapPostion = stage->getPosition();
	int y = mapPostion.y;
	int x = mapPostion.x;

	switch (direction)
	{
	case up:
		return  (0.5*mapSize.height + y - 0.5*visibleSize.height);
		break;
	case down:
		return (0.5*mapSize.height - y - 0.5*visibleSize.height);
		break;
	case left:
		return (0.5*mapSize.width - x - 0.5*visibleSize.width);
		break;
	case right:
		return (0.5*mapSize.width + x - 0.5*visibleSize.width);
		break;
	default:
		return -1;
		break;
	}
}
void Perform::activate()
{
	if (mainCharacter == NULL)
		return;
	Point position = mainCharacter->getPosition();
	Point destination;
	Character_Direction newFacingDirection;
	switch (mainCharacter->facingDirection)
	{
	case up:
		destination = ccp(position.x, position.y + STEP_DISTANCE);
		newFacingDirection = down;
		break;
	case down:
		destination = ccp(position.x, position.y - STEP_DISTANCE);
		newFacingDirection = up;
		break;
	case left:
		destination = ccp(position.x - STEP_DISTANCE, position.y);
		newFacingDirection = right;
		break;
	case right:
		destination = ccp(position.x + STEP_DISTANCE, position.y + STEP_DISTANCE);
		newFacingDirection = left;
		break;
	}
	if (!NPCList.empty())
	{
		std::list<Character*>::iterator i;
		for (i = NPCList.begin(); i != NPCList.end(); i++)
		{
			Character* tempCharacter = *i;
			Point NPCPosition = tempCharacter->getPosition();
			if (fabs(NPCPosition.x - destination.x) < NPC_ACTIVATE_DISTANCE_X && fabs(NPCPosition.y - destination.y) < NPC_ACTIVATE_DISTANCE_Y)
			{
				tempCharacter->changeFacingDirection(newFacingDirection);
				//dialog->display(tempCharacter->getWords());
				operationStatus = DisplayingDialog;
				std::list<std::string> list;
				list.push_back("HAHAHAHAHAAHAHA");
				list.push_back("Who cares?");
				list.push_back("This is just for testing");

				dialog->display(list);

				return;
			}
		}
	}

}
void Perform::updateNPCPositionList()
{
	if (!NPCList.empty())
	{
		std::list<Character*>::iterator i;
		for (i = NPCList.begin(); i != NPCList.end(); i++)
		{
			Character* tempCharacter = *i;
			NPCPositionList.push_back(tempCharacter->getPosition());
		}
	}
}
std::list<Point> Perform::getNPCPositionList()
{
	return NPCPositionList;
}

void Perform::setOperationStatus(Operation_Status status)
{
	operationStatus = status;
}
