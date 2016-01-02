#include <fstream>
#include <iostream>
#include <sstream>

#include <epoxy/gl.h>

#include "Renderer.h"

namespace renderer {


std::string get_src_path() {
	std::ifstream text("src_path");
	std::stringstream ss;
	ss << text.rdbuf();
	std::string src_path = ss.str();
	return src_path.substr(0, src_path.length() - 1);
}


Renderer::Renderer()
	:
	src_path(get_src_path()),
	vert_shader(src_path + "/shaders/simple.vert", GL_VERTEX_SHADER),
	frag_shader(src_path + "/shaders/simple.frag", GL_FRAGMENT_SHADER),
	tx() {

	program = glCreateProgram();
	glAttachShader(program, vert_shader.handle);
	glAttachShader(program, frag_shader.handle);
	glLinkProgram(program);
	glUseProgram(program);

	float size = 1.0f;
	float vertices[] = {
		-size,  size, 0.0f, 0.0f, // Top-left
		 size,  size, 1.0f, 0.0f, // Top-right
		 size, -size, 1.0f, 1.0f, // Bottom-right
		-size, -size, 0.0f, 1.0f  // Bottom-left
	};

	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLint posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

	GLint texAttrib = glGetAttribLocation(program, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));

	GLuint elements[] = {
    	0, 1, 2,
    	2, 3, 0
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}


void Renderer::update() {
	tx.update();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


}
