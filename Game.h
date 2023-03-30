#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Player.h"
#include "GroundTileMap.h"
#include "LayoutTileMap.h"

#include "SDLManager.h"
#include "AssetManager.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

#include <iostream>

class Game
{
private:

	bool isRunning;
	bool showDebug;
	int maxLevel;	
	GroundTileMap* groundTileMap;
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
	
	void ResetGame();
	
	void RetryGame();
	
	void Quit();
	
	void ToggleDebug(bool toggle);
};

