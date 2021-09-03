#include "Animation.h"

Animation::Animation(const std::string& filepath, short int frames)
{
	this->numberOfFrames = frames;
	std::string path;

	for (int i = 0; i < frames; i++)
	{
		path = filepath;
		path += std::to_string(i);
		path += ".png";

		animation.push_back(LoadFrame(path));
	}
}

SDL_Texture* Animation::LoadFrame(const std::string& filepath)
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