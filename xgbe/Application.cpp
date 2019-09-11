//
// Created by Revolware Company on 2019-08-25.
//

#include "Application.h"
#include "Window.h"
#include "KeyboardHandler.h"
#include "Emulation.h"

#include <SDL2/SDL.h>
#include <Log.h>

Application::Application()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		Log::error("Error initializing SDL: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_INIT_FAILED");
	}

	m_window = std::make_unique<Window>();
	m_keyboardHandler = std::make_unique<KeyboardHandler>();

	m_emulation = std::make_unique<Emulation>();

	update();

	m_emulation->start();
}

Application::~Application()
{
	SDL_Quit();
}

void Application::run()
{
	while(!m_quit)
		update();
}

void Application::update()
{
	processEvents();
	m_window->update();
}

void Application::processEvents() noexcept
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				m_quit = true;
				break;

			case SDL_KEYDOWN: {
				const auto command = m_keyboardHandler->handleKeyEvent(*m_emulation, event.key);

				handleKeyCommand(command);
				break;
			}
		}
	}
}

void Application::handleKeyCommand(KeyHandleCommand::Enum command) noexcept
{
	if(command < KeyCommand::Size)
		m_emulation->sendKey(static_cast<KeyCommand::Enum>(command));
	else {
		switch(command) {
			case KeyHandleCommand::PauseOrResume:
				while(!m_emulation->pauseOrResume()) {}
				break;

			case KeyHandleCommand::Step:
				m_emulation->step();
				break;

			case KeyHandleCommand::Quit:
				m_quit = true;
				break;

			case KeyHandleCommand::Up:
			case KeyHandleCommand::Left:
			case KeyHandleCommand::Down:
			case KeyHandleCommand::Right:
			case KeyHandleCommand::A:
			case KeyHandleCommand::B:
			case KeyHandleCommand::Select:
			case KeyHandleCommand::Start:
			case KeyHandleCommand::Unhandled:
				break;
		}
	}
}
