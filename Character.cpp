#include "Character.h"



using namespace cocos2d;
Character::Character(std::string _filename)
{
	if ("" == id)
		id = _filename;
	filename = _filename;

	//initialize textures and frames
	
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(filename);
	character = CCSprite::createWithTexture(texture, CCRectMake(0, 0, 32, 48));
	facingDirection = down;


	CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 48*0, 32, 48));
	CCSpriteFrameCache::getInstance()->addSpriteFrame(frame,id+"facingDown");
	frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 48*1, 32, 48));
	CCSpriteFrameCache::getInstance()->addSpriteFrame(frame, id + "facingLeft");
	frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 48*2, 32, 48));
	CCSpriteFrameCache::getInstance()->addSpriteFrame(frame, id + "facingRight");
	frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 48*3, 32, 48));
	CCSpriteFrameCache::getInstance()->addSpriteFrame(frame, id + "facingUp");


	//initialize moving animatations
	Vector<SpriteFrame*> animFrames;
	CCAnimation *animation;
	for (int y = 0; y < 4; y++)
	{
		
		for (int x = 0; x < 4; x++){
			CCSpriteFrame * frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(32 * x, 48 * y, 32, 48));
			animFrames.pushBack(frame);
			animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
		}
		if (y == 0)
			CCAnimationCache::sharedAnimationCache()->addAnimation(animation, id+"DOWN");
		else if (y==1)
			CCAnimationCache::sharedAnimationCache()->addAnimation(animation, id+"LEFT");
		else if (y==2)
			CCAnimationCache::sharedAnimationCache()->addAnimation(animation, id+"RIGHT");
		else if (y==3)
			CCAnimationCache::sharedAnimationCache()->addAnimation(animation, id+"UP");
		animFrames.clear();
	}
	
}

void Character::setId(std::string newId)
{
	id = newId;
}

void Character::setPosition(cocos2d::CCPoint position)
{
	character->setPosition(position);
}
void Character::changeFacingDirection(Character_Direction newDirection)
{
	facingDirection = newDirection;
	std::string key;
	switch (facingDirection)
	{
	case up:
		key = id + "facingUp";
		break;
	case down:
		key = id + "facingDown";
		break;
	case left:
		key = id + "facingLeft";
		break;
	case right:
		key = id + "facingRight";
		break;
	default:
		break;
	}
	CCSpriteFrame *frame = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(key);
	character->setSpriteFrame(frame);
}

void Character::moveTo(float duration, CCPoint newpoint){
	CCFiniteTimeAction *actionMove = CCMoveTo::create(duration, newpoint);  
	//character->runAction(actionMove);
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Character::moveoverCallBack, this));
	auto action = Sequence::create(actionMove, callfunc, NULL);
	character->runAction(action);
}

void Character::moveToDirection(Character_Direction direction)
{
	moveToDirectionBy(direction, Config::MAX_MOVING_DISTANCE);
}
void Character::moveToDirectionBy(Character_Direction direction, int distance)
{
	moveToDirectionBy((float)distance / Config::MOVING_SPEED, direction, distance);
}
void Character::moveToDirectionBy(float duration,Character_Direction direction, int distance)
{
	float x = 0, y = 0;
	character->getPosition(&x, &y);	
	switch (direction)
	{		
	case up:
		facingDirection = up;
		moveTo(duration, ccp(x, y + distance));
		break;
	case down:
		facingDirection = down;
		moveTo(duration, ccp(x, y - distance));
		break;
	case left:
		facingDirection = left;
		moveTo(duration, ccp(x - distance, y));
		break;
	case right:
		facingDirection = right;
		moveTo(duration, ccp(x + distance, y));
		break;
	default:
		break;
	}
}

void Character::moveoverCallBack(void)
{
	InformationCenter *ic = InformationCenter::getInstance();
	ic->moveOver();		
}

void Character::playMovingAnimation(Character_Direction direction)
{
	switch (direction)
	{
	case up:
		character->runAction(RepeatForever::create(Animate::create(CCAnimationCache::sharedAnimationCache()->getAnimation(id + "UP"))));
		break;
	case down:
		character->runAction(RepeatForever::create(Animate::create(CCAnimationCache::sharedAnimationCache()->getAnimation(id + "DOWN"))));
		break;
	case left:
		character->runAction(RepeatForever::create(Animate::create(CCAnimationCache::sharedAnimationCache()->getAnimation(id + "LEFT"))));
		break;
	case right:
		character->runAction(RepeatForever::create(Animate::create(CCAnimationCache::sharedAnimationCache()->getAnimation(id + "RIGHT"))));
		break;
	default:
		break;
	}
}
void Character::stopMoving()
{

	changeFacingDirection(facingDirection);
	character->stopAllActions();
	
}


Point Character::getPosition()
{
	return character->getPosition();
}
