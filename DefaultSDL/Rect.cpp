#include "Rect.h"
#include <SDL_image.h>
#include <iostream>

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a) :
	width(w), height(h), xCoord(x), yCoord(y), red(r), green(g), blue(b), alpha(a)
{
}

Rect::Rect(int w, int h, int x, int y, const std::string& image_path) :
	width(w), height(h), xCoord(x), yCoord(y)
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

Rect::~Rect()
{
	SDL_DestroyTexture(texture);
}

void Rect::draw() const
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

void Rect::pollEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{

		default:
			break;
		}
	}
}
