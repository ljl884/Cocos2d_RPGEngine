#include "XMLParser.h"

#define NPC_SCRIPT "xml\\NPC.xml"
#define MAP_SCRIPT "xml\\MAP.xml"
#define SCENE_SCRIPT "xml\\SCENE.xml"

XMLParser::XMLParser()
{
	npcDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(NPC_SCRIPT).c_str());
	mapDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(MAP_SCRIPT).c_str());
	sceneDoc.LoadFile(FileUtils::getInstance()->fullPathForFilename(SCENE_SCRIPT).c_str());	
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