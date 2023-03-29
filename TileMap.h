#pragma once

#include "Vector2.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include <map>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class TileMap
{
private:
	
	static std::vector<TileMap*> tileMaps;
	
protected:
	
	int width;
	int height;
	int tileSize;
	int numTiles;

	std::vector<std::vector<std::string>> tiles;
	
public:
	TileMap(int width, int height, int tileSize, std::string mapPath);
	~TileMap();

	void LoadMap(std::string mapPath);
	virtual void DrawMap() {};
	void SaveMaptoFile(std::string mapPath = "Assets/Maps/MapDefault.txt");

	Vector2 GetTilePositionById(std::string id);

	static void Clear();
};

