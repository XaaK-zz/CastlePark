#include "Wall.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

Wall::Wall(void)
{
}


Wall::Wall(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int creDir, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ,textureMgr) {
	this->crenellationDirection = creDir;
}

Wall::~Wall(void)
{

}

bool Wall::Initialize(void) {

	this->textureMgr->LoadTexture("MainWall","wall.tga");
	//ManagedTexture *wallTexture = new ManagedTexture("wall.tga");
	//this->textureList->push_back(wallTexture);

	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//wallTexture->ActivateTexture();
	this->textureMgr->ActivateTexture("MainWall");

    glColor3f(1.0, 1.0, 1.0);

	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(90.0f, 0, 0, 1);
	glTranslatef(-0.5, -0.5, 0);
	glPopAttrib();

    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(this->scaleX/2.0f, this->scaleY/2.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(-0.5f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 1.0f);
	glTexCoord2f(this->scaleX/2.0f, 0.0);
	glVertex3f(0.5f, -0.5f, 1.0f);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(this->scaleX/2.0f, this->scaleY/2.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(this->scaleX/2.0f, 0.0);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd();

	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(-90.0f, 0, 0, 1);
	glTranslatef(-0.5, -0.5, 0);
	glPopAttrib();

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5f, -0.5f, 1.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(90.0f, 0, 0, 1);
	glTranslatef(-0.5, -0.5, 0);
	glPopAttrib();

	//Inside Facing wall
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);
	glVertex3f(-0.5f, 0.5f, 1.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(-0.5f, -0.5f, 1.0f);
	glEnd();
	
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(90.0f, 0, 0, 1);
	glTranslatef(-0.5, -0.5, 0);
	glPopAttrib();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleX/2.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glTexCoord2f(0.0, this->scaleX/2.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(-0.5f, 0.5f, 1.0f);
	glEnd();
	
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(-90.0f, 0, 0, 1);
	glTranslatef(-0.5, -0.5, 0);
	glPopAttrib();
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleX/2.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(0.0, this->scaleX/2.0f);
	glVertex3f(0.5f, -0.5f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 1.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.0f);
    glEnd();
	
	
	//glPopMatrix();

	//crenellations//////////////
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	float width = 0.05f;
	float height = 0.2f;
	float depth = 0.2f;
	float xAdjust = 0.5f - width;
	float yAdjust = 0.5f - width;
	int iteratorMax = 2;
	float xPos = 0.0f;
	float yPos = 0.0f;
	float zPos = 0.0f;
	
	
	if(this->crenellationDirection == WEST || this->crenellationDirection == EAST) {
		//iteratorMax = (this->scaleY/2.75f);
		iteratorMax = 1.0f/(width+0.02f);
		float temp = depth;
		depth = width;
		width = temp;
	}
	else {
		//iteratorMax = (this->scaleX/2.75f);
		iteratorMax = 1.0f/(width+0.02f);
	}
	
	

	for(int i=0;i<iteratorMax;i++) {
		//glPushMatrix();
		if(this->crenellationDirection == WEST) {
			xAdjust = -0.5f + width;
		}
		if(this->crenellationDirection == SOUTH) {
			yAdjust = -0.5f + depth;
		}

		if(this->crenellationDirection == WEST || this->crenellationDirection == EAST) {
			xPos = xAdjust;
			yPos = 0.5f - (i*(depth+.02));
			zPos = 1.0f + height;
			//glTranslatef (this->posX + xAdjust, (this->scaleY/2.0f-1.0f) - (i*2.75f), this->scaleZ); /*  move position  */
			//glScalef(1.0f,2.0f,1.0f);
		}
		else {
			xPos = 0.5f - (i*(width+.02));
			yPos = yAdjust;
			zPos = 1.0f + height;
			//glTranslatef (this->posX + (this->scaleX/2.0f-1.0f) - (i*2.75f),this->posY + yAdjust , this->scaleZ); /*  move position  */
			//glScalef(2.0f,1.0f,1.0f);
		}
		
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f,1.0f);
		//glVertex3f(0.5f, 0.5f, 1.0f);
		glVertex3f(xPos, yPos, zPos);
		glTexCoord2f(0.0, 1.0f);
		//glVertex3f(-0.5f, 0.5f, 1.0f);
		glVertex3f(xPos-width, yPos, zPos);
		glTexCoord2f(0.0, 0.0);
		//glVertex3f(-0.5f, -0.5f, 1.0f);
		glVertex3f(xPos-width, yPos-depth, zPos);
		glTexCoord2f(1.0f, 0.0);
		//glVertex3f(0.5f, -0.5f, 1.0f);
		glVertex3f(xPos, yPos-depth, zPos);
		glEnd();
		
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(xPos, yPos-depth, zPos-height);
		glTexCoord2f(0.0,1.0f);
		//glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f(xPos-width, yPos-depth, zPos-height);
		glTexCoord2f(0.0, 0.0);
		//glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(xPos-width, yPos, zPos-height);
		glTexCoord2f(1.0f, 0.0);
		//glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(xPos, yPos, zPos-height);
		glEnd();

		//glPushAttrib(GL_TRANSFORM_BIT);
		//glMatrixMode(GL_TEXTURE);
		//glLoadIdentity();
		//glTranslatef(0.5, 0.5, 0);
		//glRotatef(-90.0f, 0, 0, 1);
		//glTranslatef(-0.5, -0.5, 0);
		//glPopAttrib();

		glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f,1.0f);
		//glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(xPos, yPos, zPos-height);
		glTexCoord2f(0.0, 1.0f);
		//glVertex3f(0.5f, 0.5f, 1.0f);
		glVertex3f(xPos, yPos, zPos);
		glTexCoord2f(0.0, 0.0);
		//glVertex3f(0.5f, -0.5f, 1.0f);
		glVertex3f(xPos, yPos-depth, zPos);
		glTexCoord2f(1.0f, 0.0);
		//glVertex3f(0.5f, -0.5f, 0.0f);
		glVertex3f(xPos, yPos-depth, zPos-height);
		glEnd();

		//Inside Facing wall
		glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(xPos-width, yPos, zPos);
		glTexCoord2f(0.0, 1.0f);
		glVertex3f(xPos-width,yPos, zPos-height);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(xPos-width, yPos-depth, zPos-height);
		glTexCoord2f(1.0f, 0.0);
		glVertex3f(xPos-width, yPos-depth, zPos);
		glEnd();
	
		//glPushAttrib(GL_TRANSFORM_BIT);
		//glMatrixMode(GL_TEXTURE);
		//glLoadIdentity();
		//glTranslatef(0.5, 0.5, 0);
		//glRotatef(90.0f, 0, 0, 1);
		//glTranslatef(-0.5, -0.5, 0);
		//glPopAttrib();

		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(xPos, yPos, zPos);
		glTexCoord2f(0.0, 1.0f);
		glVertex3f(xPos, yPos, zPos-height);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(xPos-width, yPos, zPos-height);
		glTexCoord2f(1.0f, 0.0);
		glVertex3f(xPos-width, yPos, zPos);
		glEnd();
		
		//glPushAttrib(GL_TRANSFORM_BIT);
		//glMatrixMode(GL_TEXTURE);
		//glLoadIdentity();
		//glTranslatef(0.5, 0.5, 0);
		//glRotatef(-90.0f, 0, 0, 1);
		//glTranslatef(-0.5, -0.5, 0);
		//glPopAttrib();
		
		glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(xPos, yPos-depth, zPos-height);
		glTexCoord2f(0.0,1.0f);
		glVertex3f(xPos, yPos-depth, zPos);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(xPos-width, yPos-depth, zPos);
		glTexCoord2f(1.0f, 0.0);
		glVertex3f(xPos-width, yPos-depth, zPos-height);
		glEnd();
		
		//glPopMatrix();
	}

	
glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	/////////////////////////////
//glPopMatrix();
    glEndList();

    initialized = true;

    return true;
}

void Wall::Update(float) {

}

void Wall::Draw(void) {

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