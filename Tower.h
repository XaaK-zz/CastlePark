#pragma once

#include <Fl/gl.h>
#include "WorldObject.h"

class Tower :
	public WorldObject {

protected:
	GLuint  texture_obj;    // The object for the grass texture.
    GLuint  texture_obj2;    // The object for the grass texture.
    
public:
	Tower(void);
	Tower(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ);
	
	~Tower(void);

	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);	// Updates the location of the train
    void Draw(void);		// Draws everything.
};
