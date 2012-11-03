#pragma once

#include <Fl/gl.h>
#include "WorldObject.h"

#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4


class Wall : public WorldObject {

protected:
	GLuint  texture_obj;    // The object for the grass texture.
    int crenellationDirection;

public:
	Wall(void);
	Wall(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int credDir);
	~Wall(void);

	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);	// Updates the location of the train
    void Draw(void);		// Draws everything.
};
