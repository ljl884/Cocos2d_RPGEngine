#ifndef _BATTLE_LAYER_
#define _BATTLE_LAYER_

#include "cocos2d.h"
#include "MonsterMessage.h"
using namespace cocos2d;
class BattleCharacter;
typedef BattleCharacter** Character_Ptr;


class BattleLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BattleLayer);
	void addCharacter(BattleCharacter* c);
	std::list<Character_Ptr> getCharacterArray(){ return rolesArray; }
	void initTeam();
	void initMonsterDeq(std::deque<MonsterMessage> deq);
	void addBullet(BattleCharacter* sender, Character_Ptr targetPtr);
private:
	virtual void update(float delta);
	void initListener();
	bool comparePosY(Character_Ptr a, Character_Ptr b);
	void refreshLocalZOrder();
	void updateMyControl();
	void cleanNullPtrInArray();

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

private:
	std::list<Character_Ptr> rolesArray;
	BattleCharacter* currentControlled;
	Character_Ptr currentControlledPtr;
	std::deque<MonsterMessage> m_monsterDeq;
};
#endif