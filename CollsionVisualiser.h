#pragma once

#include "SDLManager.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <map>
#include <typeindex>
#include "Vec2.h"

#include "CollisionManager.h"
using namespace CollisionSystem;

class CollsionVisualiser
{
private:

	/// <summary>
	/// A map that maps the type name of a collider to the function that draws it.
	/// </summary>
	static std::map<const char*, void(*)(SDL_Color, Collider*) > _collisionMap;

	/// <summary>
	/// Draws a box collider at its current position using the provided color.
	/// </summary>
	/// <param name="sdlColor">The color used to draw the box collider.</param>
	/// <param name="boxCollider">The box collider to draw.</param>
	static void DrawBoxAtPosition(SDL_Color sdlColor, Collider* boxCollider);

	/// <summary>
	/// Draws a box collider at its current position using the provided color.
	/// </summary>
	/// <param name="sdlColor">The color used to draw the box collider.</param>
	/// <param name="boxCollider">The box collider to draw.</param>
	static void DrawCircleAtPosition(SDL_Color sdlColor, Collider* circleCollider);

	/// <summary>
	/// Draws a polygon collider at its current position using the provided color.
	/// </summary>
	/// <param name="sdlColor">The color used to draw the polygon collider.</param>
	/// <param name="polygonCollider">The polygon collider to draw.</param>
	static void DrawPolygon(SDL_Color sdlColor, Collider* polygonCollider);

public:

	/// <summary>
	/// Initializes the CollisionVisualiser by mapping each collider type to its corresponding drawing function.
	/// </summary>
	static void Initialize();

	/// <summary>
	/// Draws all the colliders in the scene.
	/// </summary>
	static void DrawAllColliders();
};

