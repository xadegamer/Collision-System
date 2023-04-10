#pragma once

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

#include <stdio.h>
#include <functional>

namespace CollisionSystem
{
	class CollisionManager
	{
	private:

		CollisionManager() = delete;
		~CollisionManager() = delete;

		static std::function <void(Collider* colA, Collider* colB)> _onAnyCollisionEvent;

		/// <summary>
		/// This funtion checks the collider type and calls the correct collision check function
		/// </summary>
		/// <param name="_colA"></param>
		/// <param name="_colB"></param>
		/// <returns></returns>
		static bool CheckCollision(Collider* colA, Collider* colB);

		static bool BoxToBoxCollisionCheck(BoxCollider* boxA, BoxCollider* boxB, int buffer);

		static bool CircleToCircleCollsionCheck(CircleCollider* circleA, CircleCollider* circleB, int buffer);

		static bool BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer);

		static bool PolygonToPolygonCollisionCheck(PolygonCollider* polyA, PolygonCollider* polyB, int buffer);

		static bool PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer);

		static bool PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer);

		/// <summary>
		/// This funtion will calculate collision between a polygon and a polygon using the Separating Axis Theorem and return the minimum translation vector which is used for collision resolution
		/// </summary>
		/// <param name="polyAPoints"></param>
		/// <param name="polyBPoints"></param>
		/// <param name="buffer"></param>
		/// <param name="mtv"></param>
		/// <returns></returns>
		static bool SATPolyToPolyCalculation(std::vector<Vec2> A, std::vector<Vec2> B, int buffer, Vec2* mtv);

		/// <summary>
		/// This funtion will calculate collision between a polygon and a circle using the Separating Axis Theorem and return the minimum translation vector which is used for collision resolution
		/// </summary>
		static bool SATPolyToCircleCalculation(std::vector<Vec2> polyPoints, Vec2 circlePos, float circleRadious, int buffer, Vec2* mtv);

		static double DistanceSquared(int x1, int y1, int x2, int y2);

		static bool PolygonContainsPoint(const std::vector<Vec2>& polyPoints, const Vec2& point);

	public:

		/// <summary>
		/// This funtion is used to add a listener to the collision manager, this is triggered when any collision is detected
		/// </summary>
		/// <param name="func"></param>
		static void AddListener(std::function <void(Collider* colA, Collider* colB)> func);

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



