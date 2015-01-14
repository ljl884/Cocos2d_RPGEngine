#include "HelloWorldScene.h"

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

using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	
	scene->addChild(layer);

	
	

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	//Node *node = CSLoader::createNode("MainScene.csb");
	//this->addChild(node);

	//import Map
	//auto map = TMXTiledMap::create("map.tmx");
	//this->addChild(map);
	
	
	auto map = Stage::create("bmap.tmx","BMap.jpg");
	this->addChild(map);
	
	map->setLayerVisibility("Layer1", false);
	map->setLayerVisibility("Block", true);




    


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

  
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

  
	auto input = new InputManager();

	this->addChild(input);

	auto dialog = new Dialog("dialogbar.png");
	this->addChild(dialog, 0, "Dialog");

	auto perform = new Perform();
	perform->setStage(map);
	perform->setDialog(dialog);

	input->bindPerformer(perform);

	InformationCenter *ic = InformationCenter::getInstance();
	ic->setPerformer(perform);

	perform->initializeMainCharacter("Main.png");
	perform->putinMainCharacter(this, map->getObjectPosition("Hero","Pst"));
	auto NPC1 = new Character("NPC.png");
	perform->putinCharacter(this, map->getObjectPosition("Hero", "NPC1"), NPC1);
	
	XMLParser *parser = new XMLParser();
	
	//auto NPC2 = new Character(parser->getNPCImageUrl("NPC2"));
	auto NPC2 = new Character("TNPC.png");
	perform->putinCharacter(this, map->getObjectPosition("Hero", "NPC2"), NPC2);
	
	



	
    
    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    //Director::getInstance()->end();

	Size winSize = Director::sharedDirector()->getWinSize();  


	
	auto sprite2 = new Character("TNPC.png");
	sprite2->character->setPosition(300, 300);
	this->addChild(sprite2->character);

	//sprite2->moveTo(3,ccp(0,0));
	sprite2->moveToDirection(down);
	



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::spriteMoveFinished(cocos2d::Node *sender){
	Sprite *sprite = (Sprite *)sender;
	this->removeChild(sprite, true);
}