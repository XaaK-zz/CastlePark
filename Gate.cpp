#include "Gate.h"

Gate::Gate(void)
{
}


Gate::Gate(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, float pPoint, int gateDir, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ, textureMgr) {

	this->gateState = GATE_CLOSED;
	this->rotateAngle = 0.0;
	this->pivotPoint = pPoint;
	this->gateDirection = gateDir;
}


Gate::~Gate(void)
{
}

bool Gate::Initialize(void) {

	this->textureMgr->LoadTexture("Wood","woodTex.tga");
	this->textureMgr->ActivateTexture("Wood");

	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, this->texture_obj);

    glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();

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
	
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	/////////////////////////////

    glEndList();

    initialized = true;

    return true;
}

void Gate::Update(float dt) {

	if(this->gateState == GATE_OPENING) {
		this->rotateAngle += 0.5f;
		if(this->rotateAngle >= 91.0f) {
			this->gateState = GATE_OPEN;
			this->rotateAngle = 90.0f;
		}
	}
	else if(this->gateState == GATE_CLOSING) {
		this->rotateAngle -= 0.5f;
		if(this->rotateAngle <= 0.0f) {
			this->gateState = GATE_CLOSED;
			this->rotateAngle = 0.0f;
		}
	}
}

void Gate::Draw(void) {
	
	if (!initialized) {
		return;
	}

    glPushMatrix();
	
	glTranslatef (this->posX-this->pivotPoint, this->posY, this->posZ); /*  move position  */
	//glTranslatef (-this->scaleX/2.0f, 0.0f, 0.0f); /*  move position  */
	
	if(gateDirection == 1)
		glRotatef(this->rotateAngle,0,0,1.0f);
	else
		glRotatef(-this->rotateAngle,0,0,1.0f);

	glTranslatef (this->pivotPoint, 0.0f, 0.0f); /*  move position  */
	
	glScalef(this->scaleX,this->scaleY,this->scaleZ);
	//glTranslatef(0.0f,this->scaleY,0.0f);
	
	
	//glRotatef(this->rotateAngle,0,0,1.0f);

    // Draw the wall
	glCallList(this->displayList);

	glPopMatrix();
}

void Gate::ChangeGateState() {
	if(this->gateState == GATE_OPENING) {
		this->gateState = GATE_CLOSING;
	}
	else if(this->gateState == GATE_CLOSING) {
		this->gateState = GATE_OPENING;
	}
	else if(this->gateState == GATE_CLOSED) {
		this->gateState = GATE_OPENING;
	}
	else if(this->gateState == GATE_OPEN) {
		this->gateState = GATE_CLOSING;
	}
}