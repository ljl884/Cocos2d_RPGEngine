#include "Dialog.h"

#define DIALOG_FONT_SIZE 20
#define DIALOG_FONT "fonts/STXINWEI.ttf"

Dialog::Dialog(std::string dialogBarFilename)
{
	//initialize dialog bar
	dialogBar = CCSprite::create(dialogBarFilename);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float contentSizeWidth = dialogBar->getContentSize().width;
	dialogBar->setScale(2*visibleSize.width / contentSizeWidth);
	dialogBar->setVisible(false);
	this->addChild(dialogBar);

	//initialize label
	label = Label::createWithTTF("Hello", DIALOG_FONT, DIALOG_FONT_SIZE);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(dialogBar->getContentSize().width*0.2,dialogBar->getContentSize().height*0.95));
	label->setVisible(false);
	this->addChild(label);
}

void Dialog::setVisibility(bool visibility)
{
	if (dialogBar == NULL)
		return;
	dialogBar->setVisible(visibility);
	label->setVisible(visibility);
}

void Dialog::display(std::string words)
{
	label->setString(words);
	setVisibility(true);
}

bool Dialog::nextPage()
{
	if (wordsToBeDisplayed.empty())
	{
		setVisibility(false);
		return true;
	}
	else
	{
		display(wordsToBeDisplayed.front());
		wordsToBeDisplayed.pop_front();
		return false;
	}
	
}

void Dialog::display(const std::list<std::string> words)
{
	wordsToBeDisplayed = words;
	nextPage();
	
}