#include "Dragon.h"
#include <FL/glut.h>

Dragon::Dragon(void)
{
}

Dragon::Dragon(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ, textureMgr) {

	this->numDisplayLists = 4;
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
	glPopMatrix();
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
	glPopMatrix();
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
	glPopMatrix();
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
	//glTranslatef (-0.55f, 0.45f, 0.95f); 
	glRotatef(20.0f,0,0,1.0f);
	glRotatef(-55.0f,1.0f,0,0);
	//glScalef(0.08f,0.08f,2.0f);
  /*  
	float angle = 0.0f;
	float nextAngle = 0.0f;
	int numRect = 10;

	//create cyclinder for trunk
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
*/
	int size;
	Vertex *sphereVertices = Utility::CreateSphere(30,1.0f,0,0,0,&size);
	Utility::DrawSphere(sphereVertices,size);
	delete [] sphereVertices;
	/*
	glPopMatrix();
	
	glPushMatrix();
	//glTranslatef (-0.55f, 0.45f, 0.95f); 
	float x = cos(20.0f * 180/M_PI);
	float y = sin(20.0f* 180/M_PI);
	float r = sqrtf(pow(x,2)+pow(y,2));
	glTranslatef (cos(20.0f * 180/M_PI) * r, sin(20.0f* 180/M_PI) * r, sin(305.0f * 180/M_PI) * 2.0); 
	glutSolidSphere(0.1f,10,10);
	//glTranslatef (0.0f, 0.0f, -2.0f); 
	glPopMatrix();
	glEnd();
	*/
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	///////////////////////////////////////////////////////////////////////

    initialized = true;

    return true;
}

void Dragon::Update(float dt) {

}

void Dragon::Draw(void) {

	if (!initialized) {
		return;
	}

    glPushMatrix();
	glTranslatef (this->posX, this->posY, this->posZ); /*  move position  */
	glScalef(this->scaleX,this->scaleY,this->scaleZ);

	//glCallList(this->displayListIndex);
	//glCallList(this->displayListIndex+1);
	glCallList(this->displayListIndex+2);
	glCallList(this->displayListIndex+3);

	glPopMatrix();
}