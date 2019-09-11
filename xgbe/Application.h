//
// Created by Revolware Company on 2019-08-25.
//

#ifndef XGBE_APPLICATION_H
#define XGBE_APPLICATION_H

#include "KeyHandleCommand.h"

#include <memory>

class Window;
class KeyboardHandler;
class Emulation;

class Application {
public:
	Application();
	~Application();

	void run();

private:
	void update();
	void processEvents() noexcept;
	void handleKeyCommand(KeyHandleCommand::Enum command) noexcept;

	std::unique_ptr<Window> m_window = {};
	std::unique_ptr<KeyboardHandler> m_keyboardHandler = {};
	std::unique_ptr<Emulation> m_emulation = {};

	bool m_quit = false;
};


#endif //XGBE_APPLICATION_H
