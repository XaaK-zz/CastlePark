#pragma once
#include "worldobject.h"

class Bench :
	public WorldObject
{
protected:
	int woodType;
	float rotateAngle;
	bool hideLegs;

public:
	Bench(void);
	~Bench(void);

	Bench(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, float rotateAngle,
		int woodType, TextureManager *textureMgr);

	bool Initialize(void);	// Gets everything set up for drawing.
    void Draw(void);
	void HideLegs();
};
