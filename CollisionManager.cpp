 #include "CollisionManager.h"

#include <set>

namespace CollisionSystem
{
	template<class T>
	std::vector<Collider<T>*> CollisionManager<T>::_allColliders = std::vector<Collider<T>*>();

	template<class T>
	std::map<std::pair<const char*, const char*>, bool(*)(Collider<T>*, Collider<T>*, float)> CollisionManager<T>::_collisionMap;

	template<class T>
	std::function <void(Collider<T>* A, Collider<T>* B)> CollisionManager<T>::_onAnyCollisionEvent = nullptr;

	const static float s_buffer = 1;

	template<class T>
	void CollisionManager<T>::AddListener(std::function<void(Collider<T>* colA, Collider<T>* colB)> func)
	{
		_onAnyCollisionEvent = func;
	}

	template<class T>
	void CollisionManager<T>::HandleAllCollision()
	{
		for (int i = 0; i < _allColliders.size(); i++)
		{
			Collider* colliderA = _allColliders[i];
			for (int j = 0; j < _allColliders.size(); j++)
			{
				Collider* colliderB = _allColliders[j];
				if (colliderA != colliderB && colliderA->GetIsEnabled() && colliderB->GetIsEnabled())
				{
					if (CollisionManager::CheckCollision(colliderA, colliderB))
					{
						if (_onAnyCollisionEvent != nullptr) _onAnyCollisionEvent(colliderA, colliderB);

						colliderA->OnCollision();
						colliderB->OnCollision();
					}
				}
			}
		}
	}

	template<class T>
	bool CollisionManager<T>::CheckCollision(Collider<T>* _colA, Collider<T>* _colB)
	{
		auto collisionFunc = _collisionMap.find({ typeid(*_colA).name(), typeid(*_colB).name() });
		if (collisionFunc != _collisionMap.end()) {
			return collisionFunc->second(_colA, _colB, s_buffer);
		}
		else return false;
	}

	template<class T>
	bool CollisionManager<T>::BoxToBoxCollisionCheck(Collider<T>* boxA, Collider<T>* boxB, float buffer)
	{
		Vec2 mtv;

		if (SATPolyToPolyCalculation(((BoxCollider*)boxA)->GetWorldPoints(), ((BoxCollider*)boxB)->GetWorldPoints(), buffer, &mtv))
		{
			boxA->SetCollisionProperty(boxB, mtv, 1);
			boxB->SetCollisionProperty(boxA, -mtv, 1);
			return true;
		}
		return false;
	}

	template<class T>
	bool CollisionManager<T>::CircleToCircleCollisionCheck(Collider<T>* circleA, Collider<T>* circleB, float buffer)
	{
		// Get the distance between the two circles
		float distance = Vec2::Distance(circleA->GetPosition(), circleB->GetPosition());

		// Check for collision
		if (distance <= ((CircleCollider*)circleA)->GetRadius() + ((CircleCollider*)circleB)->GetRadius() + buffer)
		{
			// Calculate the minimum translation vector

			Vec2 mtv = (circleB->GetPosition() - circleA->GetPosition()).Normalized() * (((CircleCollider*)circleA)->GetRadius() + ((CircleCollider*)circleB)->GetRadius() + buffer - distance);

			// Create collision objects
			circleA->SetCollisionProperty(circleB, mtv, 1);
			circleB->SetCollisionProperty(circleA, -mtv, 1);
			return true;
		}

		return  false;
	}

	template<class T>
	bool CollisionManager<T>::BoxToCircleCollisionCheck(Collider<T>* box, Collider<T>* circle, float buffer)
	{
		Vec2 mtv;

		if (SATPolyToCircleCalculation(((BoxCollider*)box)->GetWorldPoints(), ((CircleCollider*)circle)->GetPosition(), ((CircleCollider*)circle)->GetRadius(), buffer, &mtv))
		{
			box->SetCollisionProperty(circle, mtv, 1);
			circle->SetCollisionProperty(box, mtv, -1);
			return true;
		}

		return  false;
	}

	template<class T>
	bool CollisionManager<T>::PolygonToPolygonCollisionCheck(Collider<T>* polyA, Collider<T>* polyB, float buffer)
	{
		Vec2 mtv;

		// Get the world points of both polygons
		if (SATPolyToPolyCalculation(((PolygonCollider*)polyA)->GetWorldPoints(), ((PolygonCollider*)polyB)->GetWorldPoints(), buffer, &mtv))
		{
			polyA->SetCollisionProperty(polyB, mtv, 1);
			polyB->SetCollisionProperty(polyA, -mtv, 1);
			return  true;
		}

		return false;
	}

	template<class T>
	bool CollisionManager<T>::PolygonToCircleCollisionCheck(Collider<T>* poly, Collider<T>* circle, float buffer)
	{
		Vec2 mtv;

		if (SATPolyToCircleCalculation(((PolygonCollider*)poly)->GetWorldPoints(), circle->GetPosition(), ((CircleCollider*)circle)->GetRadius(), buffer, &mtv))
		{
			poly->SetCollisionProperty(circle, mtv, 1);
			circle->SetCollisionProperty(poly, mtv, -1);
			return true;
		}

		return false;
	}

