#include "Game.h"

#include "CollisionManager.h"

#include "AudioManager.h"

#include "Enemy.h"

#include <iostream>

#include "Engine.h"

Game::Game()
{
	isRunning = false;
	showDebug = false;
	groundTileMap = nullptr;
	layoutTileMap = nullptr;
}

Game::~Game()
{
	std::cout << "cleaning game\n";
	GameObject::DestroyAllGameObjects();
	SDLManager::Clean();
}

void Game::SetUp()
{
	srand((unsigned)time(NULL));
	isRunning = true; // everything inited successfully, start the main loop
}

void Game::LoadLevel()
{
	groundTileMap = new GroundTileMap((Engine::SCREEN_WIDTH / Engine::TILE_SIZE) + 1, (Engine::SCREEN_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Ground Map.txt");
	layoutTileMap = new LayoutTileMap((Engine::SCREEN_WIDTH / Engine::TILE_SIZE) + 1, (Engine::SCREEN_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Layout Map.txt");
	
	//AudioManager::PlayMusic(AssetManager::GetMusic("Level " + std::to_string(1)), true);
}

void Game::ResetGame()
{
	TileMap::Clear();
	GameObject::DestroyAllGameObjects();
}

void Game::RetryGame()
{
	ResetGame();
	LoadLevel();
}

void Game::Quit()
{
	isRunning = false;
}

void Game::ToggleDebug(bool toggle)
{
	showDebug = toggle;
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:	isRunning = false;break;
			default:break;
		}
	}
}

void Game::Update(float deltaTime)
{
	GameObject::UpdateAllActive(deltaTime);

	CollisionManager::HandleAllCollision();

	GameObject::LateUpdateAllActive(deltaTime);
}

void Game::Render()
{
	groundTileMap->DrawMap();

	GameObject::DrawAllActive();
	
	GameObject::ShowAllDebugVisuals();
}