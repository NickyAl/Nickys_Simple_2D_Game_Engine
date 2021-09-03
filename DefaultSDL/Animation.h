#pragma once
#include <vector>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include "Window.h"

//constructor's first parameter takes addres of the folder with the frames, second one takes the number of frames
struct Animation
{
	std::vector<SDL_Texture*> animation;
	short int numberOfFrames;

	Animation(const std::string& filepath, short int frames);

private:
	SDL_Texture* LoadFrame(const std::string& filepath);
};

