#ifndef _EVENT_ACTION_
#define _EVENT_ACTION_

#include "cocos2d.h"

class Perform;
using namespace cocos2d;
enum Action_Type{
	move = 1,
	play_dialog = 2,
	battle = 3,
	change_scene = 4
};
class EventAction
{
public:
	Action_Type type;
	virtual void playEvent(Perform *perform){};
};

class MoveAction : public EventAction
{
public:
	MoveAction();
};
class DialogAction :public EventAction
{
public:
	DialogAction(std::string text);
	std::string dialogText;
	virtual void playEvent(Perform *perform);
};
class BattleAction :public EventAction
{
public:
	BattleAction();
};
class SceneAction:public EventAction
{
public:
	SceneAction(std::string sceneName);
	virtual void playEvent(Perform *perform);
private:
	std::string sceneName;
};

#endif