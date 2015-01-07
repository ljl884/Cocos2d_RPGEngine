#include "XMLParser.h"

XMLParser::XMLParser()
{
	NPCScriptUrl = "NPC.xml";
}
void XMLParser::readNPCScript()
{
	auto txt_vec = FileUtils::getInstance()->getValueVectorFromFile(NPCScriptUrl);
	NPCValueVector = txt_vec;
}

std::string XMLParser::getNPCImageUrl(std::string id)
{
	readNPCScript();
	for (auto& e : NPCValueVector)
	{
		auto txt_map = e.asValueMap();
		std::string npcId = txt_map.at("id").asString();
		if (npcId == id)
		{
			return txt_map.at("image").asString();
		}
	}
}