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
	Rect(float w, float h, float x, float y, SDL_Texture* texture);
	~Rect();

	void draw()const;

	//setter and getters
	void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { red = r; green = g; blue = b; alpha = a; }

	void setX(float x) { xCoord = x; }
	float getX()const { return xCoord; }

	void setY(float y) { yCoord = y; }
	float getY()const { return yCoord; }

	void setW(float w) { width = w; }
	float getW()const { return width; }

	void setH(float h) { height = h; }
	float getH()const { return height; }

	//movement
	void moveX(float x) { xCoord += x; }
	void moveY(float y) { yCoord += y; }

	//textures
	void setTexture(SDL_Texture* newTexture) { texture = newTexture; }
};