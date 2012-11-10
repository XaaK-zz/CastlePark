#include "ManagedTexture.h"

ManagedTexture::ManagedTexture(const char* filePath)
{

	if ( ! ( this->image_data = (ubyte*)tga_load(filePath, &this->image_width,
					   &this->image_height, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "Wall::Initialize: Couldn't load filePath\n");
		return;
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
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, this->image_width, this->image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, this->image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_NEAREST_MIPMAP_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
}

ManagedTexture::~ManagedTexture(void)
{
}

void ManagedTexture::ActivateTexture() {
	glBindTexture(GL_TEXTURE_2D, this->texture_obj);
}