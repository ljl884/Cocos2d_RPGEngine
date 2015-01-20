#include "Stage.h"

#define SCROLLING_SPEED 300  

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
std::string Stage::getPositionBridgeId(Point postion)
{
	auto bridgeLayer = map->getLayer(BRIDGE_LAYER);
	Point tileCoord = this->tileCoordForPosition(postion);
	int tileGid = bridgeLayer->getTileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = map->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {
			auto sceneid = properties[PROPERTIE_BRIDGE].asString();
			
			return sceneid;
			
		}
	}
	return "";

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
void Stage::putInMainCharacter(Sprite *character)
{
	mapImg->addChild(character);
	mainCharacter = character;
}

void Stage::scrollToDirectionBy(Direction direction, int distance)
{
	scrollToDirectionBy((float)distance / SCROLLING_SPEED, direction, distance);
}

void Stage::scrollToDirectionBy(float duration, Direction direction, int distance)
{
	float x = 0, y = 0;
	this->getPosition(&x, &y);
	switch (direction)
	{
	case UP:
		scrollTo(duration, ccp(x, y - distance));
		break;
	case DOWN:
		scrollTo(duration, ccp(x, y + distance));
		break;
	case LEFT:
		scrollTo(duration, ccp(x + distance, y));
		break;
	case RIGHT:
		scrollTo(duration, ccp(x - distance, y));
		break;
	default:
		break;
	}
}

void Stage::scrollTo(float duration, Point distination)
{
	CCFiniteTimeAction *actionMove = CCMoveTo::create(duration, distination);
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Stage::scrollOverCallBack, this));
	auto action = Sequence::create(actionMove, callfunc, NULL);
	this->runAction(action);
	//mainCharacter->stopAction(action);
	
}

void Stage::stopScrolling()
{
	isScrolling = false;
	this->stopAllActions();
}
void Stage::scrollOverCallBack(void)
{
	InformationCenter *ic = InformationCenter::getInstance();
	ic->moveOver();
}