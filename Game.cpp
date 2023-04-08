#include "Game.h"

#include <iostream>

#include "Engine.h"

#include "Wall.h"

Game::Game()
{
	isRunning = false;
	layoutTileMap = nullptr;
}

Game::~Game()
{
	std::cout << "cleaning game\n";
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

	Wall* leftWall =  new Wall(Vector2(0, 0), Vector2(20, Engine::SCREEN_HEIGHT));
	Wall* rightWall =  new Wall(Vector2(Engine::SCREEN_WIDTH - 20, 0), Vector2(20, Engine::SCREEN_HEIGHT));
	Wall* topWall = new Wall(Vector2(0, 0), Vector2(Engine::SCREEN_WIDTH, 20));
	Wall* bottomWall = new Wall(Vector2(0, Engine::SCREEN_HEIGHT - 20), Vector2(Engine::SCREEN_WIDTH, 20));
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