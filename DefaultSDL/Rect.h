#pragma once
#include "Window.h"
#include <string>
#include <SDL_image.h>
#include <iostream>

class Rect
{
protected:
	float width, height;
	float xCoord, yCoord;
	uint8_t red, green, blue, alpha;  //Color if there is no texture
	SDL_Texture* texture;				//Texture (2D image for the figure)

public:
	Rect();
	Rect(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	Rect(float w, float h, float x, float y, const std::string& image_path);
	~Rect();

	void draw()const;

	void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { red = r; green = g; blue = b; alpha = a; }

	void setX(float x) { xCoord = x; }
	void setY(float y) { yCoord = y; }

	//movement
	void moveX(float x) { xCoord += x; }
	void moveY(float y) { yCoord += y; }
};