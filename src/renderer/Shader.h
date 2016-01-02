#pragma once

#include <string>

#include <epoxy/gl.h>

namespace renderer {

/**
 * draws input verticies
 * each shader uses a specific vertex format
 */
class Shader {
public:
	std::string name;
	GLuint handle;
	GLenum type;

	Shader(std::string filename, GLenum shader_type);
	~Shader();

};

}
