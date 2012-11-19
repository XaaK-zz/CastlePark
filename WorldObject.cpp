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
		/*
		for(std::vector<ManagedTexture*>::iterator it = this->textureList->begin(); it != this->textureList->end(); ++it) {
			delete (*it);
		}

		delete this->textureList;
		*/
    }
}

WorldObject::WorldObject(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr) {
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->initialized = false;

	//this->textureList = new vector<ManagedTexture*>();
	this->textureMgr = textureMgr;
}
	
bool WorldObject::Initialize(void) {

	initialized = true;

    return true;
}

void WorldObject::Update(float) {

}

void WorldObject::Draw(void) {

	if (!initialized) {
		return;
	}

    glPushMatrix();
	glTranslatef (this->posX, this->posY, this->posZ); /*  move position  */
	glScalef(this->scaleX,this->scaleY,this->scaleZ);
    // Draw the wall
	glCallList(this->displayList);

	glPopMatrix();
}

float* WorldObject::computeNormal(float trianglePt1X,float trianglePt1Y,float trianglePt1Z,
					 float trianglePt2X,float trianglePt2Y,float trianglePt2Z,
					 float trianglePt3X,float trianglePt3Y,float trianglePt3Z) {
	float *returnValues = new float[3];
	
	float Ux = trianglePt2X - trianglePt1X;
	float Uy = trianglePt2Y - trianglePt1Y;
	float Uz = trianglePt2Z - trianglePt1Z;

	float Vx = trianglePt3X - trianglePt1X;
	float Vy = trianglePt3Y - trianglePt1Y;
	float Vz = trianglePt3Z - trianglePt1Z;

	returnValues[0] = (Uy * Vz) - (Uz * Vy);
	returnValues[1] = (Uz * Vx) - (Ux * Vz);
	returnValues[2] = (Ux * Vy) - (Uy * Vx);

	return returnValues;
}

void WorldObject::SetPosition(float x, float y, float z) {

	this->posX = x;
	this->posY = y;
	this->posZ = z;
}