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


SceneBuilder::SceneBuilder()
{
	
}
Scene *SceneBuilder::BuildScene(std::string sceneId)
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	XMLParser *parser = new XMLParser();

	XMLScene *xmlScene = parser->getSceneInfo(sceneId);


	//Build Map
	std::string mapName = xmlScene->mapName;
	std::string mapImg, mapTmx;
	XMLMap *xmlMap = parser->getMapInfo(mapName);
	auto map = Stage::create(xmlMap->TMXUrl, xmlMap->ImageUrl);
	delete xmlMap;
	Point p = map->getPosition();
	layer->addChild(map);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	map->setLayerVisibility(BACKGROUND_LAYER, false);
	map->setLayerVisibility(BLOCK_LAYER, true);


	//Build components
	auto input = new InputManager();
	layer->addChild(input);

	auto dialog = new Dialog("dialogbar.png");
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
		std::string maincharacterName = parser->getNPCInfo(xmlScene->mainCharacterName)->ImageUrl;
		perform->initializeMainCharacter(maincharacterName);
		if (xmlScene->mainCharacterPosition != "")
			perform->putinMainCharacter(layer, map->getObjectPosition(POSITION_LAYER, xmlScene->mainCharacterPosition));
	}



	//Build NPCs
	if (!xmlScene->npcNames.empty())
	{
		std::list<std::string>::iterator iNPCName, iNPCPosition;

		iNPCPosition = xmlScene->npcPositions.begin();
		for (iNPCName = xmlScene->npcNames.begin(); iNPCName != xmlScene->npcNames.end(); iNPCName++)
		{

			std::string npcName = parser->getNPCInfo(*iNPCName)->ImageUrl;
			std::string npcPosition = *iNPCPosition;
			auto NPC = new Character(npcName);
			perform->putinCharacter(layer, map->getObjectPosition(POSITION_LAYER, npcPosition), NPC);
			iNPCPosition++;
		}

	}


	scene->addChild(layer);
	return scene;

}

