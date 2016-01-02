#pragma once

namespace window {

class EventHandler {
public:
	virtual void on_key(int key, int scancode, int action, int mods) = 0;
	virtual void on_char(unsigned int code) = 0;

};


class CommandHandler : public EventHandler {
public:
	CommandHandler();
	void on_key(int key, int scancode, int action, int mods) override;
	void on_char(unsigned int code) override;
};


}
