#include "Wall.h"

Wall::Wall(Vector2 position, Vector2 size) : GameObject(position)
{
	tag = Tag::WALL;
	color = Color::GetColor(ColorType::Red);

	collider = CollisionManager::RegisterNewCollider<GameObject,BoxCollider>(this, new BoxCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), Vec2(size.x,size.y) , true));
}