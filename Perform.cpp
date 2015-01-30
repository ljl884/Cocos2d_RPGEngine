#include "Perform.h"
#include "Config.h"

//#define NPC_ACTIVATE_DISTANCE_X 30
//#define NPC_ACTIVATE_DISTANCE_Y 50
//#define MAP_SCROLL_DISTANCE 100
//#define MAP_SCROLL_STEP 300
//#define MAP_EDGE 15
//#define SWITCH_SCENE_TIME 0.5

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
				if (remainingDistanceToMapEdge > Config::MAP_SCROLL_STEP)
					scrollDistance = Config::MAP_SCROLL_STEP;
			else
				scrollDistance = remainingDistanceToMapEdge;
			stage->isScrolling = true;
			stage->scrollToDirectionBy(CharacterDirectionToDirection(mainCharacter->movingDirection), scrollDistance);
		}
		else
			mainCharacter->moveToDirectionBy(mainCharacter->movingDirection, Config::STEP_DISTANCE);
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
		{
			//if the dialog was an action, call the information center to run next action in the queue
			if (dialog->getActionFlag() == true)
			{
				dialog->setActionFlag(false);
				bool actionPlayed = InformationCenter::getInstance()->playAction();
				
				//if there is no actions in the queue, set the status to free moving.
				if (actionPlayed == false)
					operationStatus = freeMoving;
			}
			
			//if the dialog was not an action, set the status to free moving.
			else
				operationStatus = freeMoving;
		}
			
			
		break;
	default:
		break;
	}
}

bool Perform::isNextPositionBlocked(Character_Direction direction)
{
	//get main characters position
	Point nextPosition;
	Point currentPosition;
	currentPosition = mainCharacter->getPosition();
	int x = currentPosition.x;
	int y = currentPosition.y;

	//if is reaching the edge of the map return true
	Size mapSize = stage->getContentSize();
	if (((direction == left) && x<Config::MAP_EDGE) ||
		((direction == right) && x>mapSize.width - Config::MAP_EDGE) ||
		((direction == down) && y<Config::MAP_EDGE) ||
		((direction == up) && y>mapSize.height - Config::MAP_EDGE))
		return true;
	if (NULL == stage)
		return false;


	// set the position of the destination
	switch (direction)
	{
	case up:
		nextPosition = ccp(x, y + Config::STEP_DISTANCE);
		break;
	case down:
		nextPosition = ccp(x, y - Config::STEP_DISTANCE);
		break;
	case left:
		nextPosition = ccp(x - Config::STEP_DISTANCE, y);
		break;
	case right:
		nextPosition = ccp(x + Config::STEP_DISTANCE, y);
		break;
	default:
		break;
	}
	//if is reaching a event tile, get the event information and judge if the event should displayed
	std::string eventName = "";
	if (stage->getPositionEventInfo(nextPosition,eventName))
	{
		if (eventName != "")
		{
			XMLParser *parser = XMLParser::getInstance();
			XMLEvent *event = parser->getEventInfo(eventName);
			addEvent(event);
			return true;
		}
	
	}

	//if is reaching a scene bridge tile, get  the bridge information from stage class and replace the current scene.
	std::string sceneId = "", mcPosition = "";

	if (stage->getPositionBridgeInfo(nextPosition,sceneId,mcPosition))
	{
		auto scene = SceneBuilder::BuildScene(sceneId,mcPosition);
		Director::getInstance()->replaceScene(CCTransitionFade::create(Config::SWITCH_SCENE_TIME, scene));
		return true;
	}

	//call stage to judge if is reaching the blocked area
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
		if (position.y > visibleSize.height - Config::MAP_SCROLL_DISTANCE && (0.5*mapSize.height + y - 0.5*visibleSize.height)>Config::STEP_DISTANCE)
			return true;
		break;
	case down:
		if (position.y < Config::MAP_SCROLL_DISTANCE && (0.5*mapSize.height - y - 0.5*visibleSize.height)>Config::STEP_DISTANCE)
			return true;
		break;
	case left:
		if (position.x < Config::MAP_SCROLL_DISTANCE && (0.5*mapSize.width - x - 0.5*visibleSize.width)>Config::STEP_DISTANCE)
			return true;
		break;
	case right:
		if (position.x > visibleSize.width - Config::MAP_SCROLL_DISTANCE && (0.5*mapSize.width + x - 0.5*visibleSize.width)>Config::STEP_DISTANCE)
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
		destination = ccp(position.x, position.y + Config::STEP_DISTANCE);
		newFacingDirection = down;
		break;
	case down:
		destination = ccp(position.x, position.y - Config::STEP_DISTANCE);
		newFacingDirection = up;
		break;
	case left:
		destination = ccp(position.x - Config::STEP_DISTANCE, position.y);
		newFacingDirection = right;
		break;
	case right:
		destination = ccp(position.x + Config::STEP_DISTANCE, position.y + Config::STEP_DISTANCE);
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
			if (fabs(NPCPosition.x - destination.x) < Config::NPC_ACTIVATE_DISTANCE_X && fabs(NPCPosition.y - destination.y) < Config::NPC_ACTIVATE_DISTANCE_Y)
			{
				tempCharacter->changeFacingDirection(newFacingDirection);
				//dialog->display(tempCharacter->getWords());
				operationStatus = DisplayingDialog; 
				mainCharacter->stopMoving();
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
Operation_Status Perform::getOperationStatus()
{
	return operationStatus;
}
void Perform::addEvent(XMLEvent* eventToPlay)
{
	EventAction *action;
	while (!eventToPlay->actions.empty())
	{
		action = eventToPlay->actions.front();
		eventToPlay->actions.pop();
		//action->playEvent(this);
		this->actionQueue.push(action);
		
	}
	InformationCenter *informationCenter = InformationCenter::getInstance();
	informationCenter->playAction();
}
bool Perform::playAction()
{
	if (actionQueue.empty())
		return false;
	else
	{
		actionQueue.front()->playEvent(this);
		actionQueue.pop();
		return true;
	}
}
void Perform::playDialog(std::string text)
{
	operationStatus = DisplayingDialog;
	dialog->display(text);
}
void Perform::playDialog(std::string text, bool isAction)
{
	dialog->setActionFlag(isAction);
	playDialog(text);
}