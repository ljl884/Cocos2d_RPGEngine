#ifndef _XML_PARSER_
#define _XML_PARSER_

#include "cocos2d.h"

using namespace cocos2d;

class XMLParser
{
public:
	XMLParser();
	 Sprite*  initializeCharacter(std::string id);
	 std::string getNPCImageUrl(std::string id);

private:
	std::string NPCScriptUrl;
	void readNPCScript();
	ValueVector NPCValueVector;
};
#endif