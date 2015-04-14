/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include "BattleHero.h"
#include "SkillImpl.h"
#include "EffectUtil.h"
BattleHero* BattleHero::create(const std::string& name, BattleLayer* layer){
	BattleHero* ret = new BattleHero();
	if (ret && ret->init(name, layer)){
		ret->initHero();
		ret->autorelease();
		return ret;
	}
	else{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

BattleHero* BattleHero::create(const std::string& name, BattleLayer* layer, int offsetX, int offsetY){
	BattleHero* ret = new BattleHero();
	if (ret && ret->init(name, layer)){
		ret->initHero();
		ret->autorelease();
		ret->setArmOffsetX(offsetX);
		ret->setArmOffsetY(offsetY);
		return ret;
	}
	else{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

void BattleHero::skill(){
	runSkillEffect(m_skill.begin_e);
	runStateEffect(m_skill.state_e);
	skilling = true;
	canUseSkill = false;
	m_state_lastTime = 0;

	skillCD = m_skill.cd;

	SkillImpl impl;
	impl.runSkill(m_skill.id, this);
}
void BattleHero::initHero(){
	setControlable(true);
	m_type = BattleCharacter::ROLE_TYPE_HERO;
	m_state_sprite = nullptr;
	canUseSkill = false; //TO BE SET TRUE
	skilling = false;
	m_state_lastTime = 0;
	skillCD = 0;
}

void BattleHero::runStateEffect(int id){
	if (m_state_sprite == nullptr){
		m_state_sprite = Sprite::create("Battle/Skill/null.png");
		m_state_sprite->setAnchorPoint(Point(0.5f, 0));
		this->addChild(m_state_sprite, 10);
	}

	Animate* a = EffectUtil::getInstance()->getSkillEffectById(id, -1);
	m_state_sprite->runAction(a);

}