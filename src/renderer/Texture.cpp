#include "Texture.h"

namespace renderer {

Texture::Texture() {
	glGenTextures(1, &tex);
}

Texture::~Texture() {
	glDeleteTextures(1, &tex);
}

void Texture::update() {
	int width = 100;
	int height = 100;
	for (int i = 0; i < width * height * 4; ++i) {
		pixels[i] = i & 0xff;
	}

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}


}
