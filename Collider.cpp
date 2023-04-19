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

	template<class T>
	Collision<T> Collider<T>::GetCollision()
	{
		return _collision;
	}

	template<class T>
	Vec2 Collider<T>::GetPosition()
	{
		return _position;
	}

	template<class T>
	T* Collider<T>::GetOwner()
	{
		return _owner;
	}

	template<class T>
	bool Collider<T>::IsTrigger()
	{
		return _isTrigger;
	}

	template<class T>
	void Collider<T>::SetTrigger(bool isTrigger)
	{
		_isTrigger = isTrigger;
	}

	template<class T>
	bool Collider<T>::IsStatic()
	{
		return _isStatic;
	}

	template<class T>
	void Collider<T>::SetStatic(bool isStatic)
	{
		_isStatic = isStatic;
	}

	template<class T>
	bool Collider<T>::GetIsEnabled()
	{
		return _isEnabled;
	}

	template<class T>
	void Collider<T>::SetIsEnabled(bool isEnabled)
	{
		_isEnabled = isEnabled;
	}
}
