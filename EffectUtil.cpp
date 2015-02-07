#include "EffectUtil.h"

EffectUtil* EffectUtil::m_instance = nullptr;

EffectUtil* EffectUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new EffectUtil();
	}
	return m_instance;
}

Animate*  EffectUtil::getSkillEffectById(int id,int loop){
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(String::createWithFormat("Battle/Skill/Effect/%d.plist",id)->getCString(),
		String::createWithFormat("Battle/Skill/Effect/%d.png",id)->getCString());
	SpriteFrame* temp;
	Vector<SpriteFrame*> v;
	int index = 1;
	do{
		CCLOG("INDEX = %d",index);
		temp = cache->getSpriteFrameByName(String::createWithFormat("%d_%d.png",id,index)->getCString());
		index++;
		if(temp == nullptr){
			break;
		}else{
			v.pushBack(temp);
		}
	}while(true);

	Animation* animation = Animation::createWithSpriteFrames(v);
	animation->setLoops(loop);
	animation->setDelayPerUnit(0.1f);
	Animate* ret = Animate::create(animation);
	return ret;
}