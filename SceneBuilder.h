/************************************************
Author: Wentao Li
Date:14-4-2015
Description: SceneBuilder binds all related components
togeter and create a scene
*************************************************/
#ifndef _SCENE_BUILDER_
#define _SCENE_BUILDER_

#include "cocos2d.h"
#include "BattleScene.h"

using namespace cocos2d;

class SceneBuilder
{
public:
	SceneBuilder();

	static Scene* BuildScene(std::string sceneId);
	static Scene* BuildScene(std::string sceneId, std::string mainCharacterPosition);
	static Scene* BuildBattleScene();

private:
	
};
#endif