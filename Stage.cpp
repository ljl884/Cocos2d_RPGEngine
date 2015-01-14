#include "Stage.h"




Stage* Stage::create(std::string name,std::string mapImageFilename){
	auto stage = new Stage();
	auto map = TMXTiledMap::create(name);
	stage->map = map;
	stage->addChild(map);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(mapImageFilename);
	auto mapImg = Sprite::createWithTexture(texture);
	Size imageSize = mapImg->getContentSize();
	stage->setContentSize(imageSize);
	mapImg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	stage->bindMapImage(mapImg);
	
	return stage;
}

void Stage::bindMapImage(Sprite *mapImage)
{
	mapImg = mapImage;
	if (NULL != mapImg)
	{
		mapSize = mapImg->getContentSize();
		this->addChild(mapImage);

	}
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

	//NPC Position
	if (NULL != unavailablePositions)
	{
		std::list<Point>::iterator i;
		for (i = unavailablePositions->begin(); i != unavailablePositions->end(); i++)
		{
			Point tempPoint = *i;
			if (fabs(position.x - tempPoint.x) < NPC_COLLISION_WIDTH && fabs(position.y - tempPoint.y) < NPC_COLLISION_HIGHT)
				return true;
				
		}
	}
	//

	return false;
}

Point Stage::tileCoordForPosition(Point position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Point(x, y);
}

void Stage::setUnavailablePositions(std::list<Point> *_unavailablePositions)
{
	unavailablePositions = _unavailablePositions;
}

void Stage::putInCharacter(Sprite *character)
{
	mapImg->addChild(character);
}