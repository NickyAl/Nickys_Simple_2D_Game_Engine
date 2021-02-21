#pragma once
#include <string>
#include <vector>
#include "Window.h"


//MOTHER CLASS FOR ALL OBJECTS
class Object
{
private:
	float width, height;				//Width and Height
	float xCoord, yCoord;
	int red, green, blue, alpha;		//Color if there is no texture
	SDL_Texture* texture;  //Texture (2D image for the figure)
	bool hasCollision;

	std::vector<SDL_Texture*> animation;
	short int animFrames;


public:

	Object();
	Object(float w, float h, float x, float y, int r, int g, int b, int a, bool collsn);
	Object(float w, float h, float x, float y, const std::string& image_path, bool collsn);
	~Object();

	//Renders the texture or if there isnt one a rectangle filled with the color
	void draw()const;

	//Sprites and Textures
	SDL_Texture* LoadTexture(std::string filepath);
	void loadAnim(const std::string& filepath, short int frames);

	void setTexture(SDL_Texture* newTexture) { texture = newTexture; }

	void updateSprite(float tpf, float cooldown);

	//SETTERS AND GETTERS
	void setW(float w) { width = w; }
	float getW()const { return width; }

	void setH(float h) { height = h; }
	float getH()const { return height; }

	void setX(float x) { xCoord = x; }
	float getX()const { return xCoord; }

	void setY(float y) { yCoord = y; }
	float getY()const { return yCoord; }

	void setCollision(bool c) { hasCollision = c; }
	bool getCollision() { return hasCollision; }

	void setColor(int r, int g, int b, int a) { red = r; green = g; blue = b; alpha = a; }

	void setTexture(std::string filepath) { texture = LoadTexture(filepath); }
	
	//movement
	void moveX(float x) { xCoord += x; }
	void moveY(float y) { yCoord += y; }
};