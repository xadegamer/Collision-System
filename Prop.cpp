#include "Prop.h"

Prop::Prop(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger) : GameObject(position)
{
	spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSortingOrder(sortingOrder);
	spriteRenderer->SetSprite(AssetManager::GetSprite(spriteName));

	if (colliderType == ColliderType::BOX)
	{
		collider = new BoxCollider;
		BoxCollider* boxCollider = static_cast<BoxCollider*>(collider);
		boxCollider->SetUp((GameObject*)this, transform->GetPosition(), Vector2(100, 100));

	}
	else if (colliderType == ColliderType::CIRCLE)
	{
		collider = new CircleCollider;
		CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
		circleCollider->SetUp((GameObject*)this,transform->GetPosition(), 50);
	}
	else
	{
		collider = new PolygonCollider;
		PolygonCollider* polygonCollider = static_cast<PolygonCollider*>(collider);

		// Default
		//std::vector<Vector2> points = { Vector2(50,50), Vector2(-20, 120), Vector2(50, 200), Vector2(200, 200), Vector2(200, 50) };

		// MAKE HEXAGON
		//std::vector<Vector2> points = { Vector2(0,0), Vector2(0, 100), Vector2(100, 100), Vector2(100,0) };

		// MAKE TRIANGLE
		//std::vector<Vector2> points = { Vector2(0,0), Vector2(0, 100), Vector2(100, 100) };

		// MAKE SQUARE
		//std::vector<Vector2> points = { Vector2(0,0), Vector2(0, 100), Vector2(100, 100), Vector2(100,0) };

		// MAKE PENTAGON
		//std::vector<Vector2> points = { Vector2(0,0), Vector2(0, 100), Vector2(100, 100), Vector2(100,0), Vector2(50, -50) };

		// MAKE OCTAGON with 8 points and each point is 50 pixels away from the center
		std::vector<Vector2> points;
		for (int i = 0; i < 8; i++)
		{
			float angle = i * 45;
			float x = 100 * cos(angle * M_PI / 180);
			float y = 100 * sin(angle * M_PI / 180);
			points.push_back(Vector2(x, y));
		}

		polygonCollider->SetUp(this, transform->GetPosition(), points);
	}

	if (collider != nullptr)
	{
		collider->SetStatic(isStatic);
		collider->SetTrigger(isTrigger);
	}
}

Prop::~Prop()
{
	
}

void Prop::Update(float deltaTime)
{
	if (collider) collider->UpdatePosition(transform->GetPosition());
	GameObject::Update(deltaTime);
}

void Prop::Draw()
{
	spriteRenderer->Draw(transform->GetPosition());
}
