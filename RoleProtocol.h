/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _ROLEPROTOCOL_H_  
#define _ROLEPROTOCOL_H_ 

#include "cocos2d.h"
class RoleProtocol  {
public:
	virtual void stand() = 0;
	virtual void move() = 0;
	virtual void attack() = 0;
	virtual void skill() = 0;
	virtual void injured(int effect, int damage = 0) = 0;
	virtual void die() = 0;
};
#endif  