#pragma once

#include <Fl/gl.h>

class WorldObject
{
protected:
	GLubyte 	    displayList;	// The display list for the object.
    bool    	    initialized;    // Whether or not we have been initialized.
    float posX, posY, posZ;
	float scaleX, scaleY, scaleZ;

public:
	WorldObject(void);
	WorldObject(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ);
	~WorldObject(void);
	
    virtual bool Initialize(void);	// Gets everything set up for drawing.
    virtual void Update(float);	// Updates the location of the train
    virtual void Draw(void);		// Draws everything.
};
