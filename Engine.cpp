#include "Engine.h"

#include "CollisionManager.h"

TimeManager Engine::systemTimer;
TimeManager Engine::deltaTimer;
int Engine::countedFrames = 0;
Game* Engine::game = nullptr;
Sprite* Engine::cursor = nullptr;

void Engine::Start()
{
	if (!SDLManager::Init("Wild West Ranger", P0S_X, P0S_Y, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		std::cout << "SDLManager::Init() failed\n";
		return;
	}

	AssetManager::Init();
	
	InputManager::Init();

	cursor = AssetManager::GetSprite("cursor");
		
	game = new Game();

	game->SetUp();
	game->LoadLevel();

	systemTimer.tick();
	deltaTimer.tick();

	while (game->IsRunning())
	{
		deltaTimer.tick();
		
		InputManager::Update();

		Update();
		
		Render();
		
		InputManager::UpdatePreviousInput();

		FrameCap();
	}

	AssetManager::Clear();

	delete game;
	game = nullptr;
}

void Engine::Update()
{
	game->HandleEvents();
	game->Update(deltaTimer.getDeltaTime());
	CollisionManager::HandleAllCollision();
	game->LateUpdate(deltaTimer.getDeltaTime());
}

void Engine::Render()
{
	SDL_RenderClear(SDLManager::GetRenderer());

	game->Render();

	CollisionManager::VisualiseCollision();

	SDLManager::CursorBlit(cursor->texture, InputManager::GetMousePosition().x, InputManager::GetMousePosition().y, true);
	SDL_RenderPresent(SDLManager::GetRenderer());

}

void Engine::FrameCap()
{
	//Calculate and correct fps
	float avgFPS = countedFrames / (systemTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	++countedFrames;

	//If frame finished early
	int frameTicks = deltaTimer.getTicks();
	if (frameTicks < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
	}
	std::string title = "Wild West Ranger [avg fps: " + std::to_string(int(avgFPS)) + "] ";
	SDL_SetWindowTitle(SDLManager::GetWindow(), title.c_str());
}