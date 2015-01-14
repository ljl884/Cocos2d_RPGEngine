#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "InformationCenter.h"


#define MAX_MOVING_DISTANCE 1000
#define MOVING_SPEED 80
#define STEP_DISTANCE 15

enum Character_Direction
{
	up = 0,
	down = 1,
	left = 2,
	right = 3
};

class Character 
{
public:

	cocos2d::CCSprite* character;
	bool mainCharacter;

	Character(std::string filename);

	
	std::string getId();
	void setId(std::string newId);
	cocos2d::Point getPosition();
	void updatePoint(cocos2d::CCPoint newpoint);
	void setPosition(cocos2d::CCPoint position);
	void moveTo(cocos2d::CCPoint newpoint);
	void moveTo(float duration, cocos2d::CCPoint newpoint);
	void moveBy();
	void moveToDirection(Character_Direction direction);
	void moveToDirectionBy(Character_Direction direction, int distance);
	void moveToDirectionBy(float duration, Character_Direction direction, int distance);
	void stopMoving();
	void changeFacingDirection(Character_Direction newDirection);
	void playMovingAnimation(Character_Direction direction);
	bool isMoving = false;
	void moveoverCallBack(void);
	bool isNextPositionBlocked();
	Character_Direction facingDirection;
	Character_Direction movingDirection;

protected:
	std::string id;
	std::string filename;
	
	
	
	
	

};

#endif //__CHARACTER_H__