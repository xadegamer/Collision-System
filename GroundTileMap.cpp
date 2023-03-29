#include "GroundTileMap.h"

GroundTileMap::GroundTileMap(int width, int height, int tileSize, std::string mapPath) : TileMap(width, height, tileSize, mapPath)
{
	grassSprite = AssetManager::GetSprite("grass");

	asphaltCentreSprite = AssetManager::GetSprite("Asphalt_Centre");
	asphaltCentreLeftSprite = AssetManager::GetSprite("Asphalt_Centre_Left");
	asphaltCentreRightSprite = AssetManager::GetSprite("Asphalt_Centre_Right");

	asphaltTopLeftSprite = AssetManager::GetSprite("Asphalt_Top_Left");
	asphaltTopCentreSprite = AssetManager::GetSprite("Asphalt_Top_Centre");
	asphaltTopRightSprite = AssetManager::GetSprite("Asphalt_Top_Right");

	asphaltBottomLeftSprite = AssetManager::GetSprite("Asphalt_Bottom_Left");
	asphaltBottomCentreSprite = AssetManager::GetSprite("Asphalt_Bottom_Centre");
	asphaltBottomRightSprite = AssetManager::GetSprite("Asphalt_Bottom_Right");
}

GroundTileMap::~GroundTileMap()
{
}

void GroundTileMap::DrawMap()
{
	Sprite* sprite = nullptr;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			sprite = GetSprite(tiles[x][y]);
			SDL_Rect destRect = { x * tileSize, y * tileSize, sprite->textureWidth,	sprite->textureHeight };
			SDL_RenderCopy(SDLManager::GetRenderer(), sprite->texture, NULL, &destRect);
		}
	}
}

Sprite* GroundTileMap::GetSprite(std::string id)
{	
	if (id == "F")
	{
		return grassSprite;
	}
	else if (id == "S")
	{
		return asphaltCentreSprite;
	}
	else if (id == "L")
	{
		return asphaltCentreLeftSprite;
	}
	else if (id == "R")
	{
		return asphaltCentreRightSprite;
	}
	else if (id == "E")
	{
		return asphaltTopLeftSprite;
	}
	else if (id == "T")
	{
		return asphaltTopCentreSprite;
	}
	else if (id == "Y")
	{
		return asphaltTopRightSprite;
	}
	else if (id == "V")
	{
		return asphaltBottomLeftSprite;
	}
	else if (id == "B")
	{
		return asphaltBottomCentreSprite;
	}
	else if (id == "N")
	{
		return asphaltBottomRightSprite;
	}
	else
	{
		return grassSprite;
	}
}
