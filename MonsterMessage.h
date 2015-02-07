#ifndef _MONSTER_MESSAGE_H_
#define _MONSTER_MESSAGE_H_
#include "cocos2d.h"

class MonsterMessage{
public:
	int id;
	std::string name;
	std::string r_name;
	std::string r_png;
	std::string r_plist;
	std::string r_ExportJson;
	int offset_x;
	int offset_y;
	int atk_dis;
	int hp;
	int atk;
	int def;
	int speed;
	int atk_speed;
	bool naima;
	std::string bullet;
};

#endif