#pragma once
#include <iostream>
#include <vector>

#include "SDLManager.h"
#include "InputManager.h"
#include "Game.h"
#include "TimeManager.h"

class Engine
{
private:

	Engine() = delete;
	~Engine() = delete;

	static const int SCREEN_TICK_PER_FRAME = 16;
	static Game* game;
	static int countedFrames;
	static TimeManager systemTimer;
	static TimeManager deltaTimer;
	
public:
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 960;
	static const int TILE_SIZE = 89;
	static const int P0S_X = 100;
	static const int P0S_Y = 100;
	
	static void Start();
	static void Update();
	static void Render();
	static void FrameCap();
	static Game* GetGame() { return game; }
	inline static TimeManager& GetSystemTimer() { return systemTimer; }
	inline static TimeManager& GetDeltaTimer() { return deltaTimer; }
};

