#include "InputManager.h"

InputManager::InputManager()
{
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void InputManager::bindPerformer(Perform *_perform)
{
	perform = _perform;
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
	switch (keycode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		perform->startMovingMainCharacter(up);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		perform->startMovingMainCharacter(down);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		perform->startMovingMainCharacter(left);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		perform->startMovingMainCharacter(right);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		//if (status==free)
		perform->activate();
		break;
	default:
		break;
	}
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	switch (keycode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		perform->stopMovingMainCharacter(up);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		perform->stopMovingMainCharacter(down);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		perform->stopMovingMainCharacter(left);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		perform->stopMovingMainCharacter(right);
		break;
	default:
		break;
	}
	
	
	
}