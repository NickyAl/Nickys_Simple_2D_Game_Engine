#pragma once
#include "Object.h"
#include <string>

class Player
{
protected:
	Object collisionBox;

private:
	struct Acceleration
	{
		int left = 0;
		int right = 0;
		int up = 0;
		int down = 0;

		bool none() { return left == 0 && right == 0 && up == 0 && down == 0; }
	};

	Acceleration acclrtn;

public:
	Player();

	void pollEvents(SDL_Event& event, float rs);

	void draw()const;

	//SETTERS and GETTERS

	void setBody(int w, int h, int x, int y, const char* texture);
	void setBody(int w, int h, int x, int y, int r, int g, int b, int a);

	Object& getCollisionBox() { return collisionBox; }
	Acceleration& getAcclrtn() { return acclrtn; }

	int getLocX() { return collisionBox.xCoord; }
	int getLocY() { return collisionBox.yCoord; }
	void setLocX(int x) { collisionBox.xCoord = x; }
	void setLocY(int y) { collisionBox.yCoord = y; }

	int getH() { return collisionBox.getH(); }
	int getW() { return collisionBox.getW(); }

	int getAcsLeft() { return acclrtn.left; }
	int getAcsRight() { return acclrtn.right; }
	int getAcsUp() { return acclrtn.up; }
	int getAcsDown() { return acclrtn.down; }

	void updatePosition();
};

