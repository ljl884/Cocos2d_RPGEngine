/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include "Dialog.h"
#include"Config.h"

//#define DIALOG_FONT_SIZE 20
//#define DIALOG_FONT "fonts/STXINWEI.ttf"

Dialog::Dialog(std::string dialogBarFilename)
{
	currentIndex = 0
	this->isPlayingAction = false;
	//initialize dialog bar
	dialogBar = CCSprite::create(dialogBarFilename);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float contentSizeWidth = dialogBar->getContentSize().width;
	dialogBar->setScale(2*visibleSize.width / contentSizeWidth);
	dialogBar->setVisible(false);
	this->addChild(dialogBar);

	//Head img
	//Sprite* head = CCSprite::create("POI.png");
	//head->setPosition(100, 100);
	//this->addChild(head);

	//initialize label
	label = Label::createWithTTF("Hello", Config::DIALOG_FONT, Config::DIALOG_FONT_SIZE);
	label->setAlignment(TextHAlignment::LEFT);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(dialogBar->getContentSize().width*0.6,dialogBar->getContentSize().height*0.95));
	label->setVisible(false);
	this->addChild(label);
}
void Dialog::setActionFlag(bool isPlayingAction)
{
	this->isPlayingAction = isPlayingAction;
}
bool Dialog::getActionFlag()
{
	return this->isPlayingAction;
}
void Dialog::setVisibility(bool visibility)
{
	if (dialogBar == NULL)
		return;
	dialogBar->setVisible(visibility);
	label->setVisible(visibility);
}

void Dialog::displayPage(std::string words)
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
		displayPage(wordsToBeDisplayed.front());
		wordsToBeDisplayed.pop_front();
		return false;
	}
	
}

void Dialog::display(const std::list<std::string> words)
{
	wordsToBeDisplayed = words;
	nextPage();
	
}
void Dialog::display(const std::string words)
{
	std::vector<std::string> strings;
	std::list<std::string> splitedWords;
	split(words, "#", strings); //split text in script by "#"
	std::copy(strings.begin(), strings.end(), std::back_inserter(splitedWords)); //copy the vector to the list container
	display(splitedWords);
}
void Dialog::split(const std::string& src, const std::string& separator, std::vector<std::string>& dest)
{
	std::string str = src;
	std::string substring;
	std::string::size_type start = 0, index;

	do
	{
		index = str.find_first_of(separator, start);
		if (index != std::string::npos)
		{
			substring = str.substr(start, index - start);
			dest.push_back(substring);
			start = str.find_first_not_of(separator, index);
			if (start == std::string::npos) return;
		}
	} while (index != std::string::npos);

	//the last token
	substring = str.substr(start);
	dest.push_back(substring);
}