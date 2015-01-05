#include "Stage.h"

#define PROPERTIE_BLOCKED "Blocked"
#define BLOCK_LAYER "Block"
#define TRUE "True"


Stage* Stage::create(std::string name){
	auto stage = new Stage();
	stage->bindTMXTiledMap(name);
	return stage;
}
void Stage::bindTMXTiledMap(TMXTiledMap *tmxmap)
{
	map = tmxmap;
	if (NULL != getParent() && NULL != map)
	{
		getParent()->addChild(map);
	}
	
}
void Stage::bindTMXTiledMap(std::string tmxfilename)
{
	auto map = TMXTiledMap::create(tmxfilename);
	bindTMXTiledMap(map);
}

void Stage::initialize()
{
	if (NULL != getParent())
		getParent()->addChild(map);
}

Point Stage::getObjectPosition(std::string objectGroupName, std::string objectName)
{
	TMXObjectGroup *objects = map->objectGroupNamed(objectGroupName);
	auto spawnPoint = objects->getObject(objectName);
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	return ccp(x, y);
}

void Stage::setLayerVisibility(std::string layerName, bool visibility)
{
	if (NULL != map){
		TMXLayer *layer = map->getLayer(layerName);
		if (NULL != layer)
			layer->setVisible(visibility);
	}
		

}

bool Stage::isPositionBlocked(Point position)
{
	auto blockedLayer = map->getLayer(BLOCK_LAYER);
	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = blockedLayer->getTileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = map->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {
			auto blocked = properties[PROPERTIE_BLOCKED].asString();
			if (TRUE == blocked) {
				return true;
			}
		}
	}
	return false;
}

Point Stage::tileCoordForPosition(Point position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Point(x, y);
}

