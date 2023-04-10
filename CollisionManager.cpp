 #include "CollisionManager.h"

#include <set>

namespace CollisionSystem
{

	std::function <void(Collider* A, Collider* B)> CollisionManager::OnAnyCollisionEvent = nullptr;

	const static int s_buffer = 1;

	void CollisionManager::AddListener(std::function<void(Collider* colA, Collider* colB)> func)
	{
		OnAnyCollisionEvent = func;
	}

	void CollisionManager::HandleAllCollision()
	{
		for (int i = 0; i < Collider::GetAllColliders().size(); i++)
		{
			Collider* colliderA = Collider::GetAllColliders()[i];
			for (int j = 0; j < Collider::GetAllColliders().size(); j++)
			{
				Collider* colliderB = Collider::GetAllColliders()[j];
				if (colliderA != colliderB && colliderA->GetIsEnabled() && colliderB->GetIsEnabled())
				{

					if (CollisionManager::CheckCollision(colliderA, colliderB))
					{
						if (OnAnyCollisionEvent != nullptr) OnAnyCollisionEvent(colliderA, colliderB);

						colliderA->OnCollision();
						colliderB->OnCollision();
					}
				}
			}
		}
	}

	bool CollisionManager::CheckCollision(Collider* colA, Collider* colB)
	{
		BoxCollider* boxA = dynamic_cast<BoxCollider*>(colA);
		BoxCollider* boxB = dynamic_cast<BoxCollider*>(colB);

		CircleCollider* circleA = dynamic_cast<CircleCollider*>(colA);
		CircleCollider* circleB = dynamic_cast<CircleCollider*>(colB);

		PolygonCollider* polyA = dynamic_cast<PolygonCollider*>(colA);
		PolygonCollider* polyB = dynamic_cast<PolygonCollider*>(colB);

		if (boxA != nullptr && boxB != nullptr)
		{
			return BoxToBoxCollisionCheck(boxA, boxB, s_buffer);
		}
		else if (circleA != nullptr && circleB != nullptr)
		{
			return CircleToCircleCollsionCheck(circleA, circleB, s_buffer);
		}
		else if (boxA != nullptr && circleB != nullptr)
		{
			return BoxToCircleCollsionCheck(boxA, circleB, s_buffer);
		}
		else if (circleA != nullptr && boxB != nullptr)
		{
			return BoxToCircleCollsionCheck(boxB, circleA, s_buffer);
		}
		else if (polyA != nullptr && polyB != nullptr)
		{
			return PolygonToPolygonCollisionCheck(polyA, polyB, s_buffer);
		}
		else if (polyA != nullptr && circleB != nullptr)
		{
			return PolygonToCircleCollisionCheck(polyA, circleB, s_buffer);
		}
		else if (circleA != nullptr && polyB != nullptr)
		{
			return PolygonToCircleCollisionCheck(polyB, circleA, s_buffer);
		}
		else if (polyA != nullptr && boxB != nullptr)
		{
			return PolygonToBoxCollisionCheck(polyA, boxB, s_buffer);
		}
		else if (boxA != nullptr && polyB != nullptr)
		{
			return PolygonToBoxCollisionCheck(polyB, boxA, s_buffer);
		}
	}

	bool CollisionManager::BoxToBoxCollisionCheck(BoxCollider* colA, BoxCollider* colB, int buffer)
	{
		Vec2 mtv;

		// Get the world points of both polygons
		if (SATPolyToPolyCalculation(colA->GetWorldPoints(), colB->GetWorldPoints(), buffer, &mtv))
		{
			colA->SetCollisionProperty(colB, mtv, 1);
			colB->SetCollisionProperty(colA, -mtv, 1);
			return true;
		}
		return false;
	}

