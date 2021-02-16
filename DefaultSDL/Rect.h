#pragma once
#include "Window.h"
#include <string>

class Rect
{
private:
	int width, height;
	int xCoord, yCoord;
	int red, green, blue, alpha;
	SDL_Texture* texture;

	SDL_Texture** animation;

public:

	Rect(int w, int h, int x, int y, int r, int g, int b, int a);
	Rect(int w, int h, int x, int y, const std::string& image_path);
	~Rect();

	void draw()const;
	void pollEvents(SDL_Event& event);

	void setX(int x) { xCoord = x; }
	void setY(int y) { yCoord = y; }

	void moveX(int x) { xCoord += x; }
	void moveY(int y) { yCoord += y; }
};