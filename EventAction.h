#ifndef _EVENT_ACTION_
#define _EVENT_ACTION_

#include "cocos2d.h"
using namespace cocos2d;
enum Action_Type{
	move = 1,
	dialog = 2,
	battle = 3,
	changescene = 4
};
class EventAction
{
public:
	Action_Type type;
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
};
class BattleAction :public EventAction
{
public:
	BattleAction();
};
class SceneAction:public EventAction
{
public:SceneAction();
};

#endif