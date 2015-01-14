#include "Perform.h"

#define NPC_ACTIVATE_DISTANCE_X 30
#define NPC_ACTIVATE_DISTANCE_Y 50

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
		stage->putInCharacter(mainCharacter->character);
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
	}
		
	if (mainCharacter->isMoving)
	{
		
		mainCharacter->moveToDirectionBy(mainCharacter->movingDirection, STEP_DISTANCE);
	}
	
}
void Perform::stopMovingMainCharacter(Character_Direction direction)
{
	if (direction == mainCharacter->movingDirection)
		stopMovingMainCharacter();
}
void Perform::stopMovingMainCharacter()
{
	mainCharacter->isMoving = false;
	mainCharacter->stopMoving();
}

void Perform::onArrowButtonPressed(Character_Direction direction)
{
	if (operationStatus == freeMoving)
	{
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
	int x = currentPosition.x;
	int y = currentPosition.y;


	Size mapSize = stage->getContentSize();
	if (((direction == left) && x<45) ||
		((direction == right) && x>mapSize.width - 45) ||
		((direction == down) && y<45) ||
		((direction == up) && y>mapSize.height - 45))
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

	return stage->isPositionBlocked(nextPosition);
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
void Perform::updateNPCPositionList()
{
	std::list<Character*>::iterator i;
	for (i = NPCList.begin(); i != NPCList.end(); i++)
	{
		Character* tempCharacter = *i;
		NPCPositionList.push_back(tempCharacter->getPosition());
	}
}
std::list<Point> Perform::getNPCPositionList()
{
	return NPCPositionList;
}