#pragma once

#include <epoxy/gl.h>

namespace renderer {

class Texture {
public:
	Texture();
	~Texture();

	void update();

private:
	GLuint tex;
	char pixels[100 * 100 * 4];
};

}
