#pragma once
#include "Collider.h"

namespace CollisionSystem
{
	class CircleCollider : public Collider
	{
	private:

		float _radius;

	public:

		CircleCollider(void* owner, Vec2 nextPosition, float radius, float radiousMutiplier = 1, bool isStatic = false);

		void UpdatePosition(Vec2 nextPosition) override;

		Vec2 GetCenter() override;

		inline float GetRadius() { return _radius; };
	};
}
