#include "Wall.h"

Wall::Wall(Vector2 position, Vector2 size) : GameObject(position)
{
	tag = Tag::WALL;
	color = Color::GetColor(ColorType::Red);
	boxCollider = new BoxCollider { (GameObject*)this,  Vec2(transform->GetPosition().x, transform->GetPosition().y), Vec2(size.x,size.y) , true};
}