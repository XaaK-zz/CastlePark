#pragma once
#include <vector>
#include <map>
#include "ManagedTexture.h"

using namespace std;

class TextureManager
{
protected:
	map<const char*, ManagedTexture*> *textureList;

public:
	TextureManager(void);
	~TextureManager(void);

	void Init();

	bool LoadTexture(const char* textureName, const char* filePath);
	bool ActivateTexture(const char* textureName);
};
