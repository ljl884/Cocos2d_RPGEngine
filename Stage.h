#ifndef _STAGE_
#define _STAGE_

#include "cocos2d.h"

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

protected:
	TMXTiledMap *map;
};

#endif