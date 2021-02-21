#pragma once
#include "Object.h"
#include <string>

class Player
{
private:
	Object collisionBox;
	Object sprite;

	//movement
	int RS = 0;

	struct Acceleration
	{
		float left = 0;
		float right = 0;
		float up = 0;
		float down = 0;

		bool none() { return left == 0 && right == 0 && up == 0 && down == 0; }
		bool noneOnLR() { return left == 0 && right == 0; }
	};

	Acceleration acclrtn;

	bool hasJumped = false;
	bool lookingRight = true;

	//animations
	std::vector<SDL_Texture*> runLeft;
	short int runLeftFrames;
	std::vector<SDL_Texture*> runRight;
	short int runRightFrames;
	std::vector<SDL_Texture*> idleRight;
	short int idleRightFrames;
	std::vector<SDL_Texture*> idleLeft;
	short int idleLeftFrames;
	std::vector<SDL_Texture*> fallRight;
	short int fallRightFrames;
	std::vector<SDL_Texture*> fallLeft;
	short int fallLeftFrames;
	std::vector<SDL_Texture*> jumpRight;
	short int jumpRightFrames;
	std::vector<SDL_Texture*> jumpLeft;
	short int jumpLeftFrames;

public:
	bool canJump;

	Player();
	Player(int rs) { RS = rs; }

	SDL_Texture* LoadTexture(std::string filepath);
	void loadAnim(const std::string& filepath, short int frames, std::vector<SDL_Texture*>& animation, short int& forFrames);
	void updateSprite(float tpf);

	void pollEvents(SDL_Event& event, float tpf);

	void draw()const;

	void gravity(float TPF);

	//SETTERS and GETTERS
	//for anims
	std::vector<SDL_Texture*>& getRunLeft() { return runLeft; }
	short int& getRunLeftFrames() { return runLeftFrames; }

	std::vector<SDL_Texture*>& getRunRight() { return runRight; }
	short int& getRunRightFrames() { return runRightFrames; }

	std::vector<SDL_Texture*>& getIdleRight() { return idleRight; }
	short int& getIdleRightFrames() { return idleRightFrames; }

	std::vector<SDL_Texture*>& getIdleLeft() { return idleLeft; }
	short int& getIdleLeftFrames() { return idleLeftFrames; }

	std::vector<SDL_Texture*>& getFallRight() { return fallRight; }
	short int& getFallRightFrames() { return fallRightFrames; }

	std::vector<SDL_Texture*>& getFallLeft() { return fallLeft; }
	short int& getFallLeftFrames() { return fallLeftFrames; }

	std::vector<SDL_Texture*>& getJumpRight() { return jumpRight; }
	short int& getJumpRightFrames() { return jumpRightFrames; }

	std::vector<SDL_Texture*>& getJumpLeft() { return jumpLeft; }
	short int& getJumpLeftFrames() { return jumpLeftFrames; }

	void setSprite(int w, int h, int x, int y, const char* texture);
	Object& getSprite() { return sprite; }

	//for collision
	void setCollisionBox(int w, int h, float x, float y, const char* texture);
	void setCollisionBox(int w, int h, float x, float y, int r, int g, int b, int a);

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

