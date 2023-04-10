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

	static void DrawBoxAtPosition(SDL_Color sdlColor, Vec2 position, int width, int height);

	static void DrawCircleAtPosition(SDL_Color sdlColor, Vec2 position, int radius);

	static void DrawPolygon(SDL_Color sdlColor, std::vector<Vec2> _points);

public:

	static void DrawAllColliders();
};

