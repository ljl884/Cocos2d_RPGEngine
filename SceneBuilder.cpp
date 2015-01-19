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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto map = Stage::create("bmap.tmx", "BMap.jpg");
	Point p = map->getPosition();
	layer->addChild(map);

	map->setLayerVisibility("Layer1", false);
	map->setLayerVisibility("Block", true);

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

	perform->initializeMainCharacter("Main.png");
	perform->putinMainCharacter(layer, map->getObjectPosition("Hero", "Pst"));
	auto NPC1 = new Character("NPC.png");
	perform->putinCharacter(layer, map->getObjectPosition("Hero", "NPC1"), NPC1);

	XMLParser *parser = new XMLParser();

	//auto NPC2 = new Character(parser->getNPCImageUrl("NPC2"));
	auto NPC2 = new Character("TNPC.png");
	perform->putinCharacter(layer, map->getObjectPosition("Hero", "NPC2"), NPC2);




	scene->addChild(layer);
	return scene;

}

