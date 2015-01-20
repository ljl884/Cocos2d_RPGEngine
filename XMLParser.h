#ifndef _XML_PARSER_
#define _XML_PARSER_

#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"


using namespace cocos2d;

enum ScriptType
{
	npc = 0,
	map = 1,
	scene = 2
};

class XMLParser
{
public:
	XMLParser();
	 Sprite*  initializeCharacter(std::string npcName);
	 std::string getNPCImageUrl(std::string npcName);
	 bool getMapDetail(std::string mapName, std::string &imgUrl, std::string &tmxUrl);
private:
	std::string NPCScriptUrl;
	tinyxml2::XMLElement *findNodeByName(std::string name, ScriptType type);
	std::string xmlFilePath;
	tinyxml2::XMLDocument npcDoc;
	tinyxml2::XMLDocument mapDoc;
	tinyxml2::XMLDocument sceneDoc;
};
#endif