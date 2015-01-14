#ifndef _PERFROM_
#define _PERFROM_

#include "cocos2d.h"
#include "Stage.h"
#include "Character.h"
#include "Dialog.h"

using namespace cocos2d;

enum Operation_Status
{
	freeMoving = 1,
	DisplayingDialog = 2,
	playingVideo =3
};

class Perform: public Layer
{

public:
	void setMainCharacter(Character *mainCharacter);
	void setStage(Stage *_stage);
	void setDialog(Dialog *dialog);
	void startMovingMainCharacter(Character_Direction direction);
	void stopMovingMainCharacter();
	void stopMovingMainCharacter(Character_Direction direction);
	void initializeMainCharacter(std::string filename);
	void putinMainCharacter(Node *node, Point position);
	void putinCharacter(Node *node, Point position, Character *character);
	void onMovingCallback();
	void activate();
	void onActionButtonPressed();
	void onArrowButtonPressed(Character_Direction direction);
	void onArrowButtonReleased(Character_Direction direction);
	std::list<Point> getNPCPositionList();
protected:
	Stage *stage;
	Dialog *dialog;
	Character *mainCharacter;
	std::list<Character*> NPCList;
	std::list<Point> NPCPositionList;
	void updateNPCPositionList();
	bool isNextPositionBlocked(Character_Direction direction);
	Operation_Status operationStatus = freeMoving;


};

#endif//_PERFROM_