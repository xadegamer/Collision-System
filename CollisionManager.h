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

	class CollisionManager
	{
	private:

		CollisionManager() = delete;
		~CollisionManager() = delete;

		/// <summary>
		/// A vector of all registered colliders in the collision system.
		/// </summary>
		static std::vector<Collider*> _allColliders;

		/// <summary>
		/// A map of collision pairs to the corresponding collision function.
		/// </summary>
		static std::map<std::pair<const char*, const char*>, bool(*)(Collider*, Collider*, float)> _collisionMap;

		/// <summary>
		/// An event that is called whenever any two colliders collide.
		/// </summary>
		static std::function <void(Collider* colA, Collider* colB)> _onAnyCollisionEvent;

		/// <summary>
		/// Checks if there is a collision between two colliders.
		/// </summary>
		/// <param name="colA">The first collider.</param>
		/// <param name="colB">The second collider.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool CheckCollision(Collider* colA, Collider* colB);

		// <summary>
		/// Checks for collision between two box colliders.
		/// </summary>
		/// <param name="boxA">The first box collider.</param>
		/// <param name="boxB">The second box collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool BoxToBoxCollisionCheck(Collider* boxA, Collider* boxB, float buffer);

		/// <summary>
		/// Checks for collision between two circle colliders.
		/// </summary>
		/// <param name="circleA">The first circle collider.</param>
		/// <param name="circleB">The second circle collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool CircleToCircleCollisionCheck(Collider* circleA, Collider* circleB, float buffer);

		/// <summary>
		/// Checks for collision between a box collider and a circle collider.
		/// </summary>
		/// <param name="box">The box collider.</param>
		/// <param name="circle">The circle collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool BoxToCircleCollisionCheck(Collider* box, Collider* circle, float buffer);

		/// <summary>
		/// Checks for collision between two polygon colliders.
		/// </summary>
		/// <param name="polyA">The first polygon collider.</param>
		/// <param name="polyB">The second polygon collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool PolygonToPolygonCollisionCheck(Collider* polyA, Collider* polyB, float buffer);

		/// <summary>
		/// Checks for collision between a polygon collider and a circle collider.
		/// </summary>
		/// <param name="poly">The polygon collider.</param>
		/// <param name="circle">The circle collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool PolygonToCircleCollisionCheck(Collider* poly, Collider* circle, float buffer);

		/// <summary>
		/// Checks for collision between a polygon collider and a box collider.
		/// </summary>
		/// <param name="poly">The polygon collider.</param>
		/// <param name="box">The box collider.</param>
		/// <param name="buffer">The buffer size for the collision detection.</param>
		/// <returns>A boolean indicating whether a collision has occurred.</returns>
		static bool PolygonToBoxCollisionCheck(Collider* poly, Collider* box, float buffer);

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

		/// <summary>
		/// Initializes the CollisionManager and sets up the collision map. The collision map is a map of function pointers
		/// for checking different types of collisions between different types of colliders, using std::pair and typeid to
		/// identify the colliders. This function is called only once at the beginning of the program.
		/// </summary>
		static void Init();

		/// <summary>
		/// Adds a collider to the collision detection system.
		/// </summary>
		/// <param name="col">The collider to add</param>
		static void AddCollider(Collider* col);

		/// <summary>
		/// Removes a collider from the collision detection system.
		/// </summary>
		/// <param name="col">The collider to remove</param>
		static void RemoveCollider(Collider* col);

		/// <summary>
		/// Add a function to be called when any collision is detected.
		/// </summary>
		/// <param name="func">The function to be called. Takes in two colliders that have collided.</param>
		static void AddListener(std::function <void(Collider* colA, Collider* colB)> func);

		/// <summary>
		/// Gets a vector of all the colliders in the scene.
		/// </summary>
		/// <returns>A vector of all the colliders in the scene.</returns>
		inline static std::vector<Collider*> GetAllColliders() { return _allColliders; }

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



