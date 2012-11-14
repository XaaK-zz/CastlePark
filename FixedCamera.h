#pragma once

#include <vector>
#include "WorldObject.h"

using namespace std;


class FixedCamera
{
protected:
	vector<CameraPos> *cameraLocations;
	unsigned int activeCamera;

public:
	FixedCamera(void);
	~FixedCamera(void);

	void AddCameraPos(float xPos, float yPos, float zPos, float phi, float theta);
	void NextPosition();
	CameraPos GetCurrentPos();
};
