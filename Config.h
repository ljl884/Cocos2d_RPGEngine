/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _CONFIG_
#define _CONFIG_
#include "cocos2d.h"

using namespace cocos2d;

class Config
{
public:
	static void loadFromFile(std::string filename);
	static int NPC_ACTIVATE_DISTANCE_X; 
	static int NPC_ACTIVATE_DISTANCE_Y; 
	static int MAP_SCROLL_DISTANCE;
	static int MAP_SCROLL_STEP;
	static int MAP_EDGE;
	static float SWITCH_SCENE_TIME;
	static int STEP_DISTANCE;
	static float MOVING_SPEED;
	static int MAX_MOVING_DISTANCE;
	static float SCROLLING_SPEED;
	static int NPC_COLLISION_HIGHT;
	static int NPC_COLLISION_WIDTH;
	static std::string MAP_PATH;
	static std::string NPC_PATH;
	static std::string EVENT_PATH;
	static std::string BATTLE_RESOURCE;
	static std::string NPC_SCRIPT;
	static std::string MAP_SCRIPT;
	static std::string SCENE_SCRIPT;
	static std::string EVENT_SCRIPT;
	static std::string PROPERTIE_BLOCKED;
	static std::string PROPERTIE_BRIDGE;
	static std::string PROPERTIE_POSITION;
	static std::string PROPERTIE_EVENT_NAME;
	static std::string BACKGROUND_LAYER;
	static std::string BLOCK_LAYER;
	static std::string BRIDGE_LAYER;
	static std::string EVENT_LAYER;
	static std::string POSITION_LAYER;
	static std::string PROPERTIE_TRUE;
	static int DIALOG_FONT_SIZE;
	static std::string DIALOG_FONT;
	static std::string DIALOG_BAR_URL;


};

#endif

