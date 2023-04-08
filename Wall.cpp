#include "Wall.h"

Wall::Wall(Vector2 position, Vector2 size) : GameObject(position)
{
	tag = Tag::WALL;
	color = Color::GetColor(ColorType::Red);
	boxCollider = new BoxCollider { (GameObject*)this, position, size , true};
}