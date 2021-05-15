#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Tools.h"

Player::Player() :
	collisionBox(Object(40 * RS, 65 * RS, 280 * RS, 180 * RS, 0, 255, 0, 255, true)),
	sprite(Object(55 * RS, 75 * RS, 272 * RS, 180 * RS, 255, 255, 0, 255, true)),
	canJump(true), hasJumped(false), lookingRight(true), RS(0.0f)
{}

Player::Player(float rs) : Player()
{
	RS = rs;
}

SDL_Texture* Player::LoadTexture(const std::string& filepath)
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

void Player::loadAnim(const std::string& filepath, short int frames/*, std::vector<SDL_Texture*>& animation, short int& framesToBeSet*/)
{
	std::string path;
	std::vector<SDL_Texture*> animation;

	for (int i = 0; i < frames; i++)
	{
		path = filepath;
		path += Tools::intToString(i);
		path += ".png";

		animation.push_back(LoadTexture(path));	
	}

	/*framesToBeSet = frames;*/
	this->animations.push_back(PlayerAnimation{ animation, frames });
}

void Player::updateSprite(float tpf)
{

	static float timer = 0;
	static short int frame = 0;
	static short int jumpFrame = 0;

	float cooldown = 0.025f;
	int divider = 25;

	timer += tpf;

	//set cooldown between frames of the animation for each animation
	if (this->hasJumped)
	{
		cooldown = 0.06f;
	}
	else if (!this->canJump && this->acclrtn.up == 0)
	{
		cooldown = 0.15f;
	}
	else if (this->acclrtn.right - this->acclrtn.left != 0)
	{
		cooldown = 0.027f;
	}
	else if (this->acclrtn.right - this->acclrtn.left == 0)
	{
		cooldown = 0.15f;
	}

	divider = (int) (1000 * cooldown);

	//calculate frame number
	if (timer > cooldown)
	{
		int check = (int) (timer * 1000);
		if (check / divider > 1)
		{
			frame += check / divider;
		}
		else
		{
			frame++;
			if (this->hasJumped)
				jumpFrame++;
			else
				jumpFrame = 0;
		}

		timer = 0;
	}

	//set to the frame of the correct animation
	//jump
	if (this->hasJumped)
	{
		if (jumpFrame >= this->animations[6].numberOfFrames)
		{
			jumpFrame = this->animations[6].numberOfFrames - 1;
		}

		if (this->lookingRight) //jump right
			this->sprite.setTexture(this->animations[6].frames[jumpFrame]);
		else //jump left
			this->sprite.setTexture(this->animations[7].frames[jumpFrame]);
	}
	//fall
	else if (!this->canJump && this->acclrtn.up == 0)
	{
		if (frame >= this->animations[4].numberOfFrames)
			frame = 0;

		if (this->lookingRight) //fall right
			this->sprite.setTexture(this->animations[4].frames[frame]);
		else //fall left
			this->sprite.setTexture(this->animations[5].frames[frame]);
	}
	//running left
	else if (this->acclrtn.right - this->acclrtn.left < 0)
	{
		if (frame >= this->animations[1].numberOfFrames)
			frame = 0;

		this->sprite.setTexture(this->animations[1].frames[frame]);
	}
	//running right
	else if (this->acclrtn.right - this->acclrtn.left > 0)
	{
		if (frame >= this->animations[0].numberOfFrames)
			frame = 0;

		this->sprite.setTexture(this->animations[0].frames[frame]);
	}
	//idle
	else if (this->acclrtn.right - this->acclrtn.left == 0)
	{
		if (frame >= this->animations[2].numberOfFrames)
			frame = 0;

		if (lookingRight) //dile right
			this->sprite.setTexture(this->animations[2].frames[frame]);
		else //idle left
			this->sprite.setTexture(this->animations[3].frames[frame]);
	}
}

void Player::pollEvents(SDL_Event& event, float tpf)
{
	float TPF = tpf; //time per frame

	if (event.type == SDL_KEYDOWN)
	{
		if (SDLK_a == event.key.keysym.sym)
		{
			this->acclrtn.left = 200 * RS * TPF;
			this->lookingRight = false;
		}

		if (SDLK_d == event.key.keysym.sym)
		{
			this->acclrtn.right = 200 * RS * TPF;
			this->lookingRight = true;
		}

		if (SDLK_w == event.key.keysym.sym)
		{
			if (canJump)
				this->hasJumped = true;
		}
		if (SDLK_s == event.key.keysym.sym)
			this->acclrtn.down = 180 * RS * TPF;

	}
	else if(event.type == SDL_KEYUP)
	{
		if (SDLK_a == event.key.keysym.sym)
			this->acclrtn.left = 0;

		if (SDLK_d == event.key.keysym.sym)
			this->acclrtn.right = 0;

		if (SDLK_w == event.key.keysym.sym)
			this->acclrtn.up = 0;

		if (SDLK_s == event.key.keysym.sym)
			this->acclrtn.down = 0;
	}
}

void Player::draw() const
{
	//this->collisionBox.draw();
	this->sprite.draw();
}

void Player::gravity(float TPF)
{
	static float jumpTimer = 0;
	static float counter = 10;
	static float fallingCounter = 0;

	if (this->hasJumped)
	{
		if (jumpTimer < 0.4)
		{
			this->acclrtn.up = 72 * RS * TPF * counter;
			counter -= TPF * 10;
			jumpTimer += TPF;
		}
		else
		{
			counter = 10;
			this->acclrtn.up = 0;
			jumpTimer = 0;
			this->hasJumped = false;
		}
	}

	this->acclrtn.down = 350 * RS * TPF;
}



//SETTERS
void Player::setCollisionBox(float w, float h, float x, float y, const char* texture)
{
	this->collisionBox.setW(w);
	this->collisionBox.setH(h);
	this->collisionBox.setX(x);
	this->collisionBox.setY(y);
	this->collisionBox.setTexture(texture);
}

void Player::setCollisionBox(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->collisionBox.setW(w);
	this->collisionBox.setH(h);
	this->collisionBox.setX(x);
	this->collisionBox.setY(y);
	this->collisionBox.setColor(r, g, b, a);
}

void Player::setSprite(float w, float h, float x, float y, const char* texture)
{
	this->sprite.setW(w);
	this->sprite.setH(h);
	this->sprite.setX(x);
	this->sprite.setY(y);
	this->sprite.setTexture(texture);
}

void Player::updatePosition()
{
	if (acclrtn.none())
		return;

	this->collisionBox.moveX((acclrtn.right - acclrtn.left));
	this->collisionBox.moveY((acclrtn.down - acclrtn.up));

	this->sprite.setX(collisionBox.getX() - 8 * RS);
	this->sprite.setY(collisionBox.getY());
}