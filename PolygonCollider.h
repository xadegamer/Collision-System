#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>

namespace CollisionSystem
{
	class PolygonCollider : public Collider
	{
	private:

		Vec2 _position;
		int _num_points;
		std::vector<Vec2> _points;

	public:

		PolygonCollider(void* owner, Vec2 position, std::vector<Vec2> points, bool isStatic = false);

		void UpdatePosition(Vec2 nextPosition) override;

		Vec2 GetCenter() override;

		inline int GetNumPoints() { return _num_points; }

		inline std::vector<Vec2> GetPoints() { return _points; }

		std::vector<Vec2> GetWorldPoints();
	};
}

