#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "LayoutTileMap.h"

#include "SDLManager.h"
#include "InputManager.h"

#include <iostream>

class Game
{
private:

	bool isRunning;
	int maxLevel;	
	LayoutTileMap* layoutTileMap;
	
public:

	Game();

	~Game();

	void SetUp();
	
	void Render();
	
	void Update(float deltaTime);

	void LateUpdate(float deltaTime);
	
	void HandleEvents();
	
	bool IsRunning() { return isRunning; }

	void LoadLevel();
	
	void Quit();
};

