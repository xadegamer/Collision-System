#pragma once
#include "Collider.h"

namespace CollisionSystem
{
	class BoxCollider : public Collider
	{
	private:

		Vec2 _size;

	public:

		BoxCollider(void* owner, Vec2 nextPosition, Vec2 size, bool isStatic = false);

		void UpdatePosition(Vec2 nextPosition) override;

		Vec2 GetCenter() override;

		inline int GetWidth() { return _size.GetX(); }

		inline int GetHeight() { return _size.GetY(); }

		inline int GetNumPoints() { return GetWorldPoints().size(); }

		std::vector<Vec2> GetWorldPoints();
	};
}
