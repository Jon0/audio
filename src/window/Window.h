#pragma once

#include <functional>
#include <unordered_map>
#include <GLFW/glfw3.h>

#include "Event.h"

namespace window {

class Window;

class Context {
public:
	static Context *instance;

	Context();
	~Context();

	void use_window(GLFWwindow *wobj, std::function<void(Window *)> callback) const;
	void register_window(Window *wobj);
	void process_events();

private:
	std::unordered_map<GLFWwindow *, Window *> wmap;

};

class Window {
public:
	Window(Context &c);
	~Window();

	void enable_rendering() const;

	void modify_if(std::function<void(GLFWwindow *)> callback) const;
	
	EventHandler *const handler;

private:
	GLFWwindow *const window_impl;


};

}
