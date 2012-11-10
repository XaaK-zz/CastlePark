#include "Flag.h"
#include <FL/glut.h>

Flag::Flag(void)
{
}

Flag::Flag(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, float height, float fheight, float fLength)
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ) {
	this->poleHeight = height;
	this->flagHeight = fheight;
	this->flagLength = fLength;
}

Flag::~Flag(void)
{
}

bool Flag::Initialize(void) {

	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	
	glColor3f(0.75f, 0.75f, 0.75f);
	
	float angle = 0.0f;
	float nextAngle = 0.0f;
	int numRectForTrunk = 20;
	int numTriForTree = 10;
	float poleWidth = 0.05f;

	//create cyclinder for pole
	for(int i=0;i<numRectForTrunk;i++) {
		angle = i*2*M_PI/numRectForTrunk;
		nextAngle = (i+1)*2*M_PI/numRectForTrunk;
		float *temp = computeNormal(cos(angle), sin(angle),1.0f,
									cos(angle),sin(angle), 0.0f,
									cos(nextAngle),sin(nextAngle),0.0f);
		glBegin(GL_QUADS);
		glNormal3f(temp[0], temp[1],temp[2]);
		glVertex3f(cos(angle)*poleWidth, sin(angle)*poleWidth, this->poleHeight);
		glVertex3f(cos(angle)*poleWidth, sin(angle)*poleWidth, 0.0f);
		glVertex3f(cos(nextAngle)*poleWidth, sin(nextAngle)*poleWidth, 0.0f);
		glVertex3f(cos(nextAngle)*poleWidth, sin(nextAngle)*poleWidth, this->poleHeight);
		glEnd();

		delete [] temp;
	}

	//create top sphere
	glPushMatrix();
	glTranslatef (0.0f, 0.0f, this->poleHeight); /*  move position  */
	//glScalef(0.2f,0.2f,0.2f);

	glutSolidSphere(0.1f,10,10);
	glPopMatrix();
	glEnd();
	
	//create flag 
	//float flagHeight = 0.2;
	glColor3f(1.0f, 0.0f, 0.0f);
	
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, this->poleHeight-0.1f);
	glVertex3f(0.0f, 0.0f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-0.1f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, this->poleHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.0f, 0.0f, this->poleHeight-flagHeight-0.1f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f + this->flagLength, 0.0f, this->poleHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-flagHeight-0.1f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f + this->flagLength, 0.0f, this->poleHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.5f, 0.0f, this->poleHeight-0.1f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f + this->flagLength, 0.01f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.5f, 0.01f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.5f, 0.01f, this->poleHeight-0.1f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f + this->flagLength, 0.01f, this->poleHeight-flagHeight-0.1f);
	glVertex3f(0.5f, 0.01f, this->poleHeight-0.1f);
	glVertex3f(0.5f, 0.01f, this->poleHeight-flagHeight-0.1f);

	glEnd();


	glPopAttrib();
	/////////////////////////////

    glEndList();

    initialized = true;

    return true;
}

void Flag::Update(float) {

}


