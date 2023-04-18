#pragma once

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

#include <stdio.h>
#include <functional>
#include <typeinfo>
#include <map>
#include <typeindex>

namespace CollisionSystem
{
	template<class T>
	class CollisionManager
	{
	private:

		CollisionManager() = delete;
		~CollisionManager() = delete;

		static std::vector<Collider<T>*> _allColliders;

		static std::map<std::pair<const char*, const char*>, bool(*)(Collider<T>*, Collider<T>*, float)> _collisionMap;

		static std::function <void(Collider<T>* colA, Collider<T>* colB)> _onAnyCollisionEvent;

		/// <summary>
		/// Checks if there is a collision between two colliders.
		/// </summary>
		/// <param name="colA">The first collider.</param>
		/// <param name="colB">The second collider.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool CheckCollision(Collider<T>* colA, Collider<T>* colB);

		// <summary>
		/// Checks for collision between two box colliders.
		/// </summary>
		/// <param name="boxA">The first box collider.</param>
		/// <param name="boxB">The second box collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool BoxToBoxCollisionCheck(Collider<T>* boxA, Collider<T>* boxB, float buffer);

		/// <summary>
		/// Checks for collision between two circle colliders.
		/// </summary>
		/// <param name="circleA">The first circle collider.</param>
		/// <param name="circleB">The second circle collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool CircleToCircleCollisionCheck(Collider<T>* circleA, Collider<T>* circleB, float buffer);

		/// <summary>
		/// Checks for collision between a box collider and a circle collider.
		/// </summary>
		/// <param name="box">The box collider.</param>
		/// <param name="circle">The circle collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool BoxToCircleCollisionCheck(Collider<T>* box, Collider<T>* circle, float buffer);

		/// <summary>
		/// Checks for collision between two polygon colliders.
		/// </summary>
		/// <param name="polyA">The first polygon collider.</param>
		/// <param name="polyB">The second polygon collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool PolygonToPolygonCollisionCheck(Collider<T>* polyA, Collider<T>* polyB, float buffer);

		/// <summary>
		/// Checks for collision between a polygon collider and a circle collider.
		/// </summary>
		/// <param name="poly">The polygon collider.</param>
		/// <param name="circle">The circle collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool PolygonToCircleCollisionCheck(Collider<T>* poly, Collider<T>* circle, float buffer);

		/// <summary>
		/// Checks for collision between a polygon collider and a box collider.
		/// </summary>
		/// <param name="poly">The polygon collider.</param>
		/// <param name="box">The box collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool PolygonToBoxCollisionCheck(Collider<T>* poly, Collider<T>* box, float buffer);

		/// <summary>
		/// Separating Axis Theorem (SAT) algorithm to check collision between two convex polygons.
		/// </summary>
		/// <param name="polyAPoints">The vertices of the first polygon.</param>
		/// <param name="polyBPoints">The vertices of the second polygon.</param>
		/// <param name="buffer">The buffer for detecting overlap.</param>
		/// <param name="mtv">The minimum translation vector, representing the direction and magnitude of minimum overlap.</param>
		/// <returns>True if collision is detected, false otherwise.</returns>
		static bool SATPolyToPolyCalculation(std::vector<Vec2> polyAPoints, std::vector<Vec2> polyBPoints, float buffer, Vec2* mtv);

		/// <summary>
		/// Separating Axis Theorem (SAT) algorithm to check collision between a convex polygon and a circle.
		/// </summary>
		/// <param name="polyPoints">The vertices of the polygon.</param>
		/// <param name="circlePos">The position of the circle center.</param>
		/// <param name="circleRadious">The radius of the circle.</param>
		/// <param name="buffer">The buffer for detecting overlap.</param>
		/// <param name="mtv">The minimum translation vector, representing the direction and magnitude of minimum overlap.</param>
		/// <returns>True if collision is detected, false otherwise.</returns>
		static bool SATPolyToCircleCalculation(std::vector<Vec2> polyPoints, Vec2 circlePos, float circleRadious, float buffer, Vec2* mtv);

		/// <summary>
		/// Calculates the squared distance between two points.
		/// </summary>
		/// <param name="x1">The x-coordinate of the first point.</param>
		/// <param name="y1">The y-coordinate of the first point.</param>
		/// <param name="x2">The x-coordinate of the second point.</param>
		/// <param name="y2">The y-coordinate of the second point.</param>
		static double DistanceSquared(int x1, int y1, int x2, int y2);

		// <summary>
		/// Checks if a point is inside a convex polygon using the ray casting algorithm.
		/// </summary>
		/// <param name="polyPoints">The vertices of the polygon.</param>
		/// <param name="point">The point to check.</param>
		/// <returns>True if the point is inside the polygon, false otherwise.</returns>
		static bool PolygonContainsPoint(const std::vector<Vec2>& polyPoints, const Vec2& point);

	public:

		static void Init();

		static void AddCollider(Collider<T>* col);

		static void RemoveCollider(Collider<T>* col);

		/// <summary>
		/// Add a function to be called when any collision is detected.
		/// </summary>
		/// <param name="func">The function to be called. Takes in two colliders that have collided.</param>
		static void AddListener(std::function <void(Collider<T>* colA, Collider<T>* colB)> func);

		/// <summary>
		/// Gets a vector of all the colliders in the scene.
		/// </summary>
		/// <returns>A vector of all the colliders in the scene.</returns>
		inline static std::vector<Collider<T>*> GetAllColliders() { return _allColliders; }

		/// <summary>
		/// This funtion handles all the collision in the game and trigger the collision event
		/// </summary>
		static void HandleAllCollision();

		/// <summary>
		/// This funtion needs to be called at the end of the game to clean up the collision manager
		///  </summary>
		static void CleanUp();
	};
}