	bool CollisionManager::CircleToCircleCollsionCheck(CircleCollider* colA, CircleCollider* colB, int buffer)
	{
		// Get the distance between the two circles
		float distance = Vec2::Distance(colA->GetPosition(), colB->GetPosition());

		// Check for collision
		if (distance <= colA->GetRadius() + colB->GetRadius() + buffer)
		{
			// Calculate the minimum translation vector
			Vec2 mtv = (colB->GetPosition() - colA->GetPosition()).Normalized() * ((colA->GetRadius() + colB->GetRadius() + buffer) - distance);

			// Create collision objects
			colA->SetCollisionProperty(colB, mtv, 1);
			colB->SetCollisionProperty(colA, -mtv, 1);
			return true;
		}

		return  false;
	}

	bool CollisionManager::BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer)
	{
		Vec2 mtv;

		if (SATPolyToCircleCalculation(box->GetWorldPoints(), circle->GetPosition(), circle->GetRadius(), buffer, &mtv))
		{
			box->SetCollisionProperty(circle, mtv, 1);
			circle->SetCollisionProperty(box, mtv, -1);
			return true;
		}

		return  false;
	}

	bool CollisionManager::PolygonToPolygonCollisionCheck(PolygonCollider* colA, PolygonCollider* colB, int buffer)
	{
		Vec2 mtv;

		// Get the world points of both polygons
		if (SATPolyToPolyCalculation(colA->GetWorldPoints(), colB->GetWorldPoints(), buffer, &mtv))
		{
			colA->SetCollisionProperty(colB, mtv, 1);
			colB->SetCollisionProperty(colA, -mtv, 1);
			return  true;
		}

		return false;
	}

	bool CollisionManager::PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer)
	{
		Vec2 mtv;

		if (SATPolyToCircleCalculation(poly->GetWorldPoints(), circle->GetPosition(), circle->GetRadius(), buffer, &mtv))
		{
			poly->SetCollisionProperty(circle, mtv, 1);
			circle->SetCollisionProperty(poly, mtv, -1);
			return true;
		}

		return false;
	}

	bool CollisionManager::PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer)
	{
		Vec2 mtv;

		// Get the world points of both polygons
		if (SATPolyToPolyCalculation(poly->GetWorldPoints(), box->GetWorldPoints(), buffer, &mtv))
		{
			poly->SetCollisionProperty(box, mtv, 1);
			box->SetCollisionProperty(poly, -mtv, 1);
			return  true;
		}

		return  false;
	}

	bool CollisionManager::SATPolyToPolyCalculation(std::vector<Vec2> polyAPoints, std::vector<Vec2> polyBPoints, int buffer, Vec2* mtv)
	{
		// Get the world points of both polygons

		// Set up unique axes
		std::set<Vec2> uniqueAxes;

		// Get axes from polygon A
		for (int i = 0; i < polyAPoints.size(); i++)
		{
			Vec2 edge = polyAPoints[(i + 1) % polyAPoints.size()] - polyAPoints[i];
			Vec2 normal = Vec2(-edge.y, edge.x).Normalized();
			uniqueAxes.insert(normal);
		}

		// Get axes from polygon B
		for (int i = 0; i < polyBPoints.size(); i++)
		{
			Vec2 edge = polyBPoints[(i + 1) % polyBPoints.size()] - polyBPoints[i];
			Vec2 normal = Vec2(-edge.y, edge.x).Normalized();
			uniqueAxes.insert(normal);
		}

		float minOverlap = INFINITY;
		for (auto axis : uniqueAxes)
		{
			float polyAMin = INFINITY;
			float polyAMax = -INFINITY;
			float polyBMin = INFINITY;
			float polyBMax = -INFINITY;

			// Project polygon A onto axis
			for (auto point : polyAPoints)
			{
				float proj = Vec2::Dot(point, axis);
				polyAMin = std::min(polyAMin, proj);
				polyAMax = std::max(polyAMax, proj);
			}

			// Project polygon B onto axis
			for (auto point : polyBPoints)
			{
				float proj = Vec2::Dot(point, axis);
				polyBMin = std::min(polyBMin, proj);
				polyBMax = std::max(polyBMax, proj);
			}

			// Check for overlap
			float dist = std::max(polyBMin - polyAMax, polyAMin - polyBMax);
			if (dist > buffer)
			{
				// If no overlap on this axis, exit early
				return  false;
			}
			else if (std::abs(dist) < std::abs(minOverlap))
			{
				// If this axis has the smallest overlap, store the overlap and mtv
				minOverlap = dist;
				*mtv = axis * dist;
				if (Vec2::Dot(*mtv, polyBPoints[0] - polyAPoints[0]) < 0)
				{
					*mtv = -*mtv;
				}
			}
		}
		return  true;
	}

	bool CollisionManager::SATPolyToCircleCalculation(std::vector<Vec2> polyPoints, Vec2 circlePos, float circleRadious, int buffer, Vec2* mtv)
	{
		// Create axes to test against (only need axes perpendicular to the edges of the polygon)
		std::vector<Vec2> axes;
		for (int i = 0; i < polyPoints.size(); i++)
		{
			Vec2 edge = polyPoints[(i + 1) % polyPoints.size()] - polyPoints[i];
			axes.push_back(Vec2(-edge.y, edge.x).Normalized());
		}

		// Add the axis perpendicular to the line segment connecting the circle center and the closest point on the polygon to the circle center
		float minDist = INFINITY;
		Vec2 closestPointOnPoly = Vec2::Zero();
		for (auto point : polyPoints)
		{
			Vec2 toCircle = circlePos - point;
			float dist = toCircle.Length();
			if (dist < minDist)
			{
				minDist = dist;
				closestPointOnPoly = point;
			}
		}
		axes.push_back((closestPointOnPoly - circlePos).Normalized());

		float minOverlap = INFINITY;

		// Test for overlap on each axis
		for (auto axis : axes)
		{
			float polyMin = INFINITY;
			float polyMax = -INFINITY;
			float circleMin = INFINITY;
			float circleMax = -INFINITY;

			// Project the polygon onto the axis
			for (auto point : polyPoints)
			{
				float proj = Vec2::Dot(point, axis);
				polyMin = std::min(polyMin, proj);
				polyMax = std::max(polyMax, proj);
			}

			// Project the circle onto the axis
			float circleCentreProj = Vec2::Dot(circlePos, axis);
			circleMin = circleCentreProj - circleRadious;
			circleMax = circleCentreProj + circleRadious;

			// Test for overlap
			float dist = std::max(circleMin - polyMax, polyMin - circleMax);
			if (dist > buffer)
			{
				return  false;
			}
			else
			{
				float overlap = buffer - dist;
				if (overlap < minOverlap)
				{
					minOverlap = overlap;
					*mtv = axis * overlap;
					if (Vec2::Dot(*mtv, circlePos - closestPointOnPoly) < 0)
					{
						*mtv = -*mtv;
					}
				}
			}
		}
		return  true;
	}

	double CollisionManager::DistanceSquared(int x1, int y1, int x2, int y2)
	{
		int deltaX = x2 - x1;
		int deltaY = y2 - y1;
		return deltaX * deltaX + deltaY * deltaY;
	}

	bool CollisionManager::PolygonContainsPoint(const std::vector<Vec2>& polyPoints, const Vec2& point)
	{
		bool contains = false;
		int i, j = polyPoints.size() - 1;
		for (i = 0; i < polyPoints.size(); i++)
		{
			if ((polyPoints[i].y < point.y && polyPoints[j].y >= point.y || polyPoints[j].y < point.y && polyPoints[i].y >= point.y) &&
				(polyPoints[i].x + (point.y - polyPoints[i].y) / (polyPoints[j].y - polyPoints[i].y) * (polyPoints[j].x - polyPoints[i].x) < point.x))
			{
				contains = !contains;
			}
			j = i;
		}
		return contains;
	}

	void CollisionManager::CleanUp()
	{
		OnAnyCollisionEvent = nullptr;

		for (int i = 0; i < Collider::GetAllColliders().size(); i++)
		{
			delete Collider::GetAllColliders()[i];
		}

		Collider::GetAllColliders().clear();
	}

}