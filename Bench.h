#pragma once
#include "worldobject.h"

class Bench :
	public WorldObject
{
public:
	Bench(void);
	~Bench(void);

	Bench(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr);

	bool Initialize(void);	// Gets everything set up for drawing.
    
};
