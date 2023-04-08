#pragma once

#include "TileMap.h"

class LayoutTileMap : public TileMap
{	

private:

	const std::string playerID = "P";
	const std::string enemyID = "E";
	const std::string staticPropID = "S";
	const std::string nonStaticPropID = "N";

public:
	
	LayoutTileMap(int width, int height, int tileSize, std::string mapPath);
	~LayoutTileMap();

	void DrawMap() override;
	void PopulateLevel(std::string id, Vector2 position);
};
