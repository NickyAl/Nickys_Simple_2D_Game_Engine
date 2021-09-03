#pragma once
#include "Rect.h"
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


//Object is an upgraded Rect with the main difference is that it can have collision
class Object : public Rect
{
private:	
	bool hasCollision;

public:
	Object();
	Object(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool collsn);
	Object(float w, float h, float x, float y, const std::string& image_path, bool collsn);
	Object(float w, float h, float x, float y, SDL_Texture* texture, bool collsn);
	~Object();

	void setCollision(bool c) { hasCollision = c; }
	bool getCollision() { return hasCollision; }
};