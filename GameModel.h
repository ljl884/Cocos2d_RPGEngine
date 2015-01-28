#ifndef _GAME_MODEL_
#define _GAME_MODEL_

#include "cocos2d.h"
class GameModel
{
private:
	int gameSection;
	GameModel()
	{
		gameSection = 0;
	}
	static GameModel* instance;
public:
	static GameModel* getInstance()
	{
		if (instance == NULL)
		{
			instance = new GameModel();
		}
		return instance;
	}
	int getSection();


};
#endif