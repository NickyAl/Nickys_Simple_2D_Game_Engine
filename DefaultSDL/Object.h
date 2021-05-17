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
	std::vector<SDL_Texture*> animation;
	short int animFrames;


public:
	Object();
	Object(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool collsn);
	Object(float w, float h, float x, float y, const std::string& image_path, bool collsn);
	~Object();

	//Sprites and Textures
	SDL_Texture* LoadTexture(const std::string& filepath);
	void loadAnim(const std::string& filepath, short int frames);
	void setTexture(SDL_Texture* newTexture) { texture = newTexture; }
	void updateSprite(float tpf, float cooldown); //tpf - ticks per frame

	//SETTERS AND GETTERS
	void setW(float w) { width = w; }
	float getW()const { return width; }

	void setH(float h) { height = h; }
	float getH()const { return height; }

	float getX()const { return xCoord; }
	float getY()const { return yCoord; }

	void setCollision(bool c) { hasCollision = c; }
	bool getCollision() { return hasCollision; }

	void setTexture(const std::string& filepath) { texture = LoadTexture(filepath); }
};