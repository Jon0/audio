#pragma once

#include <memory>

#include "Shader.h"
#include "Texture.h"

namespace renderer {

class Renderer {
public:
	Renderer();
	void update();

private:
	std::string src_path;
	Shader vert_shader, frag_shader;
	GLuint program;
	Texture tx;
};

}
