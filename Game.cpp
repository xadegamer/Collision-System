#include "Game.h"

#include <iostream>

#include "Engine.h"

Game::Game()
{
	isRunning = false;
	layoutTileMap = nullptr;

	SetUp();
}

Game::~Game()
{
	// Delete all game objects and tile maps
	TileMap::Clear();
	GameObject::DestroyAllGameObjects();
	SDLManager::Clean();
}

void Game::SetUp()
{
	srand((unsigned)time(NULL));
	isRunning = true; 
	LoadLevel();
}

void Game::LoadLevel()
{
	layoutTileMap = new LayoutTileMap((Engine::SCREEN_WIDTH / Engine::TILE_SIZE) + 1, (Engine::SCREEN_HEIGHT / Engine::TILE_SIZE) + 1, Engine::TILE_SIZE, "Assets/Maps/Layout Map.txt");
}

void Game::Quit()
{
	isRunning = false;
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:Quit() ;break;
			default:break;
		}
	}
}

void Game::Update(float deltaTime)
{
	HandleEvents();

	GameObject::UpdateAllActive(deltaTime);
}

void Game::LateUpdate(float deltaTime)
{
	GameObject::LateUpdateAllActive(deltaTime);
}

void Game::Render()
{

}