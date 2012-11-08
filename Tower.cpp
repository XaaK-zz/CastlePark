#include "Tower.h"


Tower::Tower(void)
{
}

Tower::Tower(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int roofTri) 
: WorldObject(posX, posY, posZ, scaleX, scaleY, scaleZ) {
	this->numRoofTriangles = roofTri;
}


Tower::~Tower(void)
{
}

bool Tower::Initialize(void) {

	ubyte   *image_data;
	ubyte   *image_data2;
    int	    image_height, image_width;
	int	    image_height2, image_width2;

    // Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if ( ! ( image_data = (ubyte*)tga_load("wall.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "Wall::Initialize: Couldn't load StoneWall1.tga\n");
		return false;
    }
	if ( ! ( image_data2 = (ubyte*)tga_load("woodTex.tga", &image_width2,
					   &image_height2, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "Wall::Initialize: Couldn't load StoneWall2.tga\n");
		return false;
    }

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &this->texture_obj);
    glBindTexture(GL_TEXTURE_2D, this->texture_obj);
    
    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_NEAREST_MIPMAP_LINEAR);
	
	glGenTextures(1, &this->texture_obj2);
    glBindTexture(GL_TEXTURE_2D, this->texture_obj2);

    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width2, image_height2, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

	glBindTexture(GL_TEXTURE_2D, this->texture_obj);
	this->displayList = glGenLists(1);
    glNewList(this->displayList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texture_obj);

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

	glBindTexture(GL_TEXTURE_2D, this->texture_obj2);

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

		glTexCoord2f(0.5f, 5.0f);
		glVertex3f(0,0,0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(cos(angle),sin(angle),0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(cos(nextAngle),sin(nextAngle),0.0f);
		delete [] temp;
	}
	glEnd();

/*
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5f, 5.0f);
	glVertex3f(0,0,0.5f);
	for(int i=0;i<10;i++) {
		
		angle = i*2*M_PI/10;

		float *temp = computeNormal(0,0,0.5f,cos(angle),sin(angle),0.0f,cos((i+1)*2*M_PI/10),sin((i+1)*2*M_PI/10),0.0f);
		glNormal3f(temp[0], temp[1],temp[2]);
		glTexCoord2f(cos(angle), sin(angle));
		glVertex3f(cos(angle),sin(angle),0.0f);
		delete [] temp;
		//angle = i*2*M_PI/360;
		//glVertex3f(cos(angle),sin(angle),0.5f);
	}
	glTexCoord2f(cos(0.0f), sin(0.0f));
	glVertex3f(cos(0.0f),sin(0.0f),0.0f);
	glEnd();
*/
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