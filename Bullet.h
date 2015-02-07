#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"
#include "BattleCharacter.h"
using namespace cocos2d;
class BattleCharacter;
class Bullet : public Node{
public:
	static Bullet* createWithTarget(BattleCharacter* sender, BattleCharacter** target);
	bool initWithTarget(BattleCharacter* sender, BattleCharacter** target);
	void setDamage(int damage);
	void setHateValue(int value);
	~Bullet();
private:
	Sprite* m_bullet;
	BattleCharacter* m_target;
	BattleCharacter** m_targetPtr;
	virtual void update(float dt);
	int m_damage;
	int m_speed;
	BattleCharacter* m_sender;
	int m_HateValue;
	int m_effect;
};
#endif