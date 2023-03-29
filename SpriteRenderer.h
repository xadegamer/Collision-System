#pragma once
#include "Component.h"
#include <string>
#include <map>
#include "SDL.h"
#include "Vector2.h"

#include "SDLManager.h"


struct Sprite
{
public:
	SDL_Texture* texture;
	int textureWidth, textureHeight;

	Sprite(SDL_Texture* texture)
	{
		this->texture = texture;
		SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	}
};

enum SortingLayer
{
	CharacterBloodLayer = 0,
	DeadCharacterLayer = 1,
	CollectableLayer = 2,
	PropsLayer = 3,
	EnemyLayer = 4,
	PlayerLayer = 5,
	TreesLayer = 6,
	VfxLayer = 7,
};

class SpriteRenderer : public Component
{
private:
	Sprite* sprite;
	SDL_Rect destRect;
	int sortingOrder;

public:
	SpriteRenderer();
	~SpriteRenderer();
	
	void someFunc();

	void SetSprite(Sprite* sprite);

	void Draw(Vector2 position, float angle, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Draw(Vector2 position, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Draw(SDL_Rect srcRect, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void CursorBlit(SDL_Texture* texture, int x, int y, bool center);

	static Sprite* CreateSprite(std::string fileName, std::string id);

	Sprite* GetSprite() { return sprite; }

	int GetSortingOrder() { return sortingOrder; }
	void SetSortingOrder(int sortingOrder) { this->sortingOrder = sortingOrder; }

	SDL_Rect& GetRect() { return destRect; }

	void DebugRect();
};

