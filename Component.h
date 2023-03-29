#pragma once

#include <iostream>

class GameObject;

class Component
{
protected:
	
	GameObject* gameObject;
	bool isEnabled;
	
public:
	
	Component();

	inline GameObject* GetGameObject() { return gameObject; }
	inline void SetGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
	virtual void someFunc();
	
	inline bool GetIsEnabled() { return isEnabled; }
	inline void SetIsEnabled(bool isEnabled) { this->isEnabled = isEnabled; }
};

