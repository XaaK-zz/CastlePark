#pragma once
#include "worldobject.h"

#define GATE_CLOSED 1
#define GATE_OPEN 2
#define GATE_CLOSING 3
#define GATE_OPENING 4

class Gate :
	public WorldObject {

protected:
	GLuint  texture_obj;    
	GLuint  texture_obj2;    
    int gateState;

public:
	Gate(void);
	Gate(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ);
	virtual ~Gate(void);
	
	bool Initialize(void);	// Gets everything set up for drawing.
    void Update(float);	// Updates the location of the train
    void Draw(void);		// Draws everything.
};

