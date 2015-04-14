/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include "BattleScene.h"
#include"cocostudio/CocoStudio.h" 
#include "ui/CocosGUI.h"
#include "Config.h"
#include "BattleLayer.h"


#define ANIMATE_PATH "BoneAnimate\\"

using namespace cocostudio;

BattleScene::BattleScene()
{
	std::string animatePath = Config::BATTLE_RESOURCE + ANIMATE_PATH;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	std::string mapImageFilename = Config::BATTLE_RESOURCE + "flightBG.jpg";
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(mapImageFilename);
	auto bgImg = Sprite::createWithTexture(texture);
	bgImg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bgImg);

	ArmatureDataManager::getInstance()->addArmatureFileInfo(animatePath + "HuoChaiRen0.png", animatePath + "HuoChaiRen0.plist", animatePath + "HuoChaiRen.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo(animatePath + "Hero_Gunner0.png", animatePath + "Hero_Gunner0.plist", animatePath + "Hero_Gunner.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo(animatePath + "Hero10.png", animatePath + "Hero10.plist", animatePath + "Hero1.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo(animatePath + "Monster10.png", animatePath + "Monster10.plist", animatePath + "Monster1.ExportJson");

	//Armature *armature = Armature::create("HuoChaiRen");
	//armature->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
	//armature->getAnimation()->play("walk");
	//this->addChild(armature);

	auto battleLayer = BattleLayer::create();
	battleLayer->initTeam();
	this->addChild(battleLayer);
}
