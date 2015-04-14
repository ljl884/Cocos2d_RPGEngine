/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _BATTLE_MONSTER_
#define _BATTLE_MONSTER_

#include "cocos2d.h"
#include "BattleLayer.h"
#include "BattleCharacter.h"



class BattleMonster : public BattleCharacter{
public:
	BattleMonster();
	static BattleMonster* create(const std::string& name, BattleLayer* layer);
	void initMonster();

	virtual Point getHpSliderPos();
	void addHateValue(BattleCharacter* sender, int HateValue);

	//void initWithMessage(const MonsterMessage& msg);
private:
	virtual void update(float dt);
	void updateMonsterAttackTarget();
	void initHateMap();
	void refreshHateMap();
	virtual void injured(int damage);
	BattleCharacter** getHatest();
	bool cmpHate(const std::pair<Character_Ptr, int> &x, const std::pair<Character_Ptr, int> &y);
private:
	std::map<Character_Ptr, int> hateMap;

	bool debugMode;
};
#endif