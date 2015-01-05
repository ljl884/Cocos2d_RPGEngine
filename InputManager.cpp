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
		perform->onArrowButtonPressed(up);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		perform->onArrowButtonPressed(down);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		perform->onArrowButtonPressed(left);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		perform->onArrowButtonPressed(right);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		perform->onActionButtonPressed();
		break;
	default:
		break;
	}
}

void InputManager::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	switch (keycode){
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		perform->onArrowButtonReleased(up);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		perform->onArrowButtonReleased(down);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		perform->onArrowButtonReleased(left);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		perform->onArrowButtonReleased(right);
		break;
	default:
		break;
	}
	
	
	
}