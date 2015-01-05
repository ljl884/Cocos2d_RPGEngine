#ifndef  _INPUT_MANAGER_
#define  _INPUT_MANAGER_

#include "cocos2d.h"
#include "Perform.h"

using namespace cocos2d;

class InputManager : public CCLayer{
public:
	InputManager();
	void bindPerformer(Perform *perform);

protected:
	EventListenerKeyboard *keyboardListener;
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	Perform *perform;
};

#endif