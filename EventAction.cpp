#include "EventAction.h"


MoveAction::MoveAction()
{
	type = move;
}
DialogAction::DialogAction(std::string text)
{
	type = dialog;
	if (text != "")
	{
		std::vector<std::string> strings;
	}
}
BattleAction::BattleAction()
{
	type = battle;
}
SceneAction::SceneAction()
{
	type = changescene;
}