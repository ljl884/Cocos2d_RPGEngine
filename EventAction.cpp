#include "EventAction.h"
#include "Perform.h"


//Move
MoveAction::MoveAction()
{
	type = move;
}
void MoveAction::playEvent(Perform *perform)
{
	
	Character_Direction Cdirection;
	if (direction == "down")
		Cdirection = down;
	else if (direction == "up")
		Cdirection = up;
	else if (direction == "left")
		Cdirection = left;
	else if (direction == "right")
		Cdirection = right;

	if (targetName == "Main")
	{
		perform->stopMovingMainCharacter();
		perform->moveMainCharacter(Cdirection, this->distance);
	}
}

//Dialog
DialogAction::DialogAction(std::string text)
{
	type = play_dialog;
	if (text != "")
		dialogText = text;
}
void DialogAction::playEvent(Perform *perform)
{
	perform->playDialog(this->dialogText, true);
}

//Battle
BattleAction::BattleAction()
{
	type = battle;
}
SceneAction::SceneAction(std::string sceneName)
{
	type = change_scene;
	this->sceneName = sceneName;
}
void SceneAction::playEvent(Perform *perform)
{
	auto scene = SceneBuilder::BuildScene(sceneName);
	Director::getInstance()->replaceScene(CCTransitionFade::create(Config::SWITCH_SCENE_TIME, scene));
}
