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
class XMLNPC
{
public:
	std::string ImageUrl;
};
class XMLMap
{
public:
	std::string ImageUrl;
	std::string TMXUrl;
};
class XMLScene
{
public:
	std::string mapName="";
	std::string mainCharacterName="";
	std::string mainCharacterPosition="";
	std::list<std::string> npcNames;
	std::list<std::string> npcPositions;
};

class XMLParser
{
public:
	XMLParser();

	XMLNPC* getNPCInfo(std::string npcName);
	XMLMap* getMapInfo(std::string mapName);
	XMLScene* getSceneInfo(std::string sceneName);
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