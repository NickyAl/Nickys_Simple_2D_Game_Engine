#include <iostream>
#include "Window.h"
#include "Rect.h"
#include "Text.h"
#include "Object.h"
#include "Player.h"
#include "Tools.h"
#include <string>
#include <list>

void pollEvents(Window& window, Player& player1, int resolutionSetting)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		window.pollEvents(event);
		player1.pollEvents(event, resolutionSetting);
	}
}

void pollEventsForMenu(Window& window, Rect& menu)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		window.pollEvents(event);
		menu.pollEvents(event);
	}
}

int main(int argc, char** argv)
{

	Window startMenu("Settings", 200, 300);
	Rect menu(200, 300, 0, 0, "Resources/testMenu.jpg");

	while (!startMenu.isClosed())
	{

		pollEventsForMenu(startMenu, menu);

		startMenu.setOpndSttng(true);

		menu.draw();

		startMenu.clear();

	}
	int rs = startMenu.getRS(); //resolution settings


	//Stuff needed to lock fps
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	//

	Window window("WeebFight", 640 * rs, 360 * rs);
	Rect sky(640*rs, 360*rs, 0, 0, "Resources/sky.jpeg");


	Rect floor(900 * rs, 100 * rs, 0, 260 * rs, 75, 45, 10, 255);
	Object grass(1200 * rs, 25 * rs, 0, 245 * rs, 20, 150, 20, 255);

	Text text(Window::renderer, "Resources/arial.ttf", 30, "fockin weebs", { 30, 10, 10, 255 });

	Player player1;
	player1.setBody(15*rs, 15*rs, 315*rs, 220*rs, 255, 200, 10, 1);

	Object wall(6*rs, 50*rs, 500*rs, 100*rs, 180, 30, 30, 200);
	Object ground(100 * rs, 5 * rs, 10 * rs, 150 * rs, 180, 30, 30, 1);
	Object box(75 * rs, 75 * rs, 400 * rs, 175 * rs, 180, 100, 50, 1);

	std::list<Rect> rectangles;
	rectangles.push_back(floor);

	std::list<Object> objects;
	objects.push_back(wall);
	objects.push_back(ground);
	objects.push_back(grass);
	objects.push_back(box);

	const bool CAMERA_FOLLOWS_PLAYER = true;

	while (!window.isClosed())
	{
		frameStart = SDL_GetTicks();

		pollEvents(window, player1, rs);

		sky.draw();

		for (std::list<Rect>::iterator it = rectangles.begin(); it != rectangles.end(); it++)
		{
			it->draw();
		}
		for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++)
		{
			it->draw();
		}

		text.display(20, 20, Window::renderer);


		if (!CAMERA_FOLLOWS_PLAYER)
		{
			player1.updatePosition();
			Tools::playerCollider(player1, objects);
		}

		if (CAMERA_FOLLOWS_PLAYER)
		{
			Tools::CameraFollowsPlayer(player1, rectangles, objects);
			Tools::cameraColiider(player1, rectangles, objects);
		}
		player1.draw();
		
		window.clear();

		//if all the events ended before the end of the frame we delay until the end of the frame
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}