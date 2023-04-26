#include "CollsionVisualiser.h"

#include "GameObject.h"

std::map<const char*, void(*)(SDL_Color, Collider*) > CollsionVisualiser::_collisionMap;

void CollsionVisualiser::DrawBoxAtPosition(SDL_Color sdlColor, Collider* collider)
{
	BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider);
	Vec2 position = boxCollider->GetPosition();	// get the position of the collider
	float width = boxCollider->GetWidth();			// get the width of the collider
	float height = boxCollider->GetHeight();			// get the height of the collider
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_Rect visualRect = { position.GetX(), position.GetY(), width, height };
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &visualRect);
}

void CollsionVisualiser::DrawCircleAtPosition(SDL_Color sdlColor, Collider* collider)
{
	CircleCollider* circleCollider = dynamic_cast<CircleCollider*>(collider);
	Vec2 position = circleCollider->GetPosition();	// get the position of the collider
	int radius = circleCollider->GetRadius();			// get the radius of the collider
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	for (int i = 0; i < 360; i++)
	{
		float x = radius * cos(i * 3.14 / 180);
		float y = radius * sin(i * 3.14 / 180);
		SDL_RenderDrawPoint(SDLManager::GetRenderer(), (position.GetX() + x), (position.GetY() + y));
	}
}

void CollsionVisualiser::DrawPolygon(SDL_Color sdlColor, Collider* polygonCollider)
{
	PolygonCollider* polygon = dynamic_cast<PolygonCollider*>(polygonCollider);
	std::vector  _points = polygon->GetWorldPoints();
	int num_points = _points.size();

	SDL_Point* sdlPoints = new SDL_Point[num_points];
	for (int i = 0; i < num_points; i++)
	{
		sdlPoints[i].x = _points[i].GetX();
		sdlPoints[i].y = _points[i].GetY();
	}

	// draw the lines
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
	SDL_RenderDrawLines(SDLManager::GetRenderer(), sdlPoints, num_points);

	// draw a line form the last point to the first point
	SDL_RenderDrawLine(SDLManager::GetRenderer(), sdlPoints[0].x, sdlPoints[0].y, sdlPoints[num_points - 1].x, sdlPoints[num_points - 1].y);
}

void CollsionVisualiser::Initialize()
{
	_collisionMap = 
	{
		{typeid(BoxCollider).name(),  &DrawBoxAtPosition},
		{typeid(CircleCollider).name(), &DrawCircleAtPosition},
		{typeid(PolygonCollider).name(), &DrawPolygon}
	};
}

void CollsionVisualiser::DrawAllColliders()
{
	for (int i = 0; i < CollisionManager::GetAllColliders().size(); i++)
	{
		Collider* colliderA = CollisionManager::GetAllColliders()[i];

		if (!colliderA->GetIsEnabled()) continue;

		SDL_Color colliderColour = colliderA->GetOwnerAs<GameObject>()->GetColor();

		auto collisionFunc = _collisionMap.find({ typeid(*colliderA).name()});
		if (collisionFunc != _collisionMap.end()) 
		{
			collisionFunc->second(colliderColour, colliderA);
		}
	}
}
