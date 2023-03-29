#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::someFunc()
{

}

void SpriteRenderer::SetSprite(Sprite* sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::Draw(Vector2 position, float angle, SDL_RendererFlip flip)
{
	//Position in world
	destRect.x = position.x;
	destRect.y = position.y;

	//Size of object
	destRect.w = sprite->textureWidth;
	destRect.h = sprite->textureHeight;

	SDL_RenderCopyEx(SDLManager::GetRenderer(), sprite->texture, NULL, &destRect, angle, NULL, flip);
}

void SpriteRenderer::Draw(Vector2 position, SDL_RendererFlip flip)
{
	destRect.w = sprite->textureWidth;
	destRect.h = sprite->textureHeight;
	destRect.x = position.x;
	destRect.y = position.y;
	
	SDL_RenderCopy(SDLManager::GetRenderer(), sprite->texture, NULL, &destRect);
}

void SpriteRenderer::Draw(SDL_Rect srcRect, SDL_RendererFlip flip)
{
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	destRect.x = srcRect.x;
	destRect.y = srcRect.y;
	SDL_RenderCopy(SDLManager::GetRenderer(), sprite->texture, NULL, &destRect);
}

void SpriteRenderer::CursorBlit(SDL_Texture* texture, int x, int y, bool center)
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

Sprite* SpriteRenderer::CreateSprite(std::string fileName, std::string id)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) return nullptr;
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) return new Sprite(pTexture);
	else return nullptr;
}

void SpriteRenderer::DebugRect()
{
	SDL_SetRenderDrawColor(SDLManager::GetRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(SDLManager::GetRenderer(), &destRect);
}
