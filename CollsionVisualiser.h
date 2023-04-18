#pragma once

#include "SDLManager.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Vec2.h"

using namespace CollisionSystem;

class CollsionVisualiser
{
private:

	/// <summary>
	/// Draw a rectangle of the given color at the specified position, with the given width and height.
	/// </summary>
	/// <param name="sdlColor">The color of the rectangle.</param>
	/// <param name="position">The position at which to draw the rectangle.</param>
	/// <param name="width">The width of the rectangle.</param>
	/// <param name="height">The height of the rectangle.</param>
	static void DrawBoxAtPosition(SDL_Color sdlColor, Vec2 position, int width, int height);

	/// <summary>
	/// Draw a circle of the given color at the specified position, with the given radius.
	/// </summary>
	/// <param name="sdlColor">The color of the circle.</param>
	/// <param name="position">The position at which to draw the circle.</param>
	/// <param name="radius">The radius of the circle.</param>
	static void DrawCircleAtPosition(SDL_Color sdlColor, Vec2 position, int radius);

	/// <summary>
	/// Draw a polygon of the given color with the specified points.
	/// </summary>
	/// <param name="sdlColor">The color of the polygon.</param>
	/// <param name="_points">The points that make up the polygon.</param>
	static void DrawPolygon(SDL_Color sdlColor, std::vector<Vec2> _points);

public:

	/// <summary>
	/// Draws all the colliders in the scene.
	/// </summary>
	
	template<class T>
	static void DrawAllColliders();
};

