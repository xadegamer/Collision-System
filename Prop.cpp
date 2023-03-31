#include "Prop.h"

Prop::Prop(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger) : GameObject(position)
{
	spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer);
	spriteRenderer->SetSortingOrder(sortingOrder);
	spriteRenderer->SetSprite(AssetManager::GetSprite(spriteName));

	//if (colliderType == ColliderType::BOX)
	//{
	//	collider = new BoxCollider;
	//	BoxCollider* boxCollider = static_cast<BoxCollider*>(collider);
	//	boxCollider->SetUp(transform, Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));

	//}
	//else if (colliderType == ColliderType::CIRCLE)
	//{
	//	collider = new CircleCollider;
	//	CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
	//	circleCollider->SetUp(transform, spriteRenderer->GetSprite()->textureWidth / 2, 1);
	//}

		collider = new PolygonCollider;
		PolygonCollider* polygonCollider = static_cast<PolygonCollider*>(collider);
		std::vector<Vector2> points = { Vector2(50,50), Vector2(-150, 150), Vector2(50, 200), Vector2(200, 200), Vector2(200, 50) };

		polygonCollider->SetUp(this,transform->GetPosition(), points);

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
