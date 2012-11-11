#pragma once
#include "worldobject.h"

class Tree :
	public WorldObject
{
protected:
	float trunkWidth;
	float trunkHeight;
	float topOfTree;
	float branchWidth;

public:
	Tree(void);
	Tree(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ,
		 float tWidth, float tHeight, float bTop, float bWidth, TextureManager *textureMgr);
	
	virtual ~Tree(void);

	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);	// Updates the location of the train
    void Draw(void);		// Draws everything.
};

