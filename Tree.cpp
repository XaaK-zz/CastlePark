#include "Tree.h"

Tree::Tree(void)
{
}

Tree::Tree(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, float tWidth, float tHeight, float bTop, float bWidth, TextureManager *textureMgr) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ, textureMgr) {
		this->trunkHeight = tHeight;
	this->trunkWidth = tWidth;
	this->topOfTree = bTop;
	this->branchWidth = bWidth;
}

Tree::~Tree(void)
{
}


bool Tree::Initialize(void) {

	this->textureMgr->LoadTexture("Bark","bark1.tga");
	this->textureMgr->LoadTexture("Leaves","leaves.tga");
	//ManagedTexture *texture = new ManagedTexture("bark1.tga");
	//this->textureList->push_back(texture);
	//texture = new ManagedTexture("leaves.tga");
	//this->textureList->push_back(texture);

	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//this->textureList->at(0)->ActivateTexture();
	this->textureMgr->ActivateTexture("Bark");
	glColor3f(1.0, 1.0, 1.0);
	
	float angle = 0.0f;
	float nextAngle = 0.0f;
	int numRectForTrunk = 10;
	int numTriForTree = 10;

	//create cyclinder for trunk
	for(int i=0;i<numRectForTrunk;i++) {
		angle = i*2*M_PI/numRectForTrunk;
		nextAngle = (i+1)*2*M_PI/numRectForTrunk;
		float *temp = computeNormal(cos(angle), sin(angle),1.0f,
									cos(angle),sin(angle), 0.0f,
									cos(nextAngle),sin(nextAngle),0.0f);
		glBegin(GL_QUADS);
		glNormal3f(temp[0], temp[1],temp[2]);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle)*trunkWidth, sin(angle)*trunkWidth, trunkHeight);
		glTexCoord2f(1.0f, 0.0);	glVertex3f(cos(angle)*trunkWidth, sin(angle)*trunkWidth, 0.0f);
		glTexCoord2f(0.0, 0.0);		glVertex3f(cos(nextAngle)*trunkWidth, sin(nextAngle)*trunkWidth, 0.0f);
		glTexCoord2f(0.0,1.0f);		glVertex3f(cos(nextAngle)*trunkWidth, sin(nextAngle)*trunkWidth, trunkHeight);
		glEnd();

		delete [] temp;
	}



	//create top of tree
	//this->textureList->at(1)->ActivateTexture();
	this->textureMgr->ActivateTexture("Leaves");

	glBegin(GL_TRIANGLES);
	
	for(int i=0;i<numTriForTree;i++) {
		angle = i*2*M_PI/numTriForTree;
		nextAngle = (i+1)*2*M_PI/numTriForTree;
		float *temp = computeNormal(0,0,trunkHeight+topOfTree,
									cos(angle)*branchWidth,sin(angle)*branchWidth,trunkHeight,
									cos(nextAngle)*branchWidth,sin(nextAngle)*branchWidth,trunkHeight);
		glNormal3f(temp[0], temp[1],temp[2]);

		glTexCoord2f(0.5f, 5.0f);	glVertex3f(0,0,trunkHeight+topOfTree);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle)*branchWidth,sin(angle)*branchWidth,trunkHeight);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(cos(nextAngle) * branchWidth,sin(nextAngle)*branchWidth,trunkHeight);
		delete [] temp;

		//bottom rect
		temp = computeNormal(0,0,trunkHeight,
							cos(angle)*branchWidth,sin(angle)*branchWidth,trunkHeight,
							cos(nextAngle)*branchWidth,sin(nextAngle)*branchWidth,trunkHeight);
		glNormal3f(-temp[0], -temp[1],-temp[2]);

		glTexCoord2f(0.5f, 5.0f);	glVertex3f(0,0,trunkHeight);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(cos(nextAngle) * branchWidth,sin(nextAngle)*branchWidth,trunkHeight);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(cos(angle)*branchWidth,sin(angle)*branchWidth,trunkHeight);
		
		delete [] temp;
	}
	glEnd();
		
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	/////////////////////////////

    glEndList();

    initialized = true;

    return true;
}

void Tree::Update(float dt) {

}

void Tree::Draw(void) {

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
