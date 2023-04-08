#include "LayoutTileMap.h"

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Prop.h"

#include "MathUtility.h"

LayoutTileMap::LayoutTileMap(int width, int height, int tileSize, std::string mapPath) : TileMap(width, height, tileSize, mapPath)
{
	DrawMap();
}

LayoutTileMap::~LayoutTileMap()
{
}

void LayoutTileMap::DrawMap()
{
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
	if (id == "E")
	{
		GameObject::Instantiate(new Enemy(position));
	}
	else if (id == "B")
	{
		int barrelType = MathUtility::RandomRange(1, 3);
		GameObject::Instantiate(new Prop(position, ColliderType::CIRCLE, 1, true, false));
	}
	else if (id == "T")
	{
		// random treee 1 - 6
		int treeType = MathUtility::RandomRange(1, 6);
		GameObject::Instantiate(new Prop(position, ColliderType::BOX, 1, true, false));
	}
	else if (id == "C")
	{
		// random car 1 - 2
		int carType = MathUtility::RandomRange(1, 3);
		GameObject::Instantiate(new Prop(position, ColliderType::POLYGON, 1, true, false));
	}
	else if (id == "P")
	{
		GameObject::Instantiate(new Player(position));
	}
}

