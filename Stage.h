#ifndef _STAGE_
#define _STAGE_

#include "cocos2d.h"

#define PROPERTIE_BLOCKED "Blocked"
#define BLOCK_LAYER "Block"
#define TRUE "True"
#define NPC_COLLISION_WIDTH 20
#define NPC_COLLISION_HIGHT 40

using namespace cocos2d;

class Stage : public Node
{
public:
	static Stage *create(std::string filename);
	void bindTMXTiledMap(TMXTiledMap *tmxmap);
	void bindTMXTiledMap(std::string tmxfilename);
	void initialize();
	Point getObjectPosition(std::string objectGroupName, std::string objectName);
	void setLayerVisibility(std::string layerName, bool visibility);
	Point tileCoordForPosition(Point position);
	bool isPositionBlocked(Point position);
	void setUnavailablePositions(std::list<Point> *unavailablePositions);

protected:
	TMXTiledMap *map;
	std::list<Point> *unavailablePositions;
};

#endif