#pragma once

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include "ManagedTexture.h"
#include "TextureManager.h"
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4

using namespace std;

struct CameraPos {
	float xPos;
	float yPos;
	float zPos;
	float phi;
	float theta;
};

class WorldObject
{
protected:
	GLubyte 	    displayList;	// The display list for the object.
    bool    	    initialized;    // Whether or not we have been initialized.
    float posX, posY, posZ;
	float scaleX, scaleY, scaleZ;
	//vector<ManagedTexture*> *textureList;
	TextureManager *textureMgr;

public:
	WorldObject(void);
	WorldObject(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ,TextureManager *textureMgr);
	~WorldObject(void);
	
    virtual bool Initialize(void);	// Gets everything set up for drawing.
    virtual void Update(float);	// Updates the location of the train
    virtual void Draw(void);		// Draws everything.

	float *computeNormal(float trianglePt1X,float trianglePt1Y,float trianglePt1Z,
					 float trianglePt2X,float trianglePt2Y,float trianglePt2Z,
					 float trianglePt3X,float trianglePt3Y,float trianglePt3Z);
};