	template<class T>
	bool CollisionManager<T>::PolygonToBoxCollisionCheck(Collider<T>* poly, Collider<T>* box, float buffer)
	{
		Vec2 mtv;

		// Get the world points of both polygons
		if (SATPolyToPolyCalculation(((PolygonCollider*)poly)->GetWorldPoints(), ((BoxCollider*)box)->GetWorldPoints(), buffer, &mtv))
		{
			poly->SetCollisionProperty(box, mtv, 1);
			box->SetCollisionProperty(poly, -mtv, 1);
			return  true;
		}

		return  false;
	}

	template<class T>
	bool CollisionManager<T>::SATPolyToPolyCalculation(std::vector<Vec2> polyAPoints, std::vector<Vec2> polyBPoints, float buffer, Vec2* mtv)
	{
		// Get the world points of both polygons

		// Set up unique axes
		std::set<Vec2> uniqueAxes;

		// Get axes from polygon A
		for (int i = 0; i < polyAPoints.size(); i++)
		{
			Vec2 edge = polyAPoints[(i + 1) % polyAPoints.size()] - polyAPoints[i];
			Vec2 normal = Vec2(-edge.GetY(), edge.GetX()).Normalized();
			uniqueAxes.insert(normal);
		}

		// Get axes from polygon B
		for (int i = 0; i < polyBPoints.size(); i++)
		{
			Vec2 edge = polyBPoints[(i + 1) % polyBPoints.size()] - polyBPoints[i];
			Vec2 normal = Vec2(-edge.GetY(), edge.GetX()).Normalized();
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

	template<class T>
	bool CollisionManager<T>::SATPolyToCircleCalculation(std::vector<Vec2> polyPoints, Vec2 circlePos, float circleRadious, float buffer, Vec2* mtv)
	{
		// Create axes to test against (only need axes perpendicular to the edges of the polygon)
		std::vector<Vec2> axes;
		for (int i = 0; i < polyPoints.size(); i++)
		{
			Vec2 edge = polyPoints[(i + 1) % polyPoints.size()] - polyPoints[i];
			axes.push_back(Vec2(-edge.GetY(), edge.GetX()).Normalized());
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

	template<class T>
	double CollisionManager<T>::DistanceSquared(int x1, int y1, int x2, int y2)
	{
		int deltaX = x2 - x1;
		int deltaY = y2 - y1;
		return deltaX * deltaX + deltaY * deltaY;
	}

	template<class T>
	bool CollisionManager<T>::PolygonContainsPoint(const std::vector<Vec2>& polyPoints, const Vec2& point)
	{
		bool contains = false;
		int i, j = polyPoints.size() - 1;
		for (i = 0; i < polyPoints.size(); i++)
		{
			if ( 
				((polyPoints[i].GetY() > point.GetY()) != (polyPoints[j].GetY() > point.GetY())) &&
				(point.GetX() < (polyPoints[j].GetX() - polyPoints[i].GetX()) * (point.GetY() - polyPoints[i].GetY()) / (polyPoints[j].GetY() - polyPoints[i].GetY()) + polyPoints[i].GetX()) )
			{
				contains = !contains;
			}
			j = i;
		}
		return contains;
	}

	template<class T>
	void CollisionManager<T>::Init()
	{
		_collisionMap = {
			{ { typeid(BoxCollider).name(), typeid(BoxCollider).name()}, BoxToBoxCollisionCheck},
			{ { typeid(CircleCollider).name(), typeid(CircleCollider).name()}, CircleToCircleCollisionCheck },
			{ { typeid(BoxCollider).name(), typeid(CircleCollider).name()}, BoxToCircleCollisionCheck },
			{ { typeid(PolygonCollider).name(), typeid(PolygonCollider).name() }, PolygonToPolygonCollisionCheck },
			{ { typeid(PolygonCollider).name(), typeid(CircleCollider).name() }, PolygonToCircleCollisionCheck },
			{ { typeid(PolygonCollider).name(), typeid(BoxCollider).name() }, PolygonToBoxCollisionCheck }
		};
	}

	template<class T>
	void CollisionManager<T>::AddCollider(Collider<T>* col)
	{
		_allColliders.push_back(col);
	}

	template<class T>
	void CollisionManager<T>::RemoveCollider(Collider<T>* col)
	{
		_allColliders.push_back(col);
		_allColliders.erase(find(_allColliders.begin(), _allColliders.end(), col));
		delete col;
		col = nullptr;
	}

	template<class T>
	void CollisionManager<T>::CleanUp()
	{
		_onAnyCollisionEvent = nullptr;
		for (int i = 0; i < _allColliders.size(); i++)
		{
			delete _allColliders[i];
		}
		_allColliders.clear();
	}
}