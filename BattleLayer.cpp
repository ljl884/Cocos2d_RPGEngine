#include "BattleLayer.h"
#include"BattleCharacter.h"
#include "BattleHero.h"
#include "BattleMonster.h"
#include "Bullet.h"

bool BattleLayer::init()
{
	this->scheduleUpdate();
	initListener();
	currentControlled = nullptr;
	currentControlledPtr = nullptr;
	return true;
}

void BattleLayer::initListener()
{
	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BattleLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(BattleLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BattleLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void BattleLayer::update(float delta){
	cleanNullPtrInArray();
	updateMyControl();
	refreshLocalZOrder();
	//updateMonster();
	//updateSkill();
	
}

bool BattleLayer::comparePosY(Character_Ptr a, Character_Ptr b){
	return ((*a)->getPositionY() < (*b)->getPositionY());
}

void BattleLayer::cleanNullPtrInArray(){
	auto it = rolesArray.begin();
	while (it != rolesArray.end()){
		if ((**it)->getRoleStat() == BattleCharacter::ROLE_DIE){
			(**it)->removeFromParentAndCleanup(true);
			**it = nullptr;
			it = rolesArray.erase(it);
		}
		else{
			++it;
		}
	}
}
void BattleLayer::updateMyControl(){
	if (currentControlledPtr){
		currentControlled = *currentControlledPtr;
		if (currentControlled)
			currentControlled->setHeightLight(true);
	}
}
void BattleLayer::refreshLocalZOrder(){
	;

	int max_z_order = rolesArray.size();
	if (max_z_order <= 1){
		return;
	}

	//sort(m_rolesArray.begin(),m_rolesArray.end(),bind(&FlightLayer::comparePosY,this,std::placeholders::_1,std::placeholders::_2));

	rolesArray.sort(bind(&BattleLayer::comparePosY, this, std::placeholders::_1, std::placeholders::_2));

	for (auto it = rolesArray.begin(); it != rolesArray.end(); it++){
		(**it)->setLocalZOrder(max_z_order--);
	}
}

bool BattleLayer::onTouchBegan(Touch* touch, Event* event){
	if (rolesArray.size() < 1){
		return false;
	}
	for (auto it = rolesArray.begin(); it != rolesArray.end(); ++it){
		if ((**it)->onTouchBegan(touch, event)){
			currentControlledPtr = *it;
			currentControlled = **it;
			return true;
		}
	}
	currentControlledPtr = nullptr;
	return false;
}

void BattleLayer::onTouchMoved(Touch* touch, Event* event){
	if (currentControlled){
		currentControlled->onTouchMoved(touch, event);
	}
	else{
		return;
	}
}

void BattleLayer::onTouchEnded(Touch* touch, Event* event){
	if (currentControlled){
		currentControlled->onTouchEnded(touch, event);
		Point tp = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (!currentControlled->getBoundingBox().containsPoint(tp)){
			currentControlled->setDesPoint(currentControlled->getEndPoint());
		}
		Character_Ptr temp = currentControlled->getAttackTarget();//原来的攻击目标  
		for (auto it = rolesArray.begin(); it != rolesArray.end(); ++it){
			if ((**it)->getBoundingBox().containsPoint(tp)){
				//攻击原来的人  
				if (**it == currentControlled){
					//如果想要自己攻击自己，变为攻击原本正在攻击的那个人  
					currentControlled->setAttackTarget(temp);
					break;
				}
				currentControlled->setAttackTarget((*it));
				break;

			}
			else{
				currentControlled->setAttackTarget(nullptr);
			}
		}
	}
}

void BattleLayer::initTeam()
{
	BattleHero* hero = BattleHero::create("Hero_Gunner", this);
	hero->setPosition(Point(100,380));
	hero->setDesPoint(Point(200, 380));
	this->addCharacter(hero);
	
	
	BattleCharacter* hero2 = BattleCharacter::create("Monster1", this);
	hero2->setPosition(Point(500, 380));
	hero2->setDesPoint(Point(200, 380));
	this->addCharacter(hero2);


	
}
void BattleLayer::initMonsterDeq(std::deque<MonsterMessage> deq){
	this->m_monsterDeq = deq;
}

void BattleLayer::addCharacter(BattleCharacter* c)
{
	this->addChild(c);
	Character_Ptr temp = (Character_Ptr)malloc(sizeof(BattleCharacter*));
	*temp = c;
	rolesArray.push_back(temp);

}

void BattleLayer::addBullet(BattleCharacter* sender, Character_Ptr targetPtr){
	Bullet* bullet = Bullet::createWithTarget(sender, targetPtr);

	this->addChild(bullet);
}