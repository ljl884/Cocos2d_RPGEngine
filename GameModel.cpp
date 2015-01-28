#include "GameModel.h"

GameModel* GameModel::instance = NULL;

int GameModel::getSection()
{
	return gameSection;
}