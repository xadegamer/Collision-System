#pragma once

#include <stdio.h>
#include <functional>
#include <iostream>
#include <string>

#include "Collision.h"
#include "Vec2.h"

namespace CollisionSystem
{

	class Collider
	{
	protected:

		static std::vector<Collider*> _allColliders;
		Collision _collision;
		void* _owner;
		Vec2 _position;
		bool _isEnabled;
		bool _isTrigger;
		bool _isStatic;
		Collider* _currentCollidedObject;
		std::function <void(Collision other)> _OnCollisionEnterEvent;

	public:

		Collider(void* owner, Vec2 position, bool isStatic = false);

		~Collider();

		virtual void UpdatePosition(Vec2 position) = 0;

		virtual Vec2 GetCenter() = 0;

		void OnCollision();

		void SetCollisionProperty(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse);

		void AddListener(std::function <void(Collision other)> OnCollisionEnterEvent);

		inline Collision GetCollision() { return _collision; }

		inline Vec2 GetPosition() { return _position; }

		inline void* GetOwner() { return _owner; }

		inline bool IsTrigger() { return _isTrigger; }

		inline void SetTrigger(bool isTrigger) { _isTrigger = isTrigger; }

		inline bool IsStatic() { return _isStatic; }

		inline void SetStatic(bool isStatic) { _isStatic = isStatic; }

		inline bool GetIsEnabled() { return _isEnabled; }

		inline void SetIsEnabled(bool isEnabled) { _isEnabled = isEnabled; }

		inline static std::vector<Collider*> GetAllColliders() { return _allColliders; }
	};
}
