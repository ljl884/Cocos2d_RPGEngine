/************************************************
Author: Wentao Li
Date:14-4-2015
Description:
*************************************************/
#include"InformationCenter.h"
#include"Perform.h"

InformationCenter* InformationCenter::instance = NULL;

void InformationCenter::setPerformer(Perform *performer)
{
	this->performer = performer;
}

void InformationCenter::moveOver()
{
	performer->onMovingCallback();
}

InformationCenter::~InformationCenter()
{
	delete performer;
}
bool InformationCenter::playAction()
{
	return performer->playAction();
}