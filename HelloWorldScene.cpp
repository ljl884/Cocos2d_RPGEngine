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

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
		  
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