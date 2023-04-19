#pragma once

#include <stdio.h>
#include <functional>
#include <iostream>
#include <string>

#include "Collision.h"
#include "Vec2.h"

namespace CollisionSystem
{
	template <class T>
	class Collider
	{

	protected:

		Collision<T> _collision;
		T* _owner;
		Vec2 _position;
		bool _isEnabled;
		bool _isTrigger;
		bool _isStatic;
		Collider<T>* _currentCollidedObject;
		std::function <void(Collision<T> other)> _OnCollisionEnterEvent;

	public:

		/// <summary>
		/// This is the constructor for the Collider class. It initializes the owner of the Collider, its position, and whether it is a static object or not.
		/// </summary>
		/// <param name="owner">A void pointer to the object that owns this Collider.</param>
		/// <param name="position">The position of the Collider.</param>
		/// <param name="isStatic">Whether the Collider is static or not. Defaults to false.</param>
		Collider(T* owner, Vec2 position, bool isStatic = false)
		{
			_currentCollidedObject = nullptr;
			_isEnabled = true;

			CollisionManager::AddCollider(this);

			this->_owner = owner;
			this->_isStatic = isStatic;
		}

		/// <summary>
		/// This pure virtual function is used to update the position of the Collider in the game world.
		/// </summary>
		/// <param name="position">The new position of the Collider.</param>
		virtual void UpdatePosition(Vec2 position) = 0;

		/// <summary>
		/// This pure virtual function is used to get the center position of the Collider.
		/// </summary>
		/// <returns>The center position of the Collider.</returns>
		virtual Vec2 GetCenter() = 0;

		/// <summary>
		/// This function is called when a collision occurs.
		/// </summary>
		void OnCollision()
		{
			if (_collision.GetColliderHit() == nullptr || !_isEnabled) return;
			if (_OnCollisionEnterEvent != nullptr) _OnCollisionEnterEvent(_collision);
		}

		/// <summary>
		/// This function sets the properties of a collision, such as the collider that was hit, the minimum translation vector and the impulse.
		/// </summary>
		/// <param name="colliderHit">The collider that was hit.</param>
		/// <param name="minimumTranslationVector">The minimum translation vector needed to resolve the collision.</param>
		/// <param name="impulse">The impulse of the collision.</param>
		void SetCollisionProperty(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse)
		{
			_collision = { colliderHit , minimumTranslationVector , impulse };
		}

		/// <summary>
		/// This function adds a listener to the Collider that will be called when a collision occurs.
		/// </summary>
		/// <param name="OnCollisionEnterEvent">The function to call when a collision occurs.</param>
		void AddListener(std::function <void(Collision<T> other)> OnCollisionEnterEvent)
		{
			_OnCollisionEnterEvent = OnCollisionEnterEvent;
		}

		/// <summary>
		/// This function returns the Collision object associated with the Collider.
		/// </summary>
		/// <returns>The Collision object associated with the Collider.</returns>
		Collision<T> GetCollision()
		{
			return _collision;
		}

		/// <summary>
		/// This function returns the position of the Collider.
		/// </summary>
		/// <returns>The position of the Collider.</returns>
		Vec2 GetPosition()
		{
			return _position;
		}

		/// <summary>
		/// This function returns the owner of the Collider.
		/// </summary>
		/// <returns>A void pointer to the object that owns this Collider.</returns>
		T* GetOwner();

		/// <summary>
		/// This function returns whether the Collider is a trigger or not.
		/// </summary>
		/// <returns>True if the Collider is a trigger, false otherwise.</returns>
		bool IsTrigger();

		/// <summary>
		/// This function sets whether the Collider is a trigger or not.
		/// </summary>
		/// <param name="isTrigger">Whether the Collider is a trigger or not.</param>
		void SetTrigger(bool isTrigger);

		/// <summary>
		/// This function returns whether the Collider is static or not.
		/// </summary>
		/// <returns>True if the Collider is static, false otherwise.</returns>
		bool IsStatic();

		/// <summary>
		/// This function sets whether the Collider is static or not.
		/// </summary>
		/// <param name="isStatic">Whether the Collider is static or not.</param>
		void SetStatic(bool isStatic);

		/// <summary>
		/// Gets whether this collider is currently enabled.
		/// </summary>
		/// <returns>A boolean indicating whether this collider is currently enabled.</returns>
		bool GetIsEnabled();

		/// <summary>
		/// Sets whether this collider is enabled.
		/// </summary>
		/// <param name="isEnabled">A boolean indicating whether this collider should be enabled or not.</param>
		void SetIsEnabled(bool isEnabled);
	};
}