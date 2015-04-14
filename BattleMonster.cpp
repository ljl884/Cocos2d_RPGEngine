/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include "BattleMonster.h"

BattleMonster::BattleMonster(){
	debugMode = false;
}
BattleMonster* BattleMonster::create(const std::string& name, BattleLayer* layer){
	BattleMonster* ret = new BattleMonster();
	if (ret && ret->init(name, layer)){
		ret->autorelease();
		ret->initMonster();
		return ret;
	}
	else{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

void BattleMonster::initMonster(){
	initHateMap();
	m_type = BattleCharacter::ROLE_TYPE_MONSTER;
	m_controlable = false;
	if (debugMode){
		m_controlable = true;
	}
}
/*
void BattleMonster::initWithMessage(const MonsterMessage& msg){
	m_hp = m_initHp = msg.hp;
	m_atk = m_initAtk = msg.atk;
	m_defence = m_initDefence = msg.def;
	m_speed = m_initSpeed = msg.speed;
	m_atkSpeed = m_initAtkSpeed = msg.atk_speed;
	m_attackDistance = m_initAttackDistance = msg.atk_dis;
	m_bulletImg = msg.bullet;

	m_arm_offsetX = msg.offset_x;
	m_arm_offsetY = msg.offset_y;

	m_isNaima = msg.naima;
	if (m_isNaima){
		m_initAtk = -m_initAtk;
		m_atk = -m_atk;
	}
}
*/

void BattleMonster::update(float dt){
	BattleCharacter::update(dt);
	if (debugMode){
		return;
	}
	updateMonsterAttackTarget();
}

void BattleMonster::updateMonsterAttackTarget(){
	initHateMap();
	refreshHateMap();
	if (hateMap.size() == 0){
		return;
	}
	if (getHatest()){
		this->setAttackTarget(getHatest());
	}
	if (m_attackTarget == nullptr){
		int size = hateMap.size();

		int randnum = rand() % size;
		CCLOG("SIZE = %d,RAND = %d", size, randnum);
		int i = 1;
		std::map<Character_Ptr, int>::iterator it;
		for (it = hateMap.begin(); it != hateMap.end() && i < randnum; ++it){
			++i;
		}
		this->setAttackTarget(it->first);
		return;
	}

}

void BattleMonster::initHateMap(){
	std::list<Character_Ptr> temp = m_layer->getCharacterArray();
	for (auto it = temp.begin(); it != temp.end(); ++it){
		if ((**it)->getRoleType() == BattleCharacter::ROLE_TYPE_HERO
			|| (**it)->getRoleType() == BattleCharacter::ROLE_TYPE_NULL){
			hateMap.insert(std::make_pair((*it), 0));
		}
	}
}

void BattleMonster::addHateValue(BattleCharacter* sender, int HateValue){
	auto tempIt = find_if(hateMap.begin(), hateMap.end(), [=](const std::pair<Character_Ptr, int>& x)->bool{
		if (*x.first == sender){
			return true;
		}
		else{
			return false;
		}});
		if (tempIt != hateMap.end()){
			(*tempIt).second += HateValue;
		}
}

bool BattleMonster::cmpHate(const std::pair<Character_Ptr, int> &x, const std::pair<Character_Ptr, int> &y){
	return x.second > y.second;
}

void BattleMonster::refreshHateMap(){
	for (auto HMit = hateMap.begin(); HMit != hateMap.end();){
		if (*(*HMit).first == nullptr){
			HMit = hateMap.erase(HMit);
		}
		else{
			++HMit;
		}
	}
}

BattleCharacter** BattleMonster::getHatest(){
	std::vector<std::pair<Character_Ptr, int>> tempVec;
	for (auto it = hateMap.begin(); it != hateMap.end(); it++){
		tempVec.push_back(*it);
	}
	sort(tempVec.begin(), tempVec.end(), std::bind(&BattleMonster::cmpHate, this, std::placeholders::_1, std::placeholders::_2));
	if ((*tempVec.begin()).second == 0){
		return nullptr;
	}
	BattleCharacter** ret = (*tempVec.begin()).first;
	return ret;
}

Point BattleMonster::getHpSliderPos(){
	int h = getContentSize().height;
	return Point(0, h);
}

void BattleMonster::injured(int damage){
	BattleCharacter::injured(damage);
	refreshHateMap();
}