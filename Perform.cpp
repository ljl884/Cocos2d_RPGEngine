#include "Perform.h"

void Perform::setMainCharacter(Character *_mainCharacter)
{
	mainCharacter = _mainCharacter;
}

void Perform::setStage(Stage *_stage)
{
	stage = _stage;
}
void Perform::initializeMainCharacter(std::string filename)
{
	mainCharacter = new Character(filename);
}
void Perform::putinCharacter(Node *node, CCPoint position, Character *character)
{
	character->setPosition(position);
	node->addChild(character->character);
	NPCList.push_back(character);
}
void Perform::putinMainCharacter(Node *node, CCPoint position)
{
	if (NULL != mainCharacter){
		mainCharacter->setPosition(position);
		node->addChild(mainCharacter->character);
	}
	
}
void Perform::onMovingCallback()
{
	CCLOG("action  end!!!!!");

}
void Perform::startMovingMainCharacter(Character_Direction direction)
{
	mainCharacter->stopMoving();
	mainCharacter->changeFacingDirection(direction);
	Point nextPosition;
	Point currentPosition;
	mainCharacter->setStage(stage);
	mainCharacter->isMoving = true;
	mainCharacter->movingDirection = direction;
	mainCharacter->playMovingAnimation(direction);
	mainCharacter->moveoverCallBack();	
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

void Perform::activate()
{


}