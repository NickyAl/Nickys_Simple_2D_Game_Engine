#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

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
}

void Player::pollEvents(SDL_Event& event, float tpf)
{
	static float jumpTimer = 0;

	float TPF = tpf;
	int pixelMovement;

	if (event.type == SDL_KEYDOWN)
	{
		if (SDLK_a == event.key.keysym.sym)
			acclrtn.left = 180 * RS * TPF;

		if (SDLK_d == event.key.keysym.sym)
			acclrtn.right = 180 * RS * TPF;

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
		{
			acclrtn.up = 0;
			jumpTimer -= tpf;
			if (jumpTimer < 0)
				jumpTimer = 0;
		}
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

	if (hasJumped)
	{
		if (jumpTimer < 0.4)
		{
			acclrtn.up = 550 * RS * TPF;
			jumpTimer += TPF;
		}
		else
		{
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

	std::cout << collisionBox.getX() << " " << collisionBox.getY() << '\n';

	sprite.setX(collisionBox.getX() - 8 * RS);
	sprite.setY(collisionBox.getY());
}

void Player::updateState()
{
	if (acclrtn.none())
		state = idle;
	else
		state = running;
}

void Player::updatePlayerSprite(int currentFrame)
{
	sprite.updateSprite(currentFrame);
	//TO FINISH
}
