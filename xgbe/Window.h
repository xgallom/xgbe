//
// Created by Revolware Company on 2019-08-25.
//

#ifndef XGBE_WINDOW_H
#define XGBE_WINDOW_H

#include <cstdint>

class SDL_Window;
class SDL_Renderer;

class Window {
public:
	static constexpr int
			DisplayWidth = 160, DisplayHeight = 144;

	Window();
	~Window();

	void update();

private:
	void createWindow();
	void clear();
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	void drawPoint(int x, int y);

	SDL_Window *m_window = nullptr;
	SDL_Renderer *m_renderer = nullptr;
};


#endif //XGBE_WINDOW_H
