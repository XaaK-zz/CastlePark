#pragma once

#include "WorldObject.h"
#include <iostream>

typedef struct {
	float x;
	float y;
	float z;
	float u;
	float v;
} Vertex;

class Utility
{
public:
	Utility(void);
	~Utility(void);
	static Vertex* CreateSphere (int space, float subdivisions, float xDisplacement, float yDisplacement, float zDisplacement, int *size);
	static void DrawSphere(Vertex* vertices, int size);
};
