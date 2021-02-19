#pragma once
#include "Window.h"
#include <string>

class Rect
{
private:
	float width, height;
	float xCoord, yCoord;
	int red, green, blue, alpha;
	SDL_Texture* texture;

	SDL_Texture** animation;

public:

	Rect(float w, float h, float x, float y, int r, int g, int b, int a);
	Rect(float w, float h, float x, float y, const std::string& image_path);
	~Rect();

	void draw()const;
	void pollEvents(SDL_Event& event);

	void setX(float x) { xCoord = x; }
	void setY(float y) { yCoord = y; }

	void moveX(float x) { xCoord += x; }
	void moveY(float y) { yCoord += y; }
};