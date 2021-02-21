#include "Object.h"
#include "Tools.h"
#include <SDL_image.h>
#include <iostream>



Object::Object() :
	width(40), height(40), xCoord(500), yCoord(500), red(255), green(0), blue(0), alpha(255), hasCollision(false)
{
}

Object::Object(float w, float h, float x, float y, int r, int g, int b, int a, bool collsn) :
	width(w), height(h), xCoord(x), yCoord(y), red(r), green(g), blue(b), alpha(a), hasCollision(collsn)
{
}

Object::Object(float w, float h, float x, float y, const std::string& image_path, bool collsn) :
	width(w), height(h), xCoord(x), yCoord(y), hasCollision(collsn)
{
	auto surface = IMG_Load(image_path.c_str()); //c_str converts it to a construct pointer
	if (!surface)
	{
		std::cerr << "Failed to create surface\n";
	}

	texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!texture)
	{
		std::cerr << "Failed to create texture\n";
	}

	SDL_FreeSurface(surface);
}

Object::~Object()
{
	SDL_DestroyTexture(texture);
}

void Object::draw() const
{
	SDL_Rect rect = { xCoord, yCoord, width, height };

	if (texture)
	{
		SDL_RenderCopy(Window::renderer, texture, nullptr, &rect);
	}
	else
	{
		SDL_SetRenderDrawColor(Window::renderer, red, green, blue, alpha);
		SDL_RenderFillRect(Window::renderer, &rect);
	}
}


SDL_Texture* Object::LoadTexture(std::string filepath)
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

void Object::loadAnim(const std::string& filepath, short int frames)
{
	animFrames = frames;
	std::string path;

	for (int i = 0; i < frames; i++)
	{
		path = filepath;
		path += Tools::intToString(i);
		path += ".png";

		animation.push_back(LoadTexture(path));	
	}
}

void Object::updateSprite(float tpf, float cooldown)
{
	static float timer = 0;
	static short int frame = 0;

	int divider = 1000 * cooldown;

	timer += tpf;

	if (timer > cooldown)
	{
		int check = timer * 1000;
		if (check / divider > 1)
		{
			frame += check / divider;
		}
		else
			frame++;
		timer = 0;
	}

	if (frame >= animFrames)
		frame = 0;
	
	setTexture(animation[frame]);
}
