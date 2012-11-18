#include "Utility.h"

Utility::Utility(void)
{
}

Utility::~Utility(void)
{
}

//NOTE: Sphere code derived from this tutorial: http://www.swiftless.com/tutorials/opengl/sphere.html
Vertex* Utility::CreateSphere(int space, float subdivisions, float xDisplacement, float yDisplacement, float zDisplacement, int *size) {
	*size = (180 / space) * (360 / space) * 4;
	Vertex *output = new Vertex[*size];

	int n = 0;

	for(float b = 0; b <= 180-space; b+=space){
		for(float a = 0; a <= 360-space; a+=space){
			output[n].x = subdivisions * sin((a) / 180 * M_PI) * sin((b) / 180 * M_PI) + xDisplacement;
			output[n].normalX = subdivisions * sin((a) / 180 * M_PI) * sin((b) / 180 * M_PI);
			output[n].y = subdivisions * cos((a) / 180 * M_PI) * sin((b) / 180 * M_PI) + yDisplacement;
			output[n].normalY = subdivisions * cos((a) / 180 * M_PI) * sin((b) / 180 * M_PI);
			output[n].z = subdivisions * cos((b) / 180 * M_PI) - zDisplacement;
			output[n].normalZ = subdivisions * cos((b) / 180 * M_PI);
			output[n].v = (b) / 360;
			output[n].u = (a) / 360;
			n++;

			output[n].x = subdivisions * sin((a) / 180 * M_PI) * sin((b + space) / 180 * M_PI) + xDisplacement;
			output[n].normalX = subdivisions * sin((a) / 180 * M_PI) * sin((b + space) / 180 * M_PI);
			output[n].y = subdivisions * cos((a) / 180 * M_PI) * sin((b + space) / 180 * M_PI) + yDisplacement;
			output[n].normalY = subdivisions * cos((a) / 180 * M_PI) * sin((b + space) / 180 * M_PI);
			output[n].z = subdivisions * cos((b + space) / 180 * M_PI) - zDisplacement;
			output[n].normalZ = subdivisions * cos((b + space) / 180 * M_PI);
			output[n].v = (b + space) / 360;
			output[n].u = (a) / 360;
			n++;

			output[n].x = subdivisions * sin((a + space) / 180 * M_PI) * sin((b) / 180 * M_PI) + xDisplacement;
			output[n].normalX = subdivisions * sin((a + space) / 180 * M_PI) * sin((b) / 180 * M_PI);
			output[n].y = subdivisions * cos((a + space) / 180 * M_PI) * sin((b) / 180 * M_PI) + yDisplacement;
			output[n].normalY = subdivisions * cos((a + space) / 180 * M_PI) * sin((b) / 180 * M_PI);
			output[n].z = subdivisions * cos((b) / 180 * M_PI) - zDisplacement;
			output[n].normalZ = subdivisions * cos((b) / 180 * M_PI);
			output[n].v = (b) / 360;
			output[n].u = (a + space) / 360;
			n++;

			output[n].x = subdivisions * sin((a + space) / 180 * M_PI) * sin((b + space) / 180 * M_PI) + xDisplacement;
			output[n].normalX = subdivisions * sin((a + space) / 180 * M_PI) * sin((b + space) / 180 * M_PI);
			output[n].y = subdivisions * cos((a + space) / 180 * M_PI) * sin((b + space) / 180 * M_PI) + yDisplacement;
			output[n].normalY = subdivisions * cos((a + space) / 180 * M_PI) * sin((b + space) / 180 * M_PI);
			output[n].z = subdivisions * cos((b + space) / 180 * M_PI) - zDisplacement;
			output[n].normalZ = subdivisions * cos((b + space) / 180 * M_PI);
			output[n].v = (b + space) / 360;
			output[n].u = (a + space) / 360;
			n++;
		}
	}

	return output;
}


void Utility::DrawSphere(Vertex* vertices, int size) {
	//int size =sizeof(vertices)/sizeof(Vertex); 

	glBegin (GL_TRIANGLE_STRIP);
	for(int  b = 0; b < size; b++){
		glNormal3f(vertices[b].normalX, vertices[b].normalY,-vertices[b].normalZ);
		glTexCoord2f (vertices[b].u, vertices[b].v);
		glVertex3f (vertices[b].x, vertices[b].y, -vertices[b].z);
	}

	glEnd();
}