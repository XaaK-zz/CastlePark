#include "TextureManager.h"

TextureManager::TextureManager(void) {
	textureList = new map<const char*, ManagedTexture*>();
}

TextureManager::~TextureManager(void) {
	for(std::map<const char*,ManagedTexture*>::iterator it = this->textureList->begin(); it != this->textureList->end(); ++it) {
		delete (*it).second;
	}
	delete textureList;
}

void TextureManager:: Init() {
	//fill map with textures

}

bool TextureManager::LoadTexture(const char* textureName, const char* filePath) {

	map<const char*,ManagedTexture*>::iterator it = this->textureList->find(textureName);

	if(it == this->textureList->end()) {
		ManagedTexture *wallTexture = new ManagedTexture(filePath);
		this->textureList->insert(pair<const char*,ManagedTexture*>(textureName,wallTexture));
		return true;
	}

	return false;
}

bool TextureManager::ActivateTexture(const char* textureName) {

	map<const char*,ManagedTexture*>::iterator it = this->textureList->find(textureName);
	
	if(it != this->textureList->end()) {
		(*it).second->ActivateTexture();
		return true;
	}
	else {
		return false;
	}
}