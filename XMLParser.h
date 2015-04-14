/************************************************
Author: Wentao Li
Date:14-4-2015
Description:Coumponent to Parse XML Script
*************************************************/
#ifndef _XML_PARSER_
#define _XML_PARSER_

#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"
#include "EventAction.h"


using namespace cocos2d;

enum ScriptType
{
	npc = 0,
	map = 1,
	scene = 2,
	event=3
};

/* Here defines servral data model class. These objects would be the return values of the core functions of XMLParser*/
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
	std::string mapName;
	std::string mainCharacterName;
	std::string mainCharacterPosition;
	std::list<std::string> npcNames;
	std::list<std::string> npcPositions;
};

class XMLEvent
{
public:
	std::queue<EventAction*> actions;
}; 

//-------------------------------------------------------------
class XMLParser
{
public:
	//XMLParser is a singleton class which ensures the script file will be read only once
	static XMLParser* getInstance()
	{
		if (instance == NULL)
			instance = new XMLParser();
		return instance;
	}

	XMLNPC* getNPCInfo(std::string npcName);
	XMLMap* getMapInfo(std::string mapName);
	XMLScene* getSceneInfo(std::string sceneName);
	XMLEvent* getEventInfo(std::string eventName);
	std::string getNPCImageUrl(std::string npcName);
	bool getMapDetail(std::string mapName, std::string &imgUrl, std::string &tmxUrl);
private:
	XMLParser();
	static XMLParser *instance;
	std::string NPCScriptUrl;
	tinyxml2::XMLElement *findNodeByName(std::string name, ScriptType type);
	XMLEvent* parseEventScript(std::string filename);
	std::string xmlFilePath;
	tinyxml2::XMLDocument npcDoc;
	tinyxml2::XMLDocument mapDoc;
	tinyxml2::XMLDocument sceneDoc;
	tinyxml2::XMLDocument eventDoc;

};
#endif