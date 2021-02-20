#pragma once
#include "Object.h"
#include <string>

class Player
{
protected:
	Object collisionBox;
	Object sprite;

private:
	//movement
	int RS = 0;

	struct Acceleration
	{
		float left = 0;
		float right = 0;
		float up = 0;
		float down = 0;

		bool none() { return left == 0 && right == 0 && up == 0 && down == 0; }
	};

	Acceleration acclrtn;

	bool hasJumped = false;

	enum State
	{
		idle = 0,
		running = 1
	};

	State state;

public:
	bool canJump;

	Player();
	Player(int rs) { RS = rs; }

	void pollEvents(SDL_Event& event, float tpf);

	void draw()const;

	void gravity(float TPF);

	//SETTERS and GETTERS
	void setCollisionBox(int w, int h, float x, float y, const char* texture);
	void setCollisionBox(int w, int h, float x, float y, int r, int g, int b, int a);

	void setSprite(int w, int h, int x, int y, const char* texture);
	Object& getSprite() { return sprite; }

	Object& getCollisionBox() { return collisionBox; }
	Acceleration& getAcclrtn() { return acclrtn; }

	float getLocX() { return collisionBox.getX(); }
	float getLocY() { return collisionBox.getY(); }
	void setLocX(float x) { collisionBox.setX(x); }
	void setLocY(float y) { collisionBox.setY(y); }

	float getH() { return collisionBox.getH(); }
	float getW() { return collisionBox.getW(); }

	float getAcsLeft() { return acclrtn.left; }
	float getAcsRight() { return acclrtn.right; }
	float getAcsUp() { return acclrtn.up; }
	float getAcsDown() { return acclrtn.down; }

	void updatePosition();
	void updateState();
	void updatePlayerSprite(int currentFrame);
};

