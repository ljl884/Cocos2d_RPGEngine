#ifndef _BATTLE_HERO_
#define _BATTLE_HERO_

#include "cocos2d.h"
#include "BattleCharacter.h"

class SkillMessage
{
public:
	int id;
	std::string name;
	std::string desc;
	std::string icon;
	int begin_e;
	int state_e;
	int hit_e;
	std::string lua;
	int lastTime;
	int cd;
	std::string skill_bullet_img;
};
class BattleHero :public BattleCharacter
{
public:
	static BattleHero* create(const std::string& name, BattleLayer* layer);
	static BattleHero* create(const std::string& name, BattleLayer* layer, int offsetX, int offsetY);
	void initHero();
	inline void setSkill(SkillMessage s){ m_skill = s; }
	inline SkillMessage getSkill(){ return m_skill; }

	void runStateEffect(int id);
	//�Ƿ��ڴ���״̬
	inline bool isSkilling(){ return skilling; }
	//�Ƿ���ʹ�ô���
	inline bool isCanSkill(){ return canUseSkill; }
	//�ָ�״̬
	void recover();
	virtual void skill();

	float skillCD;
private:
	SkillMessage m_skill;
	bool skilling;
	bool canUseSkill;

	float m_state_lastTime;


	

	Sprite* m_state_sprite;
};
#endif