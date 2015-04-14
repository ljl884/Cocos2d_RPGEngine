/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _SKILL_H_
#define _SKILL_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class BattleHero;
class Skill : public Node{
public:
	bool init(BattleHero* h);
	static Skill* create(BattleHero* h);
	void onTouchDown(Ref* pSender,ui::TouchEventType type);
	BattleHero* getHero();
	void updateCD(float delta);
private:
	ui::Button* skillIcon;
	BattleHero* m_hero;
	Label* cdTime;
};
#endif