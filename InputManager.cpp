#include "InputManager.h"


Uint8* InputManager::previousKeyboardState = nullptr;
const Uint8* InputManager::currentKeyboardState = nullptr;
int InputManager::keyLength = 0;

Uint32 InputManager::previousMouseState = 0;
Uint32 InputManager::currentMouseState = 0;

int InputManager::mouseX = 0;
int InputManager::mouseY = 0;

void InputManager::Init()
{
	currentKeyboardState = SDL_GetKeyboardState(&keyLength);
	previousKeyboardState = new Uint8[keyLength];
	memcpy(previousKeyboardState, currentKeyboardState, keyLength);
}

void InputManager::Close()
{
	delete[] previousKeyboardState;
	previousKeyboardState = nullptr;
}

bool InputManager::GetKey(SDL_Scancode key)
{
	return currentKeyboardState[key];
}

bool InputManager::GetKeyDown(SDL_Scancode key)
{
	return !previousKeyboardState[key] && currentKeyboardState[key];
}

bool InputManager::GetKeyUp(SDL_Scancode key)
{
	return previousKeyboardState[key] && !currentKeyboardState[key];
}

bool InputManager::GetMouseButton(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case InputManager::LEFT:mask = SDL_BUTTON_LMASK; break;
	case InputManager::MIDDLE:mask = SDL_BUTTON_MMASK; break;
	case InputManager::RIGHT:mask = SDL_BUTTON_RMASK; break;
	case InputManager::BACK:mask = SDL_BUTTON_X1MASK; break;
	case InputManager::FORWARD:mask = SDL_BUTTON_X2MASK; break;
	}

	return (currentMouseState & mask);
}

bool InputManager::GetMouseButtonDown(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case InputManager::LEFT:mask = SDL_BUTTON_LMASK; break;
	case InputManager::MIDDLE:mask = SDL_BUTTON_MMASK; break;
	case InputManager::RIGHT:mask = SDL_BUTTON_RMASK; break;
	case InputManager::BACK:mask = SDL_BUTTON_X1MASK; break;
	case InputManager::FORWARD:mask = SDL_BUTTON_X2MASK; break;
	}

	return !(previousMouseState & mask) && (currentMouseState & mask);
}

bool InputManager::GetMouseButtonUp(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case InputManager::LEFT:mask = SDL_BUTTON_LMASK; break;
	case InputManager::MIDDLE:mask = SDL_BUTTON_MMASK; break;
	case InputManager::RIGHT:mask = SDL_BUTTON_RMASK; break;
	case InputManager::BACK:mask = SDL_BUTTON_X1MASK; break;
	case InputManager::FORWARD:mask = SDL_BUTTON_X2MASK; break;
	}

	return (previousMouseState & mask) && !(currentMouseState & mask);
}


Vector2 InputManager::GetMousePosition()
{
	return Vector2{ (float)mouseX, (float)mouseY };
}

void InputManager::Update()
{
	currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

void InputManager::UpdatePreviousInput()
{
	memcpy(previousKeyboardState, currentKeyboardState, keyLength);
	previousMouseState = currentMouseState;
}