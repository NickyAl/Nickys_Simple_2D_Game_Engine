#pragma once
#include <string>
#include <SDL.h>

class Window
{
private:
	std::string title;
	int width = 640;
	int height = 360;

	float resolutionSetting = 1.0f;
	bool openedSettings = false;

	bool closed = false;

	SDL_Window* window = nullptr;

	bool init();

public:
	static SDL_Renderer* renderer;

public:
	Window(const std::string& newTitle, int newWidth, int newHeight);
	~Window();

	bool isClosed()const { return this->closed; }

	void pollEvents(SDL_Event& event);
	void clear() const; //"means to put stuff onto the screen" - youtube dude

	//setters and getters

	void setOpndSttng(bool x) { openedSettings = x; }
	int getRS() { return resolutionSetting; } //get resolution settings
};