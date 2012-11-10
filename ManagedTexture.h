#pragma once
#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

class ManagedTexture
{
public:
	ManagedTexture(const char* filePath);
	~ManagedTexture(void);
	void ActivateTexture();

protected:
	ubyte   *image_data;
	int	    image_height, image_width;
	GLuint  texture_obj;    
};
