#pragma once
#include "worldobject.h"
#include "Utility.h"

class Dragon : public WorldObject{
protected:
	GLuint displayListIndex;
	int numDisplayLists;

public:
	Dragon(void);
	Dragon(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr);
	virtual ~Dragon(void);
	
	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);		// Updates the location of the train
	void Dragon::Draw(void);
};
