#pragma once
#include "Object.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Window.h"
#include "Animation.h"

class Player
{
private:
	Object collisionBox;
	Object sprite;
	float RS; //resolution setting

	//movement5
	bool hasJumped;
	bool lookingRight;

	struct Acceleration
	{
		float left = 0;
		float right = 0;
		float up = 0;
		float down = 0;

		bool none() { return left == 0 && right == 0 && up == 0 && down == 0; }
		bool noneOnLR() { return left == 0 && right == 0; } //none on left and right
	};

	Acceleration acclrtn;

	std::vector<Animation> animations;
	//index|animation
	//0		running right
	//1		running left
	//2		idle right
	//3		idle left
	//4		fall right
	//5		fall left
	//6		jump right
	//7		jump left
public:
	bool canJump;

	Player();
	Player(float rs);

	void addAnimation(Animation anim) { animations.push_back(anim); }

	void updateSprite(float tpf);

	void pollEvents(SDL_Event& event, float tpf);

	void draw()const;

	void gravity(float TPF);

	void setSprite(float w, float h, float x, float y, SDL_Texture* texture);
	Object& getSprite() { return sprite; }


	//for collision
	void setCollisionBox(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

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

	//update
	void updatePosition();
};