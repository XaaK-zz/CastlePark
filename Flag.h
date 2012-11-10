#pragma once
#include "worldobject.h"

class Flag :
	public WorldObject
{
protected:
	float poleHeight;
	float flagHeight;
	float flagLength;

public:
	Flag(void);
	Flag(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, float height, float flagHeight, float flagLength);
	~Flag(void);

	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);	// Updates the location of the train
};
