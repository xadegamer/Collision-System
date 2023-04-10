#include "Collider.h"

namespace CollisionSystem
{
	std::vector<Collider*> Collider::_allColliders = std::vector<Collider*>();

	Collider::Collider(void* owner, Vec2 nextPosition, bool isStatic)
	{
		_currentCollidedObject = nullptr;
		_allColliders.push_back(this);
		_isEnabled = true;

		this->_owner = owner;
		this->_isStatic = isStatic;
	}

	Collider::~Collider()
	{
		for (int i = 0; i < _allColliders.size(); i++)
		{
			if (_allColliders[i] == this)
			{
				_allColliders.erase(_allColliders.begin() + i);
				break;
			}
		}
	}

	void Collider::OnCollision()
	{
		if (_collision.GetColliderHit() == nullptr || !_isEnabled) return;

		if (_OnCollisionEnterEvent != nullptr) _OnCollisionEnterEvent(_collision);
	}

	void Collider::SetCollisionProperty(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse)
	{
		_collision = { colliderHit , minimumTranslationVector , impulse };
	}

	void Collider::AddListener(std::function<void(Collision other)> OnCollisionEnterEvent)
	{
		this->_OnCollisionEnterEvent = OnCollisionEnterEvent;
	}
}
