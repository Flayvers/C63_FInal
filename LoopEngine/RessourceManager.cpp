#include <iostream>
#include "raylib.h"
#include "LoopEngine/RessourceManager.h"

using namespace LE;

Texture& LE::RessourceManager::Load(std::string& InPath)
{
	const char* pathChar = InPath.c_str();

	if (_mapLoadedTexture.find(InPath) == _mapLoadedTexture.end())
	{
		_mapLoadedTexture[InPath] = LoadTexture(pathChar);
	}
	return _mapLoadedTexture[InPath];
}

void LE::RessourceManager::UnloadAll()
{
	for (auto& pair : _mapLoadedTexture)
	{
		UnloadTexture(pair.second);
	}
	_mapLoadedTexture.clear();
}
