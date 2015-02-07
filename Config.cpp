#include "Config.h"

int Config::NPC_ACTIVATE_DISTANCE_X = 30;
int Config::NPC_ACTIVATE_DISTANCE_Y = 50;
int Config::NPC_COLLISION_HIGHT = 40;
int Config::NPC_COLLISION_WIDTH = 20;

int Config::STEP_DISTANCE = 15;
float Config::MOVING_SPEED = 400;

int Config::MAP_SCROLL_DISTANCE = 100;
int Config::MAP_SCROLL_STEP = 300;
int Config::MAP_EDGE = 15;
int Config::MAX_MOVING_DISTANCE = 50;
float Config::SCROLLING_SPEED = 300;

float Config::SWITCH_SCENE_TIME = 0.5;

std::string Config::MAP_PATH = "map/";
std::string Config::NPC_PATH = "npc/";
std::string Config::EVENT_PATH = "event/";
std::string Config::BATTLE_RESOURCE = "Battle/";
std::string Config::NPC_SCRIPT = "xml\\NPC.xml";
std::string Config::MAP_SCRIPT = "xml\\MAP.xml";
std::string Config::SCENE_SCRIPT = "xml\\SCENE.xml";
std::string Config::EVENT_SCRIPT = "xml\\EVENT.xml";


std::string Config::PROPERTIE_BLOCKED = "Blocked";
std::string Config::PROPERTIE_BRIDGE = "SceneId";
std::string Config::PROPERTIE_POSITION = "Position";
std::string Config::PROPERTIE_EVENT_NAME = "Event";
std::string Config::BACKGROUND_LAYER = "Layer1";
std::string Config::BLOCK_LAYER = "Block";
std::string Config::BRIDGE_LAYER = "Bridge";
std::string Config::EVENT_LAYER = "Event";
std::string Config::POSITION_LAYER = "Hero";
std::string Config::PROPERTIE_TRUE = "True";

int Config::DIALOG_FONT_SIZE = 30;
std::string Config::DIALOG_FONT= "fonts/STXINWEI.ttf";
std::string Config::DIALOG_BAR_URL = "dialogbar.png";


void Config::loadFromFile(std::string filename)
{
}