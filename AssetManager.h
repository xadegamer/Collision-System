#pragma once
#include <iostream>
#include <map>
#include "SDL.h"
#include "SpriteRenderer.h"

#include "SDLManager.h"

struct Dialog;

class AssetManager
{
private:
	static std::map<std::string, Sprite*> sprites;

	static std::map<std::string, TTF_Font*> fonts;
	
	static std::map<std::string, Mix_Chunk*> sounds;
	
	static std::map<std::string, Mix_Music*> musics;

	static std::map<std::string, Dialog*> dialogs;
	
public:

	static void Init();
	static void Clear();
	
	static Sprite* GetSprite(std::string filename);
	
	static TTF_Font* GetFont(std::string filename, int size);

	static Mix_Chunk* GetSoundEffect(std::string filename);

	static Mix_Music* GetMusic(std::string filename);

private:
	AssetManager() = delete;
	~AssetManager() = delete;
};

