#ifndef _DIALOG_
#define _DIALOG_

#include "cocos2d.h"

using namespace cocos2d;

class Dialog : public Node
{
public:
	Dialog(std::string dialogBarFilename);
	void setVisibility(bool visibility);
	void display(std::string words);
	void display(const std::list<std::string> words);
	bool nextPage();  // if dialog is over, return true

protected:
	Sprite *dialogBar;
	Label *label;
	std::list<std::string> wordsToBeDisplayed;
	int currentIndex=0;
};
#endif