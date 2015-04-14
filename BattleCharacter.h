/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _BATTLE_CHARACTER_
#define _BATTLE_CHARACTER_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "RoleProtocol.h"
#include"cocostudio/CocoStudio.h"


using namespace cocos2d;
using namespace cocos2d::extension;

class BattleLayer;


class BattleCharacter : public RoleProtocol,public Node
{
public :
	BattleCharacter();
	static BattleCharacter* create(const std::string& name, BattleLayer* layer);
	virtual bool init(const std::string& name, BattleLayer* layer);
	void setControlable(bool b);
	virtual Rect getBoundingBox();
	virtual inline void setArmOffsetX(int x){ m_arm_offsetX = x; }
	virtual inline void setArmOffsetY(int y){ m_arm_offsetY = y; }
	void setEndPoint(const Point& p);
	void setHeightLight(bool b);
	Point getEndPoint();
	enum ROLE_STAT{
		ROLE_STAND,
		ROLE_MOVE,
		ROLE_ATTACK,
		ROLE_SKILL,
		ROLE_INJURED,
		ROLE_DIE,
		ROLE_NULL
	};
	ROLE_STAT en_stat;  //当前状态 
	inline ROLE_STAT getRoleStat(){ return en_stat; }
	
	enum ROLE_TYPE{
		ROLE_TYPE_NULL,
		ROLE_TYPE_HERO,
		ROLE_TYPE_MONSTER
	};
	ROLE_TYPE m_type;
	inline ROLE_TYPE getRoleType(){ return m_type; }


	/*血条相关*/
protected:
	void initHpSlider();
	virtual Point getHpSliderPos();

protected:
	/*update相关的*/
	virtual void update(float dt);
	virtual void update_checkHL();
	virtual void update_trace();
	virtual void update_pos();
	virtual void update_attackTarget();
	virtual void update_hp();
	

	/*从RoleProtocol中继承下来的方法*/
public:

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void stand();
	virtual void move();
	virtual void attack();
	virtual void skill();
	virtual void injured(int effect, int damage = 0);
	virtual void die();
	void onBondAnimationFinish(cocostudio::Armature* arm, cocostudio::MovementEventType type, const std::string& name);
public:
	//属性get/set

	//移动速度
	inline int getSpeed(){ return m_speed; }
	inline void setSpeed(int speed){ m_speed = speed; }
	inline int getInitSpeed(){ return m_initSpeed; }
	inline void setInitSpeed(int speed){ m_initSpeed = speed; }

	//攻击速度
	inline double getAtkSpeed(){ return m_atkSpeed; }
	inline void setAtkSpeed(double speed){ m_atkSpeed = speed; }
	inline double getInitAtkSpeed(){ return m_initAtkSpeed; }
	inline void setInitAtkSpeed(double speed){ m_initAtkSpeed = speed; }

	//生命值
	inline int getHp(){ return m_hp; }
	inline void setHp(int hp){ m_hp = hp; }
	inline int getInitHp(){ return m_initHp; }
	inline void setInitHp(int hp){ m_initHp = hp; }

	//攻击距离
	inline int getAttackDistance(){ return m_attackDistance; }
	inline void setAttackDistance(int distance){ m_attackDistance = distance; }
	inline int getInitAttackDistance(){ return m_initAttackDistance; }
	inline void setInitAttackDistance(int distance){ m_initAttackDistance = distance; }

	//攻击力
	inline int getAtk(){ return m_atk; }
	inline void setAtk(int atk){ m_atk = atk; }
	inline int getInitAtk(){ return m_initAtk; }
	inline void setInitAtk(int atk){ m_initAtk = atk; }

	//攻击附加仇恨值
	inline int getAtkHateValue(){ return m_atkHateValue; }
	inline void setAtkHateValue(int value){ m_atkHateValue = value; }

	//防御力
	inline void setDefence(int defence){ m_defence = defence; }
	inline int getDefence(){ return m_defence; }
	inline void setInitDefence(int def){ m_initDefence = def; }
	inline int getInitDefence(){ return m_initDefence; }


	//是不是奶妈
	inline bool isNaima(){ return m_isNaima; }
	inline void setNaima(bool b){ m_isNaima = b; }

	//子弹图片
	std::string getBulletImg();
	void setBulletImg(std::string img);

	//子弹速度
	inline int getBulletSpeed(){ return m_bulletSpeed; }
	inline void setBulletSpeed(int speed){ m_bulletSpeed = speed; }
	inline int getInitBulletSpeed(){ return m_initBulletSpeed; }
	inline void setInitBulletSpeed(int speed){ m_initBulletSpeed = speed; }

	//获取父控件
	inline BattleLayer* getLayer(){ return m_layer; }
protected:
	/*与显示相关的*/
	bool m_controlable;
	cocostudio::Armature* m_arm;
	int m_arm_offsetX;
	int m_arm_offsetY;

	Sprite* m_trace;
	Point m_endPoint;
	bool m_armFaceTo;	//朝向，默认为true，向左
	bool m_isHL;	//是否高亮显示
	Color3B m_defalutColor;
	ControlSlider* m_hpSlider;
	Sprite* m_selectCircle;


public:
	/*外部调用接口*/
	virtual inline void setDesPoint(const Point& p){ m_desPoint = p; }

	virtual void setAttackTarget(BattleCharacter** targetPtr);
	inline BattleCharacter** getAttackTarget(){ return m_attackTargetPtr; }
	//ID
	virtual inline int getId(){ return m_id; }


	//发射子弹
	void sendBullet();

	//跑技能效果（常用于被击中效果）
	void runSkillEffect(int skill_id, int loop = 1);


protected:
	/*与战斗相关的数据*/
	int m_id;   //id  
	BattleCharacter* m_attackTarget;
	BattleCharacter** m_attackTargetPtr;//攻击目标
	Point m_desPoint;//目标位置  


	int m_speed;    //移动速度  
	int m_initSpeed;
	BattleLayer * m_layer;

	int m_attackDistance;	//攻击距离
	int m_initAttackDistance;

	int m_hp;//生命值
	int m_initHp;

	int m_atk;//攻击力
	int m_initAtk;

	int m_defence;//防御力
	int m_initDefence;

	int m_atkHateValue;//攻击附带仇恨

	bool m_isNaima;//是不是奶妈

	std::string m_bulletImg;//子弹

	int m_bulletSpeed;//子弹速度
	int m_initBulletSpeed;

	double m_atkSpeed;//攻击速度
	double m_initAtkSpeed;
};

#endif