#ifndef _EFFECT_UTIL_H_
#define _EFFECT_UTIL_H_
#include "cocos2d.h"
using namespace cocos2d;

class EffectUtil{
public:
	static EffectUtil* getInstance();
	Animate* getSkillEffectById(int id,int loop=1);

private:
	static EffectUtil* m_instance;
};
#endif