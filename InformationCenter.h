#ifndef _IF_
#define _IF_
#include "cocos2d.h"

class Perform;
class InformationCenter
{
private:
	InformationCenter()
	{}
	static InformationCenter *instance;
	Perform *performer;
public:
	static InformationCenter* getInstance()
	{
		if (instance == NULL)
			instance = new InformationCenter();
		return instance;
	}
	void setPerformer(Perform *performer);
	void moveOver();
	bool playAction();
	~InformationCenter();

};



#endif