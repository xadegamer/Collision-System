#include "SDLManager.h"

SDL_Window* SDLManager::m_pWindow = nullptr;
SDL_Renderer* SDLManager::m_pRenderer = nullptr;

bool SDLManager::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}

		//Initialize PNG loading
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			std::cout << "SDL_image could not initialize!SDL_image Error :" << IMG_GetError();
		}
		else
		{
			//Get window surface
		}

		flags = MIX_INIT_MP3;
		if (Mix_Init(flags) != flags)
		{
			std::cout << "SDL_mixer could not initialize!SDL_mixer Error :" << Mix_GetError();
		}
		else
		{
			//Get window surface
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize!SDL_mixer Error :" << Mix_GetError();
		}

		if (TTF_Init() > 0 )
		{
			std::cout << "SDL_ttf could not initialize!SDL_ttf Error :" << TTF_GetError();
		}	
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	return true;
}

void SDLManager::Clean()
{	
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDLManager::SetCursorVisibility(bool show)
{
	SDL_ShowCursor(show);
}

void SDLManager::CursorBlit(SDL_Texture* texture, int x, int y, bool center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopy(SDLManager::GetRenderer(), texture, NULL, &dest);
}
