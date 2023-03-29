#pragma once

#define _INPUTMANAGER
#include "SDLManager.h"
#include "Vector2.h"

class InputManager
{
private:	
	static Uint8* previousKeyboardState;
	static const Uint8* currentKeyboardState;
	static int keyLength;

	static Uint32 previousMouseState;
	static Uint32 currentMouseState;
	
	static int mouseX;
	static int mouseY;

	InputManager() = delete;
	~InputManager() = delete;
	
public:
	enum MOUSE_BUTTON { LEFT = 0, MIDDLE = 1, RIGHT = 2, BACK = 3, FORWARD = 4 };

	static void Init();

	static void Close();

	static bool GetKeyDown(SDL_Scancode key);
	static bool GetKey(SDL_Scancode key);
	static bool GetKeyUp(SDL_Scancode key);

	static bool GetMouseButtonDown(MOUSE_BUTTON button);
	static bool GetMouseButton(MOUSE_BUTTON button);
	static bool GetMouseButtonUp(MOUSE_BUTTON button);
	
	static Vector2 GetMousePosition();
	
	static void Update();
	static void UpdatePreviousInput();
};

