#include "Tower.h"


Tower::Tower(void)
{
}

Tower::Tower(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int roofTri, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ, textureMgr) {
	this->numRoofTriangles = roofTri;
}


Tower::~Tower(void)
{
}

bool Tower::Initialize(void) {

	this->textureMgr->LoadTexture("MainWall","wall.tga");
	this->textureMgr->LoadTexture("Wood","woodTex.tga");
	 
	
	//glBindTexture(GL_TEXTURE_2D, this->texture_obj);
	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, this->texture_obj);
	this->textureMgr->ActivateTexture("MainWall");

    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef (this->posX, this->posY, this->posZ); /*  move position  */
	glScalef(this->scaleX,this->scaleY,this->scaleZ);

	//TOP
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(this->scaleX/2.0f, this->scaleY/2.0f);
	glVertex3f(0.4f, 0.4f, 1.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(-0.4f, 0.4f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.4f, -0.4f, 1.0f);
	glTexCoord2f(this->scaleX/2.0f, 0.0);
	glVertex3f(0.4f, -0.4f, 1.0f);
	glEnd();
	
	//Bottom
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

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(0.4f, 0.4f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.4f, -0.4f, 1.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleY/2.0f);
	glVertex3f(-0.4f, 0.4f, 1.0f);
	glTexCoord2f(0.0, this->scaleY/2.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(-0.4f, -0.4f, 1.0f);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleX/2.0f);
	glVertex3f(0.4f, 0.4f, 1.0f);
	glTexCoord2f(0.0, this->scaleX/2.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(-0.4f, 0.4f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(this->scaleZ/2.0f, this->scaleX/2.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(0.0, this->scaleX/2.0f);
	glVertex3f(0.4f, -0.4f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.4f, -0.4f, 1.0f);
	glTexCoord2f(this->scaleZ/2.0f, 0.0);
	glVertex3f(-0.5f, -0.5f, 0.0f);
    glEnd();
	glPopMatrix();

	//glBindTexture(GL_TEXTURE_2D, this->texture_obj2);
	this->textureMgr->ActivateTexture("Wood");

	glPushMatrix();
	glTranslatef (this->posX, this->posY, this->scaleZ-0.35f); 
	glScalef(this->scaleX/1.3f,this->scaleY/1.3f,5.0f);
	
	float angle = 0.0f;
	float nextAngle = 0.0f;
	
	glBegin(GL_TRIANGLES);
	
	for(int i=0;i<this->numRoofTriangles;i++) {
		angle = i*2*M_PI/this->numRoofTriangles;
		nextAngle = (i+1)*2*M_PI/this->numRoofTriangles;
		float *temp = computeNormal(0,0,0.5f,cos(angle),sin(angle),0.0f,cos(nextAngle),sin(nextAngle),0.0f);
		glNormal3f(temp[0], temp[1],temp[2]);

		glTexCoord2f(0.5f, 5.0f);	glVertex3f(0,0,0.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle),sin(angle),0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(cos(nextAngle),sin(nextAngle),0.0f);
		
		temp = computeNormal(0,0,0.5f,
					cos(angle),sin(angle),0.5f,
					cos(nextAngle),sin(nextAngle),0.5f);
		glNormal3f(-temp[0], -temp[1],-temp[2]);

		glTexCoord2f(0.5f, 5.0f);	glVertex3f(0,0,0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(cos(nextAngle),sin(nextAngle),0);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle),sin(angle),0);
		
		delete [] temp;
	}
	glEnd();

	glPopMatrix();

glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	/////////////////////////////

    glEndList();

    initialized = true;

    return true;
}

void Tower::Update(float) {

}

void Tower::Draw(void) {
	
	if (!initialized) {
		return;
	}

    glPushMatrix();

    // Draw the wall
	glCallList(this->displayList);

	glPopMatrix();
}