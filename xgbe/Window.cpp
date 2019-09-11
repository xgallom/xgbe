//
// Created by Revolware Company on 2019-08-25.
//

#include "Window.h"

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <Log.h>

Window::Window()
{
	createWindow();

	if(!(m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED))) {
		Log::error("Error creating renderer: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_CREATE_RENDERER_FAILED");
	}

	if(SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE) != 0) {
		Log::error("Error setting renderer blend mode: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_SET_RENDERER_DRAW_BLEND_MODE_FAILED");
	}

	if(SDL_RenderSetIntegerScale(m_renderer, SDL_TRUE) != 0) {
		Log::error("Error setting integer render scale: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_RENDER_SET_INTEGER_SCALE_FAILED");
	}

	if(SDL_RenderSetLogicalSize(m_renderer, DisplayWidth, DisplayHeight) != 0) {
		Log::error("Error setting logical render size: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_RENDER_SET_LOGICAL_SIZE_FAILED");
	}

	clear();
	SDL_RenderPresent(m_renderer);
}

Window::~Window()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Window::update()
{
	const SDL_Rect rect = {0, 0, DisplayWidth, DisplayHeight};
	setColor(255, 0, 255);

	SDL_RenderDrawRect(m_renderer, &rect);
	SDL_RenderPresent(m_renderer);
}

void Window::createWindow()
{
	if(ApplicationConfig.windowed) {
		if(!(m_window = SDL_CreateWindow(
				"X GameBoy Emulator",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				DisplayWidth, DisplayHeight,
				0)
		)) {
			Log::error("Error creating window: ", SDL_GetError(), "\n");
			throw std::runtime_error("SDL_CREATE_WINDOW_FAILED");
		}
	} else {
		SDL_DisplayMode displayMode;

		if(SDL_GetDesktopDisplayMode(0, &displayMode) != 0) {
			Log::error("Error getting desktop display mode: ", SDL_GetError(), "\n");
			throw std::runtime_error("SDL_GET_DESKTOP_DISPLAY_MODE_FAILED");
		}

		if(!(m_window = SDL_CreateWindow(
				"X GameBoy Emulator",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				displayMode.w, displayMode.h,
				SDL_WINDOW_FULLSCREEN)
		)) {
			Log::error("Error creating window: ", SDL_GetError(), "\n");
			throw std::runtime_error("SDL_CREATE_WINDOW_FAILED");
		}
	}
}

void Window::clear()
{
	setColor(0, 0, 0);

	if(SDL_RenderClear(m_renderer) != 0) {
		Log::error("Error clearing render: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_RENDER_CLEAR_FAILED");
	}
}

void Window::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	if(SDL_SetRenderDrawColor(m_renderer, r, g, b, SDL_ALPHA_OPAQUE) != 0) {
		Log::error("Error setting render color: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_SET_RENDER_DRAW_COLOR_FAILED");
	}
}

void Window::drawPoint(int x, int y)
{
	if(SDL_RenderDrawPoint(m_renderer, x, y) != 0) {
		Log::error("Error rendering point at [", x, ", ", y, "]: ", SDL_GetError(), "\n");
		throw std::runtime_error("SDL_RENDER_DRAW_POINT_FAILED");
	}
}
