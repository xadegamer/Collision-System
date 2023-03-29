#include "AssetManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::map<std::string, Sprite*> AssetManager::sprites = std::map<std::string, Sprite*>();
std::map<std::string, TTF_Font*> AssetManager::fonts = std::map<std::string, TTF_Font*>();
std::map<std::string, Mix_Chunk*> AssetManager::sounds = std::map<std::string, Mix_Chunk*>();
std::map<std::string, Mix_Music*> AssetManager::musics = std::map<std::string, Mix_Music*>();
std::map<std::string, Dialog*> AssetManager::dialogs = std::map<std::string, Dialog*>();

void AssetManager::Init()
{
}

void AssetManager::Clear()
{
	for (auto tex : sprites)
	{
		if (tex.second->texture != nullptr) SDL_DestroyTexture(tex.second->texture);
	}
	sprites.clear();

	for (auto font : fonts)
	{
		if (font.second != nullptr) TTF_CloseFont(font.second);
	}
	fonts.clear();

	for (auto sound : sounds)
	{
		if (sound.second != nullptr) Mix_FreeChunk(sound.second);
	}
	sounds.clear();

	for (auto music : musics)
	{
		if (music.second != nullptr) Mix_FreeMusic(music.second);
	}
	musics.clear();

	for (auto dialog : dialogs)
	{
		if (dialog.second != nullptr) delete dialog.second;
	}
	dialogs.clear();
}

Sprite* AssetManager::GetSprite(std::string filename)
{
	std::string fullPath = "Assets/Art/" + filename + ".png";

	if (sprites[fullPath] == nullptr)
	{
		SDL_Surface* pTempSurface = IMG_Load(fullPath.c_str());
		if (pTempSurface == 0) 
		{
			std::cout << " Sprite Not Found 1" << std::endl;
			return nullptr;
		}
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(SDLManager::GetRenderer(), pTempSurface);
		SDL_FreeSurface(pTempSurface);
		if (pTexture != 0) sprites[fullPath] = new Sprite(pTexture);
		else
		{
			std::cout << "Sprite Not Found 2" << std::endl;
			return nullptr;
		}
	}

	return 	sprites[fullPath];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
	std::string fullPath = "Assets/Fonts/" + filename + ".ttf";

	if (fonts[fullPath] == nullptr)
	{
		TTF_Font* font = TTF_OpenFont(fullPath.c_str(), size);
		if (font == 0) return nullptr; else return fonts[fullPath] = font;
	}

	return fonts[fullPath];
}

Mix_Chunk* AssetManager::GetSoundEffect(std::string filename)
{
	std::string fullPath = "Assets/Audio/" + filename + ".wav";

	if (sounds[fullPath] == nullptr)
	{
		Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
		if (sound == 0) return nullptr; else return sounds[fullPath] = sound;
	}

	return sounds[fullPath];
}

Mix_Music* AssetManager::GetMusic(std::string filename)
{
	std::string fullPath = "Assets/Audio/" + filename + ".mp3";

	if (musics[fullPath] == nullptr)
	{
		Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
		if (music == 0) return nullptr; else return musics[fullPath] = music;
	}

	return musics[fullPath];
}
