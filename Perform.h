/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _PERFROM_
#define _PERFROM_

#include "cocos2d.h"
#include "Stage.h"
#include "Character.h"
#include "Dialog.h"
#include "SceneBuilder.h"
#include "XMLParser.h"

using namespace cocos2d;

enum Operation_Status
{
	freeMoving = 1,
	DisplayingDialog = 2,
	playingVideo =3,
	NoMainCharacter =4
};

class Perform: public Layer
{

public:
	void setMainCharacter(Character *mainCharacter);
	void setStage(Stage *_stage);
	void setDialog(Dialog *dialog);
	void moveMainCharacter(Character_Direction direction, int distance);
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
	void setOperationStatus(Operation_Status status);
	Operation_Status getOperationStatus();
	void setCameraPosition(Point position);
	void addEvent(XMLEvent* eventToPlay);
	bool playAction();
	void playDialog(std::string text);
	void playDialog(std::string text, bool isAction);
	Direction CharacterDirectionToDirection(Character_Direction cd);
	std::list<Point> getNPCPositionList();
protected:
	Stage *stage;
	Dialog *dialog;
	Character *mainCharacter;
	std::list<Character*> NPCList;
	std::list<Point> NPCPositionList;
	void updateNPCPositionList();
	bool isNextPositionBlocked(Character_Direction direction);
	bool mapShouldScroll(Character_Direction direction);
	int remainingDistanceToMapEdge(Character_Direction direction);
	Operation_Status operationStatus;
	std::queue<EventAction*> actionQueue;


};

#endif//_PERFROM_