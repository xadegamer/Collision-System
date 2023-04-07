#pragma once

#include <iostream>
#include <vector>

#include "Component.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "RigidBody.h"

#include "AssetManager.h"

#include "Vector2.h"
#include "MathUtility.h"

#include "Collider.h"

#include "Collision.h"

enum Tag
{
	DEFAULT,
	PLAYER,
	ENEMY,
	BULLET,
	GAS_CYLINDER,
	COLLECTABLE
};

class GameObject
{

private:
	
	static const int minLayer = static_cast<int>(SortingLayer::CharacterBloodLayer);
	static const int maxlayer = static_cast<int>(SortingLayer::VfxLayer);
	
	bool toBeDestroyed = false;
	float destoryDelay = 1.0f;
	float currentDestoryTime;
	
protected:

	static std::vector<GameObject*> activeGameobjects;

	std::vector<Component*> components;
	Tag tag = Tag::DEFAULT;
	Transform* transform;

	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw() {};
	
public:
	GameObject(Vector2 position = Vector2(0, 0));
	virtual ~GameObject();
	
	inline Transform* GetTransform() { return transform; }
	inline Tag GetTag() { return tag; }
	inline void SetTag(Tag tag) { this->tag = tag; }

	template<class T>
	T* AddComponent(T* newCom)
	{
		Component* newComponent = dynamic_cast<Component*>(newCom);

		if (CheckIfComponentExits(newComponent)) std::cout << "Already Exists" << std::endl;
		newComponent->SetGameObject(this);
		components.push_back(newComponent);
		return newCom;
	}

	template<class T>
	T* GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr) return  component;
		}
	}
	
	template<class T>
	bool TryGetComponent(T*& component)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			component = dynamic_cast<T*>(components[i]);
			if (component != nullptr) return true;
		}
		return false;
	}

	template<class T>
	T* RemoveComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			T* component = dynamic_cast<T*>(components[i]);
			if (component != nullptr)
			{
				components.erase(components.begin() + i);
				return component;
			}
		}
	}

	template<class T>
	static T* Instantiate(T* prefab)
	{
		T* newObject = new T(*prefab);
		return newObject;
	}


	virtual void OnCollisionEnter(Collision collision) {};

	void CheckComponent(Component* newCom);
	
	inline bool CompareTag(Tag tag) { return this->tag == tag; }

	bool CheckIfComponentExits(Component* newComponent);	
	
	inline bool IsToBeDestroyed() { return toBeDestroyed;}

	void ClearObjectFromMemory(GameObject* gameObject);

	inline static std::vector<GameObject*> GetActiveGameobjects() { return activeGameobjects; }
	
	static void UpdateAllActive(float deltaTime);

	static void LateUpdateAllActive(float deltaTime);
	
	static void DrawAllActive();
	
	static void ShowAllDebugVisuals();
	
	static void Destroy(GameObject* gameObject);

	static void DestroyAllGameObjects();	

	static GameObject* FindGameObjectWithTag(Tag tag);
};