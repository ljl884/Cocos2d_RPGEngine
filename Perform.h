#ifndef _PERFROM_
#define _PERFROM_

#include "cocos2d.h"
#include "Stage.h"
#include "Character.h"

using namespace cocos2d;

class Perform: public CCLayer
{

public:
	void setMainCharacter(Character *mainCharacter);
	void setStage(Stage *_stage);
	void startMovingMainCharacter(Character_Direction direction);
	void stopMovingMainCharacter();
	void stopMovingMainCharacter(Character_Direction direction);
	void initializeMainCharacter(std::string filename);
	void putinMainCharacter(Node *node, CCPoint position);
	void putinCharacter(Node *node, CCPoint position, Character *character);
	void onMovingCallback();
	void activate();
	std::list<Point> getNPCPositionList();
protected:
	Stage *stage;
	Character *mainCharacter;
	std::list<Character*> NPCList;
	std::list<Point> NPCPositionList;
	void updateNPCPositionList();
	


};

#endif//_PERFROM_