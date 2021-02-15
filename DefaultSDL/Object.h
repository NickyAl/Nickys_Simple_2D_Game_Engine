#pragma once
#include <string>
#include "Window.h"

//MOTHER CLASS FOR ALL OBJECTS
class Object
{
protected:
	int width, height;				//Width and Height
	int red, green, blue, alpha;		//Color if there is no texture
	SDL_Texture* _texture;  //Texture (2D image for the figure)

public:
	int xCoord, yCoord;				//Coordinates will need to change a lot in the event poll which means we would need to change them directly 

	Object();
	Object(int w, int h, int x, int y, int r, int g, int b, int a);
	Object(int w, int h, int x, int y, const std::string& image_path);
	~Object();

	//Renders the texture or if there isnt one a rectangle filled with the color
	void draw()const;

	//loadTexture is used as a setter
	SDL_Texture* LoadTexture(std::string filepath);

	//SETTERS AND GETTERS

	void setW(int w) { width = w; }
	int getW()const { return width; }

	void setH(int h) { height = h; }
	int getH()const { return height; }

	void setX(int x) { xCoord = x; }
	int getX()const { return xCoord; }

	void setY(int y) { yCoord = y; }
	int getY()const { return yCoord; }

	void setColor(int r, int g, int b, int a) { red = r; green = g; blue = b; alpha = a; }

	void setTexture(const char* filepath) { _texture = LoadTexture(filepath); }
	void setTexture(char* filepath) { _texture = LoadTexture(filepath); }
	void setTexture(std::string filepath) { _texture = LoadTexture(filepath); }
	
	//movement
	void moveX(int x) { xCoord += x; }
	void moveY(int y) { yCoord += y; }
};