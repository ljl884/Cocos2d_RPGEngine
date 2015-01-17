#ifndef _STAGE_
#define _STAGE_

#include "cocos2d.h"
#include "InformationCenter.h"

#define PROPERTIE_BLOCKED "Blocked"
#define BLOCK_LAYER "Block"
#define TRUE "True"
#define NPC_COLLISION_WIDTH 20
#define NPC_COLLISION_HIGHT 40

using namespace cocos2d;

enum  Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

class Stage : public Node
{
public:
	static Stage *create(std::string tmxFilename, std::string mapImageFilename);
	void bindTMXTiledMap(TMXTiledMap *tmxmap);
	void bindTMXTiledMap(std::string tmxfilename);
	void Stage::bindMapImage(Sprite *mapImage);
	void initialize();
	Point getObjectPosition(std::string objectGroupName, std::string objectName);
	void setLayerVisibility(std::string layerName, bool visibility);
	Point tileCoordForPosition(Point position);
	bool isPositionBlocked(Point position);
	void setUnavailablePositions(std::list<Point> *unavailablePositions);
	void putInCharacter(Sprite * character);
	void putInMainCharacter(Sprite * character);
	void scrollToDirectionBy(Direction direction, int distance);
	void scrollToDirectionBy(float duration, Direction direction, int distance);
	void scrollTo(float duration, Point distination);
	void stopScrolling();
	void Stage::scrollOverCallBack(void);
	bool isScrolling=false;

protected:
	Node background;
	TMXTiledMap *map;
	Sprite *mapImg;
	std::list<Point> *unavailablePositions;
	Size mapSize;
	Sprite *mainCharacter;
};

#endif