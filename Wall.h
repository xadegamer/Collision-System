#pragma once

#include "GameObject.h"`
#include "BoxCollider.h"

class Wall : public GameObject
{
protected:

	BoxCollider* boxCollider;

public:

	Wall(Vector2 position, Vector2 size);
};

