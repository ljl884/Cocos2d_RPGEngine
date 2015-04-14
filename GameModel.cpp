/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include "GameModel.h"

GameModel* GameModel::instance = NULL;

int GameModel::getSection()
{
	return gameSection;
}