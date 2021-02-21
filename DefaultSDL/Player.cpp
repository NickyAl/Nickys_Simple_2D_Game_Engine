#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Tools.h"

Player::Player()
{
	collisionBox.setW(100);
	collisionBox.setH(150);
	collisionBox.setX(100);
	collisionBox.setY(150);
	collisionBox.setColor(0, 255, 0, 255);

	sprite.setW(10);
	sprite.setH(15);
	sprite.setX(100);
	sprite.setY(150);
	sprite.setColor(255, 255, 0, 255);

	hasJumped = false;
	lookingRight = true;
}

SDL_Texture* Player::LoadTexture(std::string filepath)
{
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurf = IMG_Load(filepath.c_str());

	if (loadedSurf == nullptr)
	{
		std::cerr << "Failed to load pawn texture\n";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(Window::renderer, loadedSurf);
		if (newTexture == nullptr)
		{
			std::cerr << "Failed to create texture for pawn\n";
		}
		SDL_FreeSurface(loadedSurf);
	}

	return newTexture;
}

void Player::loadAnim(const std::string& filepath, short int frames, std::vector<SDL_Texture*>& animation, short int& forFrames)
{
	std::string path;

	for (int i = 0; i < frames; i++)
	{
		path = filepath;
		path += Tools::intToString(i);
		path += ".png";

		animation.push_back(LoadTexture(path));	
	}

	forFrames = frames;
}

void Player::updateSprite(float tpf)
{

	static float timer = 0;
	static short int frame = 0;
	static short int jumpFrame = 0;

	float cooldown = 0.025;
	int divider = 25;

	timer += tpf;

	//set cooldown between frames of the animation for each animation
	if (hasJumped)
	{
		cooldown = 0.06;
	}
	else if (!canJump && acclrtn.up == 0)
	{
		cooldown = 0.15;
	}
	else if (acclrtn.right - acclrtn.left != 0)
	{
		cooldown = 0.027;
	}
	else if (acclrtn.right - acclrtn.left == 0)
	{
		cooldown = 0.15;
	}

	divider = 1000 * cooldown;

	//calculate frame number
	if (timer > cooldown)
	{
		int check = timer * 1000;
		if (check / divider > 1)
		{
			frame += check / divider;
		}
		else
		{
			frame++;
			if (hasJumped)
				jumpFrame++;
			else
				jumpFrame = 0;
		}

		timer = 0;
	}

	//set to the frame of the right animation
	if (hasJumped)
	{
		if (jumpFrame >= jumpRightFrames)
		{
			jumpFrame = jumpRightFrames - 1;
		}

		if (lookingRight)
			this->sprite.setTexture(jumpRight[jumpFrame]);
		else
			this->sprite.setTexture(jumpLeft[jumpFrame]);
	}
	else if (!canJump && acclrtn.up == 0)
	{
		if (frame >= fallRightFrames)
			frame = 0;

		if (lookingRight)
			this->sprite.setTexture(fallRight[frame]);
		else
			this->sprite.setTexture(fallLeft[frame]);
	}
	else if (acclrtn.right - acclrtn.left < 0)
	{
		if (frame >= runLeftFrames)
			frame = 0;

		this->sprite.setTexture(runLeft[frame]);
	}
	else if (acclrtn.right - acclrtn.left > 0)
	{
		if (frame >= runRightFrames)
			frame = 0;

		this->sprite.setTexture(runRight[frame]);
	}
	else if (acclrtn.right - acclrtn.left == 0)
	{
		if (frame >= idleRightFrames)
			frame = 0;

		if (lookingRight)
			this->sprite.setTexture(idleRight[frame]);
		else
			this->sprite.setTexture(idleLeft[frame]);
	}
}

void Player::pollEvents(SDL_Event& event, float tpf)
{
	float TPF = tpf;
	int pixelMovement;

	if (event.type == SDL_KEYDOWN)
	{
		if (SDLK_a == event.key.keysym.sym)
		{
			acclrtn.left = 200 * RS * TPF;
			lookingRight = false;
		}

		if (SDLK_d == event.key.keysym.sym)
		{
			acclrtn.right = 200 * RS * TPF;
			lookingRight = true;
		}

		if (SDLK_w == event.key.keysym.sym)
		{
			if (canJump)
				hasJumped = true;
		}
		if (SDLK_s == event.key.keysym.sym)
			acclrtn.down = 180 * RS * TPF;

	}
	else if(event.type == SDL_KEYUP)
	{
		if (SDLK_a == event.key.keysym.sym)
			acclrtn.left = 0;

		if (SDLK_d == event.key.keysym.sym)
			acclrtn.right = 0;

		if (SDLK_w == event.key.keysym.sym)
			acclrtn.up = 0;

		if (SDLK_s == event.key.keysym.sym)
			acclrtn.down = 0;
	}
}

void Player::draw() const
{
	//collisionBox.draw();
	sprite.draw();
}

void Player::gravity(float TPF)
{
	static float jumpTimer = 0;
	static float counter = 10;
	static float fallingCounter = 0;

	if (hasJumped)
	{
		if (jumpTimer < 0.4)
		{
			acclrtn.up = 72 * RS * TPF * counter;
			counter -= TPF * 10;
			jumpTimer += TPF;
		}
		else
		{
			counter = 10;
			acclrtn.up = 0;
			jumpTimer = 0;
			hasJumped = false;
		}
	}

	acclrtn.down = 350 * RS * TPF;
}



//SETTERS

void Player::setCollisionBox(int w, int h, float x, float y, const char* texture)
{
	collisionBox.setW(w);
	collisionBox.setH(h);
	collisionBox.setX(x);
	collisionBox.setY(y);
	collisionBox.setTexture(texture);
}

void Player::setCollisionBox(int w, int h, float x, float y, int r, int g, int b, int a)
{
	collisionBox.setW(w);
	collisionBox.setH(h);
	collisionBox.setX(x);
	collisionBox.setY(y);
	collisionBox.setColor(r, g, b, a);
}

void Player::setSprite(int w, int h, int x, int y, const char* texture)
{
	sprite.setW(w);
	sprite.setH(h);
	sprite.setX(x);
	sprite.setY(y);
	sprite.setTexture(texture);
}

void Player::updatePosition()
{
	if (acclrtn.none())
		return;

	collisionBox.moveX((acclrtn.right - acclrtn.left));
	collisionBox.moveY((acclrtn.down - acclrtn.up));

	sprite.setX(collisionBox.getX() - 8 * RS);
	sprite.setY(collisionBox.getY());
}