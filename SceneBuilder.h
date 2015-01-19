#ifndef _SCENE_BUILDER_
#define _SCENE_BUILDER_

#include "cocos2d.h"


using namespace cocos2d;

class SceneBuilder
{
public:
	SceneBuilder();

	static Scene* BuildScene(std::string sceneId);
	

private:
	
};
#endif