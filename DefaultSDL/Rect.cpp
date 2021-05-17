#include "Rect.h"


Rect::Rect() :
	width(20), height(20), xCoord(0), yCoord(0), red(255), green(255), blue(255), alpha(255), texture(nullptr)
{
}

Rect::Rect(float w, float h, float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
	width(w), height(h), xCoord(x), yCoord(y), red(r), green(g), blue(b), alpha(a), texture(nullptr)
{
}

Rect::Rect(float w, float h, float x, float y, const std::string& image_path) :
	width(w), height(h), xCoord(x), yCoord(y), red(0), green(0), blue(0), alpha(0), texture(nullptr)
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
	SDL_Rect rect = { (int)this->xCoord, (int)this->yCoord, (int)this->width, (int)this->height };
	//Using float and then casting to int because to have thing scale up with resolution I pass values for 640 by 360 and multiply them by RS (resolution setting)
	//and if lets say I multiply them by 3 for 1080p if I use int I wont be able to give it a value that %3 != 0 so I use float

	if (this->texture)
	{
		SDL_RenderCopy(Window::renderer, this->texture, nullptr, &rect);
	}
	else
	{
		SDL_SetRenderDrawColor(Window::renderer, (Uint8)this->red, (Uint8)this->green, (Uint8)this->blue, (Uint8)this->alpha);
		SDL_RenderFillRect(Window::renderer, &rect);
	}
}