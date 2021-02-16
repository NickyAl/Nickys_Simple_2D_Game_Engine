#pragma once
#include <string>
#include <vector>
#include "Window.h"


//MOTHER CLASS FOR ALL OBJECTS
class Object
{
protected:
	int width, height;				//Width and Height
	int red, green, blue, alpha;		//Color if there is no texture
	SDL_Texture* texture;  //Texture (2D image for the figure)
	bool hasCollision;

	std::vector<SDL_Texture*> animation;
	unsigned int animFrames;

public:
	int xCoord, yCoord;				//Coordinates will need to change a lot in the event poll which means we would need to change them directly 

	Object();
	Object(int w, int h, int x, int y, int r, int g, int b, int a, bool collsn);
	Object(int w, int h, int x, int y, const std::string& image_path, bool collsn);
	~Object();

	//Renders the texture or if there isnt one a rectangle filled with the color
	void draw()const;

	//Sprites and Textures
	SDL_Texture* LoadTexture(std::string filepath);
	void loadAnim(const std::string& filepath, int frames);

	void setTexture(SDL_Texture* newTexture) { texture = newTexture; }

	void updateSprite(int currentFrame) { setTexture(animation[currentFrame % animFrames]); }

	//SETTERS AND GETTERS
	void setW(int w) { width = w; }
	int getW()const { return width; }

	void setH(int h) { height = h; }
	int getH()const { return height; }

	void setX(int x) { xCoord = x; }
	int getX()const { return xCoord; }

	void setY(int y) { yCoord = y; }
	int getY()const { return yCoord; }

	void setCollision(bool c) { hasCollision = c; }
	bool getCollision() { return hasCollision; }

	void setColor(int r, int g, int b, int a) { red = r; green = g; blue = b; alpha = a; }

	void setTexture(std::string filepath) { texture = LoadTexture(filepath); }
	
	//movement
	void moveX(int x) { xCoord += x; }
	void moveY(int y) { yCoord += y; }
	
};