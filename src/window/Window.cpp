#include <iostream>

#include "Window.h"

namespace window {

Context *Context::instance = nullptr;

void error_callback(int error, const char* description) {
	std::cout << "error " << error << ", " << description << "\n";
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Context::instance->use_window(window, [key, scancode, action, mods](Window *wobj) {
		wobj->handler->on_key(key, scancode, action, mods);
	});
}


void character_callback(GLFWwindow* window, unsigned int code) {
	Context::instance->use_window(window, [code](Window *wobj) {
		wobj->handler->on_char(code);
	});
}

Context::Context() {
	if (!glfwInit()) {
		// Handle initialization failure
	}
	instance = this;
	glfwSetErrorCallback(error_callback);
}


Context::~Context() {
	glfwTerminate();
}


void Context::use_window(GLFWwindow *wobj, std::function<void(Window *)> callback) const {
	if (wmap.count(wobj) > 0) {
		callback(wmap.at(wobj));
	}
}


void Context::register_window(Window *wobj) {
	wobj->modify_if([this, wobj](GLFWwindow *w) {
		glfwSetKeyCallback(w, key_callback);
		glfwSetCharCallback(w, character_callback);
		wmap.insert(std::make_pair(w, wobj));
	});
}


void Context::process_events() {
	while (true) {
		glfwWaitEvents();
	}
}


Window::Window(Context &c)
	:
	window_impl(glfwCreateWindow(
		800,
		600,
		"Audio",
		nullptr,
		nullptr
	)),
	handler(nullptr) {
	c.register_window(this);
}


Window::~Window() {
	modify_if([](GLFWwindow *w) {
		glfwDestroyWindow(w);
	});
}


void Window::enable_rendering() const {
	modify_if([](GLFWwindow *w) {
		glfwMakeContextCurrent(w);
	});
}


void Window::modify_if(std::function<void(GLFWwindow *)> callback) const {
	if (window_impl) {
		callback(window_impl);
	}
}


}
