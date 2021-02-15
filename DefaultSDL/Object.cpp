#include "Object.h"
#include <SDL_image.h>
#include <iostream>



Object::Object() :
	width(40), height(40), xCoord(500), yCoord(500), red(255), green(0), blue(0), alpha(255)
{
}

Object::Object(int w, int h, int x, int y, int r, int g, int b, int a) :
	width(w), height(h), xCoord(x), yCoord(y), red(r), green(g), blue(b), alpha(a)
{
}

Object::Object(int w, int h, int x, int y, const std::string& image_path) :
	width(w), height(h), xCoord(x), yCoord(y)
{
	auto surface = IMG_Load(image_path.c_str()); //c_str converts it to a construct pointer
	if (!surface)
	{
		std::cerr << "Failed to create surface\n";
	}

	_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!_texture)
	{
		std::cerr << "Failed to create texture\n";
	}

	SDL_FreeSurface(surface);
}

Object::~Object()
{
	SDL_DestroyTexture(_texture);
}

void Object::draw() const
{
	SDL_Rect rect = { xCoord, yCoord, width, height };

	if (_texture)
	{
		SDL_RenderCopy(Window::renderer, _texture, nullptr, &rect);
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