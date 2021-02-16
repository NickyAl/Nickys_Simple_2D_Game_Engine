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
}

void Player::pollEvents(SDL_Event& event, float rs)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (SDLK_a == event.key.keysym.sym)
			acclrtn.left = 3 * rs;

		if (SDLK_d == event.key.keysym.sym)
			acclrtn.right = 3 * rs;

		if (SDLK_w == event.key.keysym.sym)
			acclrtn.up = 3 * rs;

		if (SDLK_s == event.key.keysym.sym)
			acclrtn.down = 3 * rs;
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



//SETTERS

void Player::setCollisionBox(int w, int h, int x, int y, const char* texture)
{
	collisionBox.setW(w);
	collisionBox.setH(h);
	collisionBox.setX(x);
	collisionBox.setY(y);
	collisionBox.setTexture(texture);
}

void Player::setCollisionBox(int w, int h, int x, int y, int r, int g, int b, int a)
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

	collisionBox.moveX(acclrtn.right - acclrtn.left);
	collisionBox.moveY(acclrtn.down - acclrtn.up);

	sprite.setX(collisionBox.xCoord - 10 * RS);
	sprite.setY(collisionBox.yCoord);
}
