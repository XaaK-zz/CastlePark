#include "FixedCamera.h"

FixedCamera::FixedCamera(void) {
	this->cameraLocations = new vector<CameraPos>();
	activeCamera = 0;
}

FixedCamera::~FixedCamera(void) {
	delete cameraLocations;
}

void FixedCamera::AddCameraPos(float xPos, float yPos, float zPos, float phi, float theta) {

	CameraPos cam;
	cam.xPos = xPos;
	cam.yPos = yPos;
	cam.zPos = zPos;
	cam.phi = phi;
	cam.theta= theta;
	
	this->cameraLocations->push_back(cam);
}

void FixedCamera::NextPosition() {
	this->activeCamera++;
	if(this->activeCamera > this->cameraLocations->capacity()-1)
		this->activeCamera = 0;
}

CameraPos FixedCamera::GetCurrentPos() {
	return this->cameraLocations->at(this->activeCamera);
}