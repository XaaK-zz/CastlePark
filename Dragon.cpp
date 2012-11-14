#include "Dragon.h"

Dragon::Dragon(void)
{
}

Dragon::Dragon(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ, textureMgr) {

}

Dragon::~Dragon(void)
{
}

bool Dragon::Initialize(void) {

	//TODO - load textures

	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
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
	/////////////////////////////////////////////////////////////////

	//Tail//////////////////////////////////////////////////////////////
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
	//////////////////////////////////////////////////////////////////////

	//Head/////////////////////////////////////////////////////////////////
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
	
	glEnd();
	////////////////////////////////////////////////////////////////////////
		

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	
    glEndList();

    initialized = true;

    return true;
}

void Dragon::Update(float dt) {

}
