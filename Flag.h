#pragma once
#include "worldobject.h"

class Flag :
	public WorldObject
{
protected:
	float poleHeight;

public:
	Flag(void);
	Flag(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, float height);
	~Flag(void);

	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);	// Updates the location of the train
};
