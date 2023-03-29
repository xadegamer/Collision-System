#pragma once

#include "TileMap.h"

class GroundTileMap : public TileMap
{
private:
	
	Sprite* grassSprite;

	Sprite* asphaltTopLeftSprite;
	Sprite* asphaltTopCentreSprite;
	Sprite* asphaltTopRightSprite;

	Sprite* asphaltCentreLeftSprite;
	Sprite* asphaltCentreSprite;
	Sprite* asphaltCentreRightSprite;

	Sprite* asphaltBottomLeftSprite;
	Sprite* asphaltBottomCentreSprite;
	Sprite* asphaltBottomRightSprite;
		
public:
	GroundTileMap(int width, int height, int tileSize, std::string mapPath);
	~GroundTileMap();
	
	void DrawMap() override;
	Sprite* GetSprite(std::string id);
};

