#include "EventAction.h"
#include "Perform.h"



MoveAction::MoveAction()
{
	type = move;
}
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
