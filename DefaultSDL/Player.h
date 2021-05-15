#pragma once
#include "Object.h"
#include <string>

class Player
{
private:
	Object collisionBox;
	Object sprite;

	//movement
	float RS; //resolution setting

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

	bool hasJumped;
	bool lookingRight;

	struct PlayerAnimation
	{
		std::vector<SDL_Texture*> frames;
		short int numberOfFrames;
	};

	//animations
	std::vector<PlayerAnimation> animations;
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

	SDL_Texture* LoadTexture(const std::string& filepath);
	void loadAnim(const std::string& filepath, short int frames/*, std::vector<SDL_Texture*>& animation, short int& forFrames*/);
	void updateSprite(float tpf);

	void pollEvents(SDL_Event& event, float tpf);

	void draw()const;

	void gravity(float TPF);

	void setSprite(float w, float h, float x, float y, const char* texture);
	Object& getSprite() { return sprite; }

	//for collision
	void setCollisionBox(float w, float h, float x, float y, const char* texture);
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

