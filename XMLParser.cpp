#include "XMLParser.h"
#include"Config.h"
//#define NPC_SCRIPT "xml\\NPC.xml"
//#define MAP_SCRIPT "xml\\MAP.xml"
//#define SCENE_SCRIPT "xml\\SCENE.xml"

XMLParser * XMLParser::instance = NULL;

XMLParser::XMLParser()
{
	npcDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(Config::NPC_SCRIPT).c_str());
	mapDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(Config::MAP_SCRIPT).c_str());
	sceneDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(Config::SCENE_SCRIPT).c_str());
	eventDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(Config::EVENT_SCRIPT).c_str());
}

tinyxml2::XMLElement* XMLParser::findNodeByName(std::string name, ScriptType type)
{
	const char* nodeName;
	tinyxml2::XMLDocument* doc;
	switch (type)
	{
	case npc:
		nodeName = "NPC";
		doc = &npcDoc;
		break;
	case map:
		nodeName = "MAP";
		doc = &mapDoc;
		break;
	case scene:
		nodeName = "Scene";
		doc = &sceneDoc;
		break;
	case event:
		nodeName = "Event";
		doc = &eventDoc;
		break;
	default:
		break;
	}
	tinyxml2::XMLElement *root = doc->RootElement();
	tinyxml2::XMLElement *node = root->FirstChildElement(nodeName);
	while (node)
	{
		const char* tempName = node->FirstChildElement("name")->GetText();
		if (name == tempName)
			return node;
		node = node->NextSiblingElement();
	}
	return NULL;
}

XMLNPC* XMLParser::getNPCInfo(std::string npcName)
{
	XMLNPC *npcTemplate = new XMLNPC();
	tinyxml2::XMLElement *npcNode=findNodeByName(npcName, npc);
	if (NULL != npcNode)
	{
		npcTemplate->ImageUrl = npcNode->FirstChildElement("image")->GetText();
	}
	return npcTemplate;
}
XMLMap* XMLParser::getMapInfo(std::string mapName)
{
	XMLMap* mapTemplate = new XMLMap();
	tinyxml2::XMLElement *mapNode = findNodeByName(mapName, map);
	if (NULL != mapNode)
	{
		mapTemplate->ImageUrl = mapNode->FirstChildElement("image")->GetText();
		mapTemplate->TMXUrl   = mapNode->FirstChildElement("tmx")->GetText();
	}
	return mapTemplate;
}
XMLScene* XMLParser::getSceneInfo(std::string sceneName)
{
	XMLScene* sceneTemplate = new XMLScene();
	tinyxml2::XMLElement *sceneNode = findNodeByName(sceneName, scene);
	if (NULL != sceneNode)
	{
		sceneTemplate->mapName = sceneNode->FirstChildElement("map")->GetText();
		
		tinyxml2::XMLElement *maincharacter = sceneNode->FirstChildElement("maincharacter");
		if (NULL!=maincharacter)
		{
			sceneTemplate->mainCharacterName = maincharacter->FirstChildElement("name")->GetText();
			sceneTemplate->mainCharacterPosition = maincharacter->FirstChildElement("position")->GetText();
		}
	

		tinyxml2::XMLElement *sceneNPCs = sceneNode->FirstChildElement("NPCs");
		if (NULL != sceneNPCs)
		{
			tinyxml2::XMLElement *npc = sceneNPCs->FirstChildElement("npc");
			while (npc)
			{
				sceneTemplate->npcNames.push_back(npc->FirstChildElement("name")->GetText());
				sceneTemplate->npcPositions.push_back(npc->FirstChildElement("postion")->GetText());
				npc = npc->NextSiblingElement();
			}
		}
		
	}

	return sceneTemplate;
}
XMLEvent* XMLParser::getEventInfo(std::string eventName)
{
	XMLEvent* eventTemplate = NULL;
	tinyxml2::XMLElement *eventNode = findNodeByName(eventName, event);
	if (NULL != eventNode){
		std::string scriptUrl = eventNode->FirstChildElement("file")->GetText();
		eventTemplate = parseEventScript(scriptUrl);
	}
	
	return eventTemplate;
}
XMLEvent* XMLParser::parseEventScript(std::string filename)
{
	XMLEvent* eventTemplate = new XMLEvent();
	tinyxml2::XMLDocument *eventDocument = new tinyxml2::XMLDocument();
	eventDocument->LoadFile(FileUtils::getInstance()->fullPathForFilename(Config::EVENT_PATH + filename).c_str());
	if (eventDocument == NULL)
		return NULL;
	tinyxml2::XMLElement *root = eventDocument->RootElement();
	tinyxml2::XMLElement *actionNode = root->FirstChildElement("Action");
	while (actionNode)
	{
		std::string actionType = actionNode->FirstChildElement("type")->GetText();
		if (actionType == "dialog")
		{
			std::string  text = actionNode->FirstChildElement("text")->GetText();
			DialogAction *dialogAction = new DialogAction(text);
			eventTemplate->actions.push(dialogAction);
		}
		else if (actionType == "move")
		{
			MoveAction *moveAction = new MoveAction();
			eventTemplate->actions.push(moveAction);
		}
		else if (actionType == "change_scene")
		{
			std::string sceneName = actionNode->FirstChildElement("scene")->FirstChildElement("name")->GetText();
			if (sceneName != "")
			{
				SceneAction *sceneAction = new SceneAction(sceneName);
				eventTemplate->actions.push(sceneAction);
			}
			
		}
		actionNode = actionNode->NextSiblingElement();
	}
	delete eventDocument;
	return eventTemplate;
}
std::string XMLParser::getNPCImageUrl(std::string npcName)
{
	tinyxml2::XMLElement *npcNode = findNodeByName(npcName, npc);
	if (NULL == npcNode)
		return "";
	return  npcNode->FirstChildElement("image")->GetText();
	
}
bool XMLParser::getMapDetail(std::string mapName, std::string &imgUrl, std::string &tmxUrl)
{
	tinyxml2::XMLElement *mapNode = findNodeByName(mapName, map);
	if (NULL == mapNode)
		return false;
	imgUrl = mapNode->FirstChildElement("image")->GetText();
	tmxUrl = mapNode->FirstChildElement("tmx")->GetText();
	return true;
}