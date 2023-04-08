#include "Wall.h"

Wall::Wall(Vector2 position, Vector2 size) : GameObject(position)
{
	transform = AddComponent<Transform>(new Transform);
	transform->SetPosition(position);
	boxCollider = new BoxCollider { (GameObject*)this, transform->GetPosition(), size };
}
