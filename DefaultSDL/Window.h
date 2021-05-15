#pragma once
#include <string>
#include <SDL.h>

class Window
{
private:
	std::string title;
	int width;
	int height;

	float resolutionSetting;
	bool openedSettings;

	bool closed;

	SDL_Window* window;

	bool init();

public:
	static SDL_Renderer* renderer;

	Window();
	Window(const std::string& newTitle, int newWidth, int newHeight);
	~Window();

	bool isClosed()const { return this->closed; }

	void pollEvents(SDL_Event& event);
	void clear() const; //"means to put stuff onto the screen" - youtube dude

	//setters and getters

	void setOpndSttng(bool x) { openedSettings = x; }
	float getRS() { return resolutionSetting; } //get resolution settings
};