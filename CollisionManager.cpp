 #include "CollisionManager.h"

#include <set>


std::function <void(Collider* A, Collider* B)> CollisionManager::OnAnyCollisionEvent = nullptr;

const static int s_buffer = 1;

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
	// Get the world points of both polygons
	std::vector<Vector2> polyAPoints = colA->GetWorldPoints();
	std::vector<Vector2> polyBPoints = colB->GetWorldPoints();

	// Set up unique axes
	std::set<Vector2> uniqueAxes;

	// Get axes from polygon A
	for (int i = 0; i < colA->GetNumPoints(); i++)
	{
		Vector2 edge = polyAPoints[(i + 1) % colA->GetNumPoints()] - polyAPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Get axes from polygon B
	for (int i = 0; i < colB->GetNumPoints(); i++)
	{
		Vector2 edge = polyBPoints[(i + 1) % colB->GetNumPoints()] - polyBPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Check for overlap on each axis
	Vector2 mtv;
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
			float proj = Vector2::Dot(point, axis);
			polyAMin = std::min(polyAMin, proj);
			polyAMax = std::max(polyAMax, proj);
		}

		// Project polygon B onto axis
		for (auto point : polyBPoints)
		{
			float proj = Vector2::Dot(point, axis);
			polyBMin = std::min(polyBMin, proj);
			polyBMax = std::max(polyBMax, proj);
		}

		// Check for overlap
		float dist = std::max(polyBMin - polyAMax, polyAMin - polyBMax);
		if (dist > buffer)
		{
			// If no overlap on this axis, exit early
			return false;
		}
		else if (std::abs(dist) < std::abs(minOverlap))
		{
			// If this axis has the smallest overlap, store the overlap and mtv
			minOverlap = dist;
			mtv = axis * dist;
			if (Vector2::Dot(mtv, polyBPoints[0] - polyAPoints[0]) < 0)
			{
				mtv = -mtv;
			}
		}
	}

	// Create collision objects and add them to the vector
	colA->SetCollisionProperty(colB, mtv, 1);
	colB->SetCollisionProperty(colA, -mtv, 1);
	return true;
}

bool CollisionManager::CircleToCircleCollsionCheck(CircleCollider* colA, CircleCollider* colB, int buffer)
{
	// Get the distance between the two circles
	float distance = Vector2::Distance(colA->GetPosition(), colB->GetPosition());

	// Check for collision
	if (distance <= colA->GetRadius() + colB->GetRadius() + buffer)
	{
		// Calculate the minimum translation vector
		Vector2 mtv = (colB->GetPosition() - colA->GetPosition()).Normalized() * ((colA->GetRadius() + colB->GetRadius() + buffer) - distance);

		// Create collision objects
		colA->SetCollisionProperty(colB, mtv, 1);
		colB->SetCollisionProperty(colA, -mtv, 1);
		return true;
	}

	return  false;
}

bool CollisionManager::BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer)
{
	// Get the world points of the polygon collider
	std::vector<Vector2> polyPoints = box->GetWorldPoints();

	// Get the position of the circle collider in world space
	Vector2 circlePos = circle->GetPosition();

	// Create axes to test against (only need axes perpendicular to the edges of the polygon)
	std::vector<Vector2> axes;
	for (int i = 0; i < box->GetNumPoints(); i++)
	{
		Vector2 edge = polyPoints[(i + 1) % box->GetNumPoints()] - polyPoints[i];
		axes.push_back(Vector2(-edge.y, edge.x).Normalized());
	}

	// Add the axis perpendicular to the line segment connecting the circle center and the closest point on the polygon to the circle center
	float minDist = INFINITY;
	Vector2 closestPointOnPoly = Vector2::Zero();
	for (auto point : polyPoints)
	{
		Vector2 toCircle = circlePos - point;
		float dist = toCircle.Length();
		if (dist < minDist)
		{
			minDist = dist;
			closestPointOnPoly = point;
		}
	}
	axes.push_back((closestPointOnPoly - circlePos).Normalized());

	// Initialize MTV
	Vector2 mtv = Vector2::Zero();
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
			float proj = Vector2::Dot(point, axis);
			polyMin = std::min(polyMin, proj);
			polyMax = std::max(polyMax, proj);
		}

		// Project the circle onto the axis
		float circleCentreProj = Vector2::Dot(circlePos, axis);
		circleMin = circleCentreProj - circle->GetRadius();
		circleMax = circleCentreProj + circle->GetRadius();

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
				mtv = axis * overlap;
				if (Vector2::Dot(mtv, circlePos - closestPointOnPoly) < 0)
				{
					mtv = -mtv;
				}
			}
		}
	}

	// If no separating axis found, the polygon and circle overlap
	box->SetCollisionProperty(circle, mtv, 1);
	circle->SetCollisionProperty(box, mtv, -1);
	return  true;
}

bool CollisionManager::PolygonToPolygonCollisionCheck(PolygonCollider* colA, PolygonCollider* colB, int buffer)
{
	// Get the world points of both polygons
	std::vector<Vector2> polyAPoints = colA->GetWorldPoints();
	std::vector<Vector2> polyBPoints = colB->GetWorldPoints();

	// Set up unique axes
	std::set<Vector2> uniqueAxes;

	// Get axes from polygon A
	for (int i = 0; i < colA->GetNumPoints(); i++)
	{
		Vector2 edge = polyAPoints[(i + 1) % colA->GetNumPoints()] - polyAPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Get axes from polygon B
	for (int i = 0; i < colB->GetNumPoints(); i++)
	{
		Vector2 edge = polyBPoints[(i + 1) % colB->GetNumPoints()] - polyBPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Check for overlap on each axis
	Vector2 mtv;
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
			float proj = Vector2::Dot(point, axis);
			polyAMin = std::min(polyAMin, proj);
			polyAMax = std::max(polyAMax, proj);
		}

		// Project polygon B onto axis
		for (auto point : polyBPoints)
		{
			float proj = Vector2::Dot(point, axis);
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
			mtv = axis * dist;
			if (Vector2::Dot(mtv, polyBPoints[0] - polyAPoints[0]) < 0)
			{
				mtv = -mtv;
			}
		}
	}

	// Create collision objects and add them to the vector
	colA ->SetCollisionProperty(colB, mtv, 1);
	colB ->SetCollisionProperty(colA, -mtv, 1);

	return true;
}

bool CollisionManager::PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer)
{
	// Get the world points of the polygon collider
	std::vector<Vector2> polyPoints = poly->GetWorldPoints();

	// Get the position of the circle collider in world space
	Vector2 circlePos = circle->GetPosition();

	// Create axes to test against (only need axes perpendicular to the edges of the polygon)
	std::vector<Vector2> axes;
	for (int i = 0; i < poly->GetNumPoints(); i++)
	{
		Vector2 edge = polyPoints[(i + 1) % poly->GetNumPoints()] - polyPoints[i];
		axes.push_back(Vector2(-edge.y, edge.x).Normalized());
	}

	// Add the axis perpendicular to the line segment connecting the circle center and the closest point on the polygon to the circle center
	float minDist = INFINITY;
	Vector2 closestPointOnPoly = Vector2::Zero();
	for (auto point : polyPoints)
	{
		Vector2 toCircle = circlePos - point;
		float dist = toCircle.Length();
		if (dist < minDist)
		{
			minDist = dist;
			closestPointOnPoly = point;
		}
	}
	axes.push_back((closestPointOnPoly - circlePos).Normalized());

	// Initialize MTV
	Vector2 mtv = Vector2::Zero();
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
			float proj = Vector2::Dot(point, axis);
			polyMin = std::min(polyMin, proj);
			polyMax = std::max(polyMax, proj);
		}

		// Project the circle onto the axis
		float circleCentreProj = Vector2::Dot(circlePos, axis);
		circleMin = circleCentreProj - circle->GetRadius();
		circleMax = circleCentreProj + circle->GetRadius();

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
				mtv = axis * overlap;
				if (Vector2::Dot(mtv, circlePos - closestPointOnPoly) < 0)
				{
					mtv = -mtv;
				}
			}
		}
	}

	// If no separating axis found, the polygon and circle overlap

	poly->SetCollisionProperty(circle, mtv, 1);
	circle->SetCollisionProperty(poly, mtv, -1);
	return true;
}

bool CollisionManager::PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer)
{
	std::vector<Collision> collisions;

	// Get the world points of both polygons
	std::vector<Vector2> polyAPoints = poly->GetWorldPoints();
	std::vector<Vector2> polyBPoints = box->GetWorldPoints();

	// Set up unique axes
	std::set<Vector2> uniqueAxes;

	// Get axes from polygon A
	for (int i = 0; i < poly->GetNumPoints(); i++)
	{
		Vector2 edge = polyAPoints[(i + 1) % poly->GetNumPoints()] - polyAPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Get axes from polygon B
	for (int i = 0; i < box->GetNumPoints(); i++)
	{
		Vector2 edge = polyBPoints[(i + 1) % box->GetNumPoints()] - polyBPoints[i];
		Vector2 normal = Vector2(-edge.y, edge.x).Normalized();
		uniqueAxes.insert(normal);
	}

	// Check for overlap on each axis
	Vector2 mtv;
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
			float proj = Vector2::Dot(point, axis);
			polyAMin = std::min(polyAMin, proj);
			polyAMax = std::max(polyAMax, proj);
		}

		// Project polygon B onto axis
		for (auto point : polyBPoints)
		{
			float proj = Vector2::Dot(point, axis);
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
			mtv = axis * dist;
			if (Vector2::Dot(mtv, polyBPoints[0] - polyAPoints[0]) < 0)
			{
				mtv = -mtv;
			}
		}
	}

	// Create collision objects and add them to the vector
	Collision collisionB(box, mtv, 1);
	Collision collisionA(poly, -mtv, 1);

	return  true;
}

double CollisionManager::DistanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

bool CollisionManager::PolygonContainsPoint(const std::vector<Vector2>& polyPoints, const Vector2& point)
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