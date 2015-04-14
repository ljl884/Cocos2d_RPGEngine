/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include "SkillImpl.h"
#include "BattleHero.h"
#include "BattleLayer.h"
void SkillImpl::runSkill(int id, BattleHero* hero){
	switch(id){
	case 4001://skill_kb
	{
		hero->setHp(hero->getHp()/2);
		hero->setSpeed(hero->getSpeed()*2);
		hero->setAtkSpeed(hero->getAtkSpeed()*2);
		hero->setAtkHateValue(hero->getAtkHateValue()*3);
		break;
	}

	case 4002://skill_zl
	{
		Character_Ptr initTarget = hero->getAttackTarget();
		std::list<Character_Ptr> list = hero->getLayer()->getCharacterArray();
		for(auto it = list.begin();it!=list.end();it++){
			if((**it)->getRoleType() == BattleCharacter::ROLE_TYPE_HERO){
				hero->setAttackTarget(*it);
				hero->sendBullet();
			}
		}
		hero->setAttackTarget(initTarget);
		break;
	}

	case 4003://skill_ld
	{
		hero->setAtk(hero->getAtk()*2);
		hero->setBulletSpeed(hero->getBulletSpeed()*2);
		break;
	}
	default:
		break;
	}
}