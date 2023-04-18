#include "Collider.h"

#include "CollisionManager.h"

namespace CollisionSystem
{
	template<class T>
	Collider<T>::Collider(T* owner, Vec2 position, bool isStatic)
	{
		_currentCollidedObject = nullptr;
		_isEnabled = true;

		CollisionManager::AddCollider(this);

		this->_owner = owner;
		this->_isStatic = isStatic;
	}

	template<class T>
	Collider<T>::~Collider()
	{
		CollisionManager::RemoveCollider(this);
	}

	template<class T>
	void Collider<T>::OnCollision()
	{
		if (_collision.GetColliderHit() == nullptr || !_isEnabled) return;

		if (_OnCollisionEnterEvent != nullptr) _OnCollisionEnterEvent(_collision);
	}

	template<class T>
	void Collider<T>::SetCollisionProperty(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse)
	{
		_collision = { colliderHit , minimumTranslationVector , impulse };
	}

	template<class T>
	void Collider<T>::AddListener(std::function<void(Collision<T> other)> OnCollisionEnterEvent)
	{
		this->_OnCollisionEnterEvent = OnCollisionEnterEvent;
	}

	// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
	void TemporaryFunction()
	{
		Collider<int> TempObj ();
	}
}
