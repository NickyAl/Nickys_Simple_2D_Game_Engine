#pragma once
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Window.h"

//we can not deep copy textures so we keep a pointer to each texture pass it around to the objects
struct Texture
{
	SDL_Texture* texture;

	Texture(const std::string& filepath);
	~Texture();

	void LoadTexture(const std::string& filepath); //will make static or private later on
};

