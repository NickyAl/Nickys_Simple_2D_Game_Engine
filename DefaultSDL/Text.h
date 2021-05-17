#pragma once
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class Text
{
private:
	SDL_Texture* text_texture = nullptr;
	mutable SDL_Rect text_rect;

public:
	Text(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);

	void display(int x, int y, SDL_Renderer* renderer)const;

	static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);
};