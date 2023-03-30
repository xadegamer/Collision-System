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
		boxCollider->SetUp(transform, Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));

	}
	else if (colliderType == ColliderType::CIRCLE)
	{
		collider = new CircleCollider;
		CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
		circleCollider->SetUp(transform, spriteRenderer->GetSprite()->textureWidth / 2, 1);
	}

		//collider = new PolygonCollider;
		//PolygonCollider* polygonCollider = static_cast<PolygonCollider*>(collider);
		//SDL_Point* points = new SDL_Point[4];
		//points[0] = { 10,20 };
		//points[0] = { 20,20 };
		//points[0] = { 50,10 };
		//points[0] = { 10,10 };
		//polygonCollider->SetUp(transform, points, 4);

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
	if (collider) collider->Update();
	GameObject::Update(deltaTime);
}

void Prop::Draw()
{
	spriteRenderer->Draw(transform->GetPosition());
}
