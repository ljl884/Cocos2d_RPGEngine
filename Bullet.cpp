#include "Bullet.h"

#include "BattleMonster.h"
#include "BattleHero.h"
Bullet::~Bullet(){
	this->removeAllChildren();
}
Bullet* Bullet::createWithTarget(BattleCharacter* sender, BattleCharacter** targetPtr){
	Bullet* ret = new Bullet();
	if(ret && ret->initWithTarget(sender,targetPtr)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool Bullet::initWithTarget(BattleCharacter* sender, BattleCharacter** targetPtr){
	m_damage = 0;
	m_effect = 0;
	m_bullet = Sprite::create("Battle/Bullet/" + sender->getBulletImg());
	setDamage(sender->getAtk());
	setHateValue(sender->getAtkHateValue());
	if (sender->getRoleType() == BattleCharacter::ROLE_TYPE_HERO){
		BattleHero* h = dynamic_cast<BattleHero*>(sender);
		if(h->isSkilling()){
			m_effect = h->getSkill().hit_e;
			if(h->getSkill().skill_bullet_img.compare("null")){
				m_bullet = Sprite::create("Battle/Bullet/" + h->getSkill().skill_bullet_img);
			}
		}
		
	}
	if(sender->isNaima()){
		m_effect = 5005;//回血的效果
	}
	setPosition(sender->getPosition() + Point(0,sender->getContentSize().height/2));
	
	this->addChild(m_bullet);

	m_speed = sender->getBulletSpeed();
	
	m_targetPtr = targetPtr;
	m_sender = sender;
	this->scheduleUpdate();
	return true;
}

void Bullet::setDamage(int damage){
	m_damage = damage;
}

void Bullet::setHateValue(int value){
	m_HateValue = value;
}

void Bullet::update(float dt){
	m_target = *m_targetPtr;
	if(!m_target){
		this->removeFromParentAndCleanup(true);
		return;
	}
	if(!m_target->getBoundingBox().containsPoint(this->getPosition())){
		float distance = ccpDistance(getPosition(),m_target->getPosition()+Vec2(0,m_target->getContentSize().height));
		float t = distance / m_speed;
		float speed_x = (m_target->getPositionX() - getPositionX()) / t;
		float speed_y = (m_target->getPositionY()+ m_target->getContentSize().height/2 - getPositionY()) / t;
		setPositionX(getPositionX() + speed_x);
		setPositionY(getPositionY() + speed_y);
	}else{
		CCLOG("BULLET->ARR");
		m_target->injured(m_effect,m_damage);
		if (m_target->getRoleType() == BattleCharacter::ROLE_TYPE_MONSTER){
			BattleMonster* m = dynamic_cast<BattleMonster*>(m_target);
			m->addHateValue(m_sender,m_HateValue);
		}
		this->removeFromParentAndCleanup(true);
	}
}

