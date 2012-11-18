#include "Dragon.h"
#include <FL/glut.h>
#include <iostream>

Dragon::Dragon(void)
{
}

Dragon::Dragon(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ, textureMgr) {

	this->numDisplayLists = 5;
	this->tailUpdateCounter = 0;
	this->tailAngle = 0.0f;
	this->tailDirection = true;
}

Dragon::~Dragon(void)
{
}

bool Dragon::Initialize(void) {

	//TODO - load textures

	this->displayListIndex = glGenLists(numDisplayLists);
    glNewList(this->displayListIndex, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//this->textureMgr->ActivateTexture("MainWall");

    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	glBegin(GL_QUADS);
	
	//BODY///////////////////////////////////////////////////
	//TOP
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, -0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(0.6f, -0.5f, 1.0f);
	
	//Bottom
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(0.6f, -0.5f, 0.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-0.6f, -0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(0.6f, 0.5f, 0.0f);
	
	//right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.6f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(0.6f, -0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(0.6f, -0.5f, 0.0f);
	
	//left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-0.6f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-0.6f, -0.5f, 1.0f);

	//north
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(0.6f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-0.6f, 0.5f, 1.0f);

	//south
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.6f, -0.5f, 0.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(0.6f, -0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, -0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-0.6f, -0.5f, 0.0f);
	
	glEnd();
	//glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	/////////////////////////////////////////////////////////////////

	//Tail//////////////////////////////////////////////////////////////
	glNewList(this->displayListIndex+1, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//this->textureMgr->ActivateTexture("MainWall");
    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	glBegin(GL_TRIANGLES);
	float *temp = computeNormal(0.6f, 0.5f, 1.0f, 0.5f, -0.5f, 1.0f, 3.0f, 0.0f, 0.5f);
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(0.6f, -0.5f, 1.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(3.0f, 0.0f, 0.5f);
	delete [] temp;

	temp = computeNormal(0.6f, 0.5f, 1.0f, 3.0f, 0.0f, 0.5f,0.5f, 0.5f, 0.0f);
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(3.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(0.6f, 0.5f, 0.0f);
	delete [] temp;

	temp = computeNormal(0.6f, -0.5f, 1.0f,0.5f, -0.5f, 0.0f,3.0f, 0.0f, 0.5f );
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(0.6f, -0.5f, 1.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(0.6f, -0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(3.0f, 0.0f, 0.5f);
	delete [] temp;

	temp = computeNormal(0.6f, 0.5f, 0.0f,3.0f, 0.0f, 0.5f,0.5f, -0.5f, 0.0f);
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(0.6f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(3.0f, 0.0f, 0.5f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(0.6f, -0.5f, 0.0f);
	delete [] temp;

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	//////////////////////////////////////////////////////////////////////

	//Head/////////////////////////////////////////////////////////////////
	glNewList(this->displayListIndex+2, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//this->textureMgr->ActivateTexture("MainWall");
    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	glBegin(GL_QUADS);
	temp = computeNormal(-0.6f, 0.5f, 1.0f,-1.8f, 0.2f, 0.7f,-1.8f, -0.2f, 0.7f );
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(-0.6f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-1.8f, 0.2f, 0.7f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-1.8f, -0.2f, 0.7f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-0.6f, -0.5f, 1.0f);
	delete [] temp;
	
	temp = computeNormal(-0.6f, 0.5f, 1.0f,-0.6f, 0.5f, 0.0f,-1.8f, 0.2f, 0.7f );
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(-0.6f, 0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-0.6f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-1.8f, 0.2f, 0.2f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-1.8f, 0.2f, 0.7f);
	delete [] temp;

	temp = computeNormal(-0.6f, -0.5f, 1.0f,-1.8f, -0.2f, 0.7f,-1.8f, -0.2f, 0.2f);
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(-0.6f, -0.5f, 1.0f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-1.8f, -0.2f, 0.7f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-1.8f, -0.2f, 0.2f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, -0.5f, 0.0f);
	delete [] temp;
	
	temp = computeNormal(-0.6f, 0.5f, 0.0f,-0.6f, -0.5f, 0.0f,-1.8f, -0.2f, 0.2f);
	glNormal3f(temp[0], temp[1],temp[2]);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(-0.6f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-0.6f, -0.5f, 0.0f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-1.8f, -0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-1.8f, 0.2f, 0.2f);
	delete [] temp;
	
	glNormal3f(-1.0f, 0,0);
	glTexCoord2f(1.0f,1.0f);	glVertex3f(-1.8f, 0.2f, 0.7f);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-1.8f, 0.2f, 0.2f);
	glTexCoord2f(0.0, 1.0f);	glVertex3f(-1.8f, -0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0);	glVertex3f(-1.8f, -0.2f, 0.7f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	////////////////////////////////////////////////////////////////////////
		
	//Right Wing////////////////////////////////////////////////////////////
	glNewList(this->displayListIndex+3, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//this->textureMgr->ActivateTexture("MainWall");
    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef (-0.55f, 0.45f, 0.95f); 
	glRotatef(20.0f,0,0,1.0f);
	glRotatef(-55.0f,1.0f,0,0);
	glPushMatrix();
	glScalef(0.08f,0.08f,2.0f);
    
	float angle = 0.0f;
	float nextAngle = 0.0f;
	int numRect = 10;

	//Wing "bone"
	for(int i=0;i<numRect;i++) {
		angle = i*2*M_PI/numRect;
		nextAngle = (i+1)*2*M_PI/numRect;
		float *temp = computeNormal(cos(angle), sin(angle),1.0f,
									cos(angle),sin(angle), 0.0f,
									cos(nextAngle),sin(nextAngle),0.0f);
		glBegin(GL_QUADS);
			glNormal3f(temp[0], temp[1],temp[2]);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle), sin(angle), 1.0f);
			glTexCoord2f(1.0f, 0.0);	glVertex3f(cos(angle), sin(angle), 0.0f);
			glTexCoord2f(0.0, 0.0);		glVertex3f(cos(nextAngle), sin(nextAngle), 0.0f);
			glTexCoord2f(0.0,1.0f);		glVertex3f(cos(nextAngle), sin(nextAngle), 1.0f);
		glEnd();

		delete [] temp;
	}
	//wing attached to main bone
	glBegin(GL_QUADS);
		glNormal3f(0, -1.0f,0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 1.0f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 0.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(15.0f, 0, -0.3f);
		glTexCoord2f(0.0,1.0f);		glVertex3f(15.0f, 0, 0.8f);

		glNormal3f(0, 1.0f,0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 1.0f);
		glTexCoord2f(0.0,1.0f);		glVertex3f(15.0f, 0, 0.8f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(15.0f, 0, -0.3f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 0.0f);
	glEnd();

	//wing joint
	glPopMatrix();
	int size;
	Vertex *sphereVertices = Utility::CreateSphere(1,0.1f,0,0,2.0f,&size);
	Utility::DrawSphere(sphereVertices,size);
	delete [] sphereVertices;
	
	glPushMatrix();

	glTranslatef (0, 0, 2.0f); 
	glRotatef(-40.0f,0,0,1.0f);
	glRotatef(-55.0f,1.0f,0,0);

	glTranslatef (0, 0, -2.0f); 

	glScalef(0.08f,0.08f,2.0f);

	//wing bone end
	for(int i=0;i<numRect;i++) {
		angle = i*2*M_PI/numRect;
		nextAngle = (i+1)*2*M_PI/numRect;
		float *temp = computeNormal(cos(angle), sin(angle),1.0f,
									cos(nextAngle),sin(nextAngle),1.0f,
									0.0f,0.0f, 2.0f);
		glBegin(GL_TRIANGLES);
			glNormal3f(temp[0], temp[1],temp[2]);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle), sin(angle), 1.0f);
			glTexCoord2f(1.0f, 0.0);	glVertex3f(cos(nextAngle), sin(nextAngle), 1.0f);
			glTexCoord2f(0.0, 0.0);		glVertex3f(0.0f, 0.0f, 2.0f);
		glEnd();

		delete [] temp;
	}

	//wing membrane attached to end
	glBegin(GL_TRIANGLES);
		glNormal3f(0, -1.0f,0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 2.0f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 1.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(14.0f, 10.0f, 1.2f);

		glNormal3f(0, 1.0f,0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 2.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(14.0f, 10.0f, 1.2f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 1.0f);
	glEnd();

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	//////////////////////////////////////////////////////////////////////////////

	//LEFT Wing////////////////////////////////////////////////////////////////
	glNewList(this->displayListIndex+4, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//this->textureMgr->ActivateTexture("MainWall");
    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef (-0.55f, -0.45f, 0.95f); 
	glRotatef(-20.0f,0,0,1.0f);
	glRotatef(55.0f,1.0f,0,0);
	glPushMatrix();
	glScalef(0.08f,0.08f,2.0f);
    
	angle = 0.0f;
	nextAngle = 0.0f;
	numRect = 10;

	//Wing "bone"
	for(int i=0;i<numRect;i++) {
		angle = i*2*M_PI/numRect;
		nextAngle = (i+1)*2*M_PI/numRect;
		float *temp = computeNormal(cos(angle), sin(angle),1.0f,
									cos(angle),sin(angle), 0.0f,
									cos(nextAngle),sin(nextAngle),0.0f);
		glBegin(GL_QUADS);
			glNormal3f(temp[0], temp[1],temp[2]);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle), sin(angle), 1.0f);
			glTexCoord2f(1.0f, 0.0);	glVertex3f(cos(angle), sin(angle), 0.0f);
			glTexCoord2f(0.0, 0.0);		glVertex3f(cos(nextAngle), sin(nextAngle), 0.0f);
			glTexCoord2f(0.0,1.0f);		glVertex3f(cos(nextAngle), sin(nextAngle), 1.0f);
		glEnd();

		delete [] temp;
	}
	//wing attached to main bone
	glBegin(GL_QUADS);
		glNormal3f(0, -1.0f,0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 1.0f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 0.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(15.0f, 0, -0.3f);
		glTexCoord2f(0.0,1.0f);		glVertex3f(15.0f, 0, 0.8f);

		glNormal3f(0, 1.0f,0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 1.0f);
		glTexCoord2f(0.0,1.0f);		glVertex3f(15.0f, 0, 0.8f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(15.0f, 0, -0.3f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 0.0f);
	glEnd();

	//wing joint
	glPopMatrix();
	sphereVertices = Utility::CreateSphere(1,0.1f,0,0,2.0f,&size);
	Utility::DrawSphere(sphereVertices,size);
	delete [] sphereVertices;
	
	//glPopMatrix();
	glPushMatrix();

	//glTranslatef (-0.55f, 0.45f, 0.95f); 
	//glRotatef(20.0f,0,0,1.0f);
	//glRotatef(-55.0f,1.0f,0,0);
	
	glTranslatef (0, 0, 2.0f); 
	glRotatef(40.0f,0,0,1.0f);
	glRotatef(55.0f,1.0f,0,0);

	glTranslatef (0, 0, -2.0f); 

	glScalef(0.08f,0.08f,2.0f);

	//wing bone end
	for(int i=0;i<numRect;i++) {
		angle = i*2*M_PI/numRect;
		nextAngle = (i+1)*2*M_PI/numRect;
		temp = computeNormal(cos(angle), sin(angle),1.0f,
									cos(nextAngle),sin(nextAngle),1.0f,
									0.0f,0.0f, 2.0f);
		glBegin(GL_TRIANGLES);
			glNormal3f(temp[0], temp[1],temp[2]);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle), sin(angle), 1.0f);
			glTexCoord2f(1.0f, 0.0);	glVertex3f(cos(nextAngle), sin(nextAngle), 1.0f);
			glTexCoord2f(0.0, 0.0);		glVertex3f(0.0f, 0.0f, 2.0f);
		glEnd();

		delete [] temp;
	}

	//wing membrane attached to end
	glBegin(GL_TRIANGLES);
		temp = computeNormal(0,0,2.0f,
							0,0,1.0f,
							14.0f,-10.0f,1.2f);
		glNormal3f(temp[0],temp[1],temp[2]);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 2.0f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 1.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(14.0f, -10.0f, 1.2f);

		temp = computeNormal(0,0,2.0f,
							14.0f,-10.0f,1.2f,
							0,0,1.0f);
		glNormal3f(temp[0],temp[1],temp[2]);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(0,    0, 2.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(14.0f, -10.0f, 1.2f);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(0,    0, 1.0f);
	glEnd();

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();



	///////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////

    initialized = true;

    return true;
}

void Dragon::Update(float dt) {
	this->tailUpdateCounter++;
	if(this->tailUpdateCounter > 2) {
		this->tailUpdateCounter = 0;
		if(this->tailDirection) {
			this->tailAngle += 2.0f;
			if(this->tailAngle >= 11.0f) {
				this->tailDirection = false;
			}
		}
		else {
			this->tailAngle -= 2.0f;
			if(this->tailAngle <= -11.0f) {
				this->tailDirection = true;
			}
		}
	}
}

void Dragon::Draw(void) {

	if (!initialized) {
		return;
	}

    glPushMatrix();
	glTranslatef (this->posX, this->posY, this->posZ); /*  move position  */
	glScalef(this->scaleX,this->scaleY,this->scaleZ);

	//BODY
	glCallList(this->displayListIndex);

	//TAIL
	glPushMatrix();
	glTranslatef(0.5f,0,0);
	glRotatef(this->tailAngle,0,0,1.0f);
	glTranslatef(-0.5f,0,0);
	glCallList(this->displayListIndex+1);
	glPopMatrix();

	//Head
	glCallList(this->displayListIndex+2);
	
	//right wing
	glPushMatrix();
	glRotatef(this->tailAngle,1.0f,0,0);
	glCallList(this->displayListIndex+3);
	glPopMatrix();
	
	//left wing
	glPushMatrix();
	glRotatef(-this->tailAngle,1.0f,0,0);
	glCallList(this->displayListIndex+4);
	glPopMatrix();

	glPopMatrix();
}