#include "SceneBuilder.h"
#include "Character.h"
#include "Perform.h"
#include "Stage.h"
#include "InputManager.h"
#include "ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h" 
#include"Box2D/Box2D.h"
#include "Dialog.h"
#include "XMLParser.h"
#include "InformationCenter.h"
#include "Config.h"

//#define MAP_PATH "map/"
//#define NPC_PATH "npc/"


SceneBuilder::SceneBuilder()
{
	
}
Scene *SceneBuilder::BuildScene(std::string sceneId)
{
	return BuildScene(sceneId, "");
}
Scene *SceneBuilder::BuildScene(std::string sceneId,std::string mainCharacterPosition)
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	XMLParser *parser = XMLParser::getInstance();
	XMLScene *xmlScene = parser->getSceneInfo(sceneId);


	//Build Map
	std::string mapName = xmlScene->mapName;
	std::string mapImg, mapTmx;
	XMLMap *xmlMap = parser->getMapInfo(mapName);
	auto map = Stage::create(Config::MAP_PATH + xmlMap->TMXUrl, Config::MAP_PATH + xmlMap->ImageUrl);
	delete xmlMap;
	//Point p = map->getPosition();
	layer->addChild(map);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map->setLayerVisibility(Config::BACKGROUND_LAYER, false);
	map->setLayerVisibility(Config::BLOCK_LAYER, false);
	map->setLayerVisibility(Config::EVENT_LAYER, false);


	//Build components
	auto input = new InputManager();
	layer->addChild(input);

	auto dialog = new Dialog(Config::DIALOG_BAR_URL);
	layer->addChild(dialog, 0, "Dialog");

	auto perform = new Perform();
	perform->setStage(map);
	perform->setDialog(dialog);

	input->bindPerformer(perform);
	
	InformationCenter *ic = InformationCenter::getInstance();
	ic->setPerformer(perform);


	
	//Build Main Character
	if ("" == xmlScene->mainCharacterName)
		perform->setOperationStatus(NoMainCharacter);   //This will ban moving operations on main character
	else
	{
		std::string maincharacterUrl = Config::NPC_PATH + parser->getNPCInfo(xmlScene->mainCharacterName)->ImageUrl;
		perform->initializeMainCharacter(maincharacterUrl);
		Point position;
		if (mainCharacterPosition != "")
			position = map->getObjectPosition(Config::POSITION_LAYER, mainCharacterPosition);
		else if (xmlScene->mainCharacterPosition != "")
			position = map->getObjectPosition(Config::POSITION_LAYER, xmlScene->mainCharacterPosition);
			
		perform->putinMainCharacter(layer, position);
		perform->setCameraPosition(position);
		
	}



	//Build NPCs
	if (!xmlScene->npcNames.empty())
	{
		std::list<std::string>::iterator iNPCName, iNPCPosition;

		iNPCPosition = xmlScene->npcPositions.begin();
		for (iNPCName = xmlScene->npcNames.begin(); iNPCName != xmlScene->npcNames.end(); iNPCName++)
		{

			std::string npcUrl = Config::NPC_PATH + parser->getNPCInfo(*iNPCName)->ImageUrl;
			std::string npcPosition = *iNPCPosition;
			auto NPC = new Character(npcUrl);
			perform->putinCharacter(layer, map->getObjectPosition(Config::POSITION_LAYER, npcPosition), NPC);
			iNPCPosition++;
		}

	}


	scene->addChild(layer);
	return scene;

}

Scene* SceneBuilder::BuildBattleScene()
{
	auto battleScene = new BattleScene();
	return battleScene;
}