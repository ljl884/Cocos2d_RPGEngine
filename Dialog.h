/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#ifndef _DIALOG_
#define _DIALOG_

#include "cocos2d.h"

using namespace cocos2d;

class Dialog : public Node
{
public:
	Dialog(std::string dialogBarFilename);
	void setVisibility(bool visibility);
	void displayPage(std::string words);
	void display(const std::string words);
	void display(const std::list<std::string> words);
	void setActionFlag(bool isPlayingAction); //when displaying event dialog, set the flag as true, then the dialog will call information center to display next action on the end of displaying
	bool getActionFlag();
	bool nextPage();  // if dialog is over, return true

protected:
	Sprite *dialogBar;
	Label *label;
	std::list<std::string> wordsToBeDisplayed;
	int currentIndex;
	void split(const std::string& src, const std::string& separator, std::vector<std::string>& dest);
	bool isPlayingAction;
};
#endif