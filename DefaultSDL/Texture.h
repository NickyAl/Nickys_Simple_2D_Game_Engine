#pragma once
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Window.h"

class Texture
{
	SDL_Texture* texture;

	SDL_Texture* LoadTexture(const std::string& filepath);
};

