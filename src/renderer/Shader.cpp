#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Shader.h"

namespace renderer {

Shader::Shader(std::string filename, GLenum shader_type)
	:
	handle(0) {
	name = filename;
	type = shader_type;

	// load the fragment shader.
	std::fstream fragmentShaderFile(filename, std::ios::in);
	std::string fragmentShaderSource;

	if (fragmentShaderFile.is_open()) {
		std::stringstream buffer;
		buffer << fragmentShaderFile.rdbuf();
		fragmentShaderSource = buffer.str();
	}
	else {
		fragmentShaderFile.close();
		std::cerr << "could not find " << filename << std::endl;
		return;
	}
	fragmentShaderFile.close();

	handle = glCreateShader(type);
	const char *g = fragmentShaderSource.c_str();
	glShaderSource( handle, 1, &g, NULL );
	glCompileShader( handle );

	//Error checking.
	int isCompiled;
	glGetShaderiv( handle, GL_COMPILE_STATUS, &isCompiled );
	if( !isCompiled )
	{
	        GLint maxLength = 0;
	        glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &maxLength );

	        //The maxLength includes the NULL character
	        std::vector<char> errorLog( maxLength );
	        glGetShaderInfoLog( handle, maxLength, &maxLength, errorLog.data() ); // &errorLog[0]
	        std::cerr << "error in file " << filename << std::endl;
	        std::cerr << errorLog.data() << std::endl;
	        glDeleteShader(handle); //Don't leak the shader.
	        handle = 0;
	        return;
	}
}

Shader::~Shader() {
	if (handle) {
		glDeleteShader(handle);
	}
}

}
