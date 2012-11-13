#pragma once

#include <vector>

using namespace std;

struct CameraPos {
	float xPos;
	float yPos;
	float zPos;
	float phi;
	float theta;
};

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
