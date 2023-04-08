#include "LayoutTileMap.h"

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Prop.h"
#include "Wall.h"

#include "MathUtility.h"
#include "Engine.h"

LayoutTileMap::LayoutTileMap(int width, int height, int tileSize, std::string mapPath) : TileMap(width, height, tileSize, mapPath)
{
	DrawMap();
}

LayoutTileMap::~LayoutTileMap()
{
}

void LayoutTileMap::DrawMap()
{
	Wall* leftWall = new Wall(Vector2(0, 0), Vector2(20, Engine::SCREEN_HEIGHT));
	Wall* rightWall = new Wall(Vector2(Engine::SCREEN_WIDTH - 20, 0), Vector2(20, Engine::SCREEN_HEIGHT));
	Wall* topWall = new Wall(Vector2(0, 0), Vector2(Engine::SCREEN_WIDTH, 20));
	Wall* bottomWall = new Wall(Vector2(0, Engine::SCREEN_HEIGHT - 20), Vector2(Engine::SCREEN_WIDTH, 20));

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Vector2 position = Vector2(x * tileSize, y * tileSize);
			PopulateLevel(tiles[x][y], position);
		}
	}
}

void LayoutTileMap::PopulateLevel(std::string id, Vector2 position)
{
	if (id == enemyID)
	{
		GameObject::Instantiate(new Enemy(position));
	}
	else if (id == staticPropID)
	{
		GameObject::Instantiate(new Prop(position, 1, true));
	}
	else if (id == nonStaticPropID)
	{
		GameObject::Instantiate(new Prop(position, 1, false));
	}
	else if (id == playerID)
	{
		GameObject::Instantiate(new Player(position));
	}
}

