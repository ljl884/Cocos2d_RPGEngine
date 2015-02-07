#include "Skill.h"
#include "BattleHero.h"
Skill* Skill::create(BattleHero* h){
	Skill* skill = new Skill();
	if(skill && skill->init(h)){
		skill->autorelease();
		return skill;
	}else{
		CC_SAFE_DELETE(skill);
		return nullptr;
	}
}

bool Skill::init(BattleHero* h){
	m_hero = h;
	skillIcon = ui::Button::create("Skill/" + h->getSkill().icon);
	skillIcon->addTouchEventListener(this,toucheventselector(Skill::onTouchDown));
	this->addChild(skillIcon);

	int cd = m_hero->skillCD;
	cdTime = Label::create(__String::createWithFormat("%d",cd)->getCString(),"Arial",30);
	this->addChild(cdTime);
	if(cd == 0){
		cdTime->setVisible(false);
	}

	this->schedule(schedule_selector(Skill::updateCD),1.0f);

	return true;
}

BattleHero* Skill::getHero(){
	return m_hero;
}
void  Skill::onTouchDown(Ref* pSender,ui::TouchEventType type){
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
		if(m_hero->isCanSkill()){
			m_hero->skill();
			cdTime->setString(__String::createWithFormat("%d",m_hero->getSkill().cd)->getCString());
		}
	}
}

void Skill::updateCD(float delta){
	int cd = m_hero->skillCD;
	if(cd <= 0){
		cdTime->setVisible(false);
		return;
	}else{
		cdTime->setString(__String::createWithFormat("%d",cd)->getCString());
		cdTime->setVisible(true);
	}
}