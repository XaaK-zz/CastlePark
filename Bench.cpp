#include "Bench.h"

Bench::Bench(void)
{
}

Bench::~Bench(void)
{
}

Bench::Bench(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ,textureMgr) {

}

bool Bench::Initialize(void) {

	float benchHeight = 0.2f;

	this->textureMgr->LoadTexture("LightWood","LightWood.tga");
	
	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	this->textureMgr->ActivateTexture("LightWood");

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);//TOP
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(this->scaleX/2.0f, this->scaleY/2.0f);	glVertex3f(0.5f, 0.5f, 1.0f);
		glTexCoord2f(0.0, this->scaleY/2.0f);				glVertex3f(-0.5f, 0.5f, 1.0f);
		glTexCoord2f(0.0, 0.0);								glVertex3f(-0.5f, -0.5f, 1.0f);
		glTexCoord2f(this->scaleX/2.0f, 0.0);				glVertex3f(0.5f, -0.5f, 1.0f);
	glEnd();
	
	glBegin(GL_QUADS);//bottom
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(this->scaleX/2.0f, this->scaleY/2.0f);		glVertex3f(0.5f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(-0.5f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.5f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(this->scaleX/2.0f, 0.0);					glVertex3f(0.5f, 0.5f, 1.0f - benchHeight);
	glEnd();

	glBegin(GL_QUADS);//right side
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(0.5f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(0.5f, 0.5f, 1.0f);
		glTexCoord2f(0.0, 0.0);									glVertex3f(0.5f, -0.5f, 1.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(0.5f, -0.5f, 1.0f - benchHeight);
	glEnd();

	glBegin(GL_QUADS);//left side
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(-0.5f, 0.5f, 1.0f);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(-0.5f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.5f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.5f, -0.5f, 1.0f);
	glEnd();
	
	glBegin(GL_QUADS);	//north side
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleX/2.0f);		glVertex3f(0.5f, 0.5f, 1.0f);
		glTexCoord2f(0.0, this->scaleX/2.0f);					glVertex3f(0.5f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.5f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.5f, 0.5f, 1.0f);
	glEnd();
	
	glBegin(GL_QUADS);	//south side
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleX/2.0f);		glVertex3f(0.5f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleX/2.0f);					glVertex3f(0.5f, -0.5f, 1.0f);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.5f, -0.5f, 1.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.5f, -0.5f, 1.0f - benchHeight);
    glEnd();
	
	//legs
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(-0.3f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(-0.3f, 0.3f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.3f, -0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.3f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);//left side
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(-0.3f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(-0.3f, -0.3f, 0.0f);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.3f, -0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.3f, 0.3f, 1.0f - benchHeight);
	glEnd();
	
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(-0.35f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(-0.35f, -0.3f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.35f, 0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.35f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);//left side
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(-0.35f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(-0.35f, 0.3f, 0.0f);
		glTexCoord2f(0.0, 0.0);									glVertex3f(-0.35f, 0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(-0.35f, -0.3f, 1.0f - benchHeight);
	glEnd();

	///
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(0.3f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(0.3f, 0.3f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(0.3f, -0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(0.3f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);//left side
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(0.3f, 0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(0.3f, -0.3f, 0.0f);
		glTexCoord2f(0.0, 0.0);									glVertex3f(0.3f, -0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(0.3f, 0.3f, 1.0f - benchHeight);
	glEnd();
	
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(0.35f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(0.35f, -0.3f, 1.0f - benchHeight);
		glTexCoord2f(0.0, 0.0);									glVertex3f(0.35f, 0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(0.35f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);//left side
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);		glVertex3f(0.35f, -0.5f, 1.0f - benchHeight);
		glTexCoord2f(0.0, this->scaleY/2.0f);					glVertex3f(0.35f, 0.3f, 0.0f);
		glTexCoord2f(0.0, 0.0);									glVertex3f(0.35f, 0.5f, 0.0f);
		glTexCoord2f(this->scaleZ/2.0f, 0.0);					glVertex3f(0.35f, -0.3f, 1.0f - benchHeight);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
    glEndList();

    initialized = true;

    return true;
}

    