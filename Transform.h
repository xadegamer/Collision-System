#pragma once

#include "Component.h"
#include "Vector2.h"

class Transform : public Component
{

private:
	Vector2 centre;
	Vector2 position;
	Vector2 scale;
	float rotation;
	
public:
	
	Transform();
	~Transform();
	
	void Translate(Vector2 translation);
	void TranslateX(float x);
	void TranslateY(float y);

	Vector2 GetForward();
	Vector2 GetRight();

	inline Vector2 GetPosition() { return position; }
	inline Vector2 GetScale() { return scale; }
	inline float GetRotation() { return rotation; }
	inline Vector2 GetCentre() { return centre; }
	
	inline void SetPosition(Vector2 position) { this->position = position; }
	inline void SetXPosition(float x) { this->position.x = x; }
	inline void SetYPosition(float y) { this->position.y = y; }
	inline void SetScale(Vector2 scale) { this->scale = scale; }
	inline void SetRotation(float rotation) { this->rotation = rotation; }
	inline void SetCentre(Vector2 centre) { this->centre = centre; };
};

