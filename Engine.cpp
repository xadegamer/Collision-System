#include "Engine.h"

#include "CollisionManager.h"
#include "CollsionVisualiser.h"
#include "CollisionResolver.h"

TimeManager Engine::systemTimer;
TimeManager Engine::deltaTimer;
int Engine::countedFrames = 0;
Game* Engine::game = nullptr;

void Engine::Start()
{
	if (!SDLManager::Init("Collision System", P0S_X, P0S_Y, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		return;
	}

	InputManager::Init();

	CollisionResolver::Initialize();

	game = new Game();

	game->SetUp();

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

	CollisionResolver::Shutdown();

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

	CollsionVisualiser::DrawAllColliders();

	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 0, 0, 0, 255);

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

	std::string title = "Collision System [avg fps: " + std::to_string(int(avgFPS)) + "] ";
	SDL_SetWindowTitle(SDLManager::GetWindow(), title.c_str());
}