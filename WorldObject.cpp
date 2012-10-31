#include "WorldObject.h"

WorldObject::WorldObject(void) {
	this->posX = 0.0f;
	this->posY = 0.0f;
	this->posZ = 0.0f;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;
	this->scaleZ = 1.0f;

	this->initialized = false;
}

WorldObject::~WorldObject(void) {
	if (initialized){
		glDeleteLists(displayList, 1);
    }
}

WorldObject::WorldObject(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ) {
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->initialized = false;
}
	
bool WorldObject::Initialize(void) {

	initialized = true;

    return true;
}

void WorldObject::Update(float) {

}

void WorldObject::Draw(void) {

}