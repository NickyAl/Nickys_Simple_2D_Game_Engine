#include "Texture.h"

Texture::Texture(const std::string& filepath)
{
	LoadTexture(filepath);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::LoadTexture(const std::string& filepath)
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

	this->texture = newTexture;
}