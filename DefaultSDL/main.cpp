#include <iostream>
#include "Window.h"
#include "Rect.h"
#include "Text.h"
#include "Object.h"
#include "Player.h"
#include "Tools.h"
#include <string>
#include <list>
#include <chrono>

void pollEvents(Window& window, Player& player1, int resolutionSetting, float time_per_frame)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		window.pollEvents(event);
		player1.pollEvents(event, resolutionSetting, time_per_frame);
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
	//START MENU
	Window startMenu("Settings", 200, 300);
	Rect menu(200, 300, 0, 0, "Resources/testMenu.jpg");

	while (!startMenu.isClosed())
	{

		pollEventsForMenu(startMenu, menu);

		startMenu.setOpndSttng(true);

		menu.draw();

		startMenu.clear();

	}
	int RS = startMenu.getRS(); //resolution settings


	//GAME WINDOW///////////////////////////////////////////////////////////////////////////////
	Window window("Nicky's simple 2D game engine", 640 * RS, 360 * RS);

	//GAME PROPS////////////////////////////////////////////////////////////////////////////////

	//simple rectangles no animation no collision
	//------------------------------------------------------------------------------------------
	Rect sky(640 * RS, 360 * RS, 0, 0, "Resources/sky.jpeg");
	Rect floor(900 * RS, 100 * RS, 0, 260 * RS, 75, 45, 10, 255);

	std::list<Rect*> rects;
	//rects.push_back(&sky);
	rects.push_back(&floor);


	//complex rectangles possible animations and collisions
	//------------------------------------------------------------------------------------------
	Object grass(1200 * RS, 25 * RS, 0, 245 * RS, 20, 150, 20, 255, true);
	Object wall(6 * RS, 50 * RS, 500 * RS, 100 * RS, 180, 30, 30, 200, true);
	Object ground(100 * RS, 5 * RS, 10 * RS, 150 * RS, 180, 30, 30, 1, true);
	Object box(75 * RS, 75 * RS, 400 * RS, 175 * RS, 180, 100, 50, 1, true);
	Object coin(20 * RS, 20 * RS, 200 * RS, 200 * RS, "Resources/coin/Gold_0.png", false);
	
	coin.loadAnim("Resources/coin/Gold_", 10);

	std::list<Object*> objects;
	objects.push_back(&wall);
	objects.push_back(&ground);
	objects.push_back(&grass);
	objects.push_back(&box);
	objects.push_back(&coin);


	//text for UI
	//------------------------------------------------------------------------------------------
	Text text(Window::renderer, "Resources/arial.ttf", 30, "NS2D", { 30, 10, 10, 255 });


	//Player actor
	//------------------------------------------------------------------------------------------
	Player player1(RS);
	player1.setCollisionBox(25*RS, 60*RS, 280*RS, 180*RS, 255, 200, 10, 1);
	player1.setSprite(42 * RS, 72 * RS, 272 * RS, 180 * RS, "Resources/maniken/maniken0.png");
	player1.getSprite().loadAnim("Resources/maniken/maniken", 20);


	//Const and others used in each frames logic
	//------------------------------------------------------------------------------------------
	const bool CAMERA_FOLLOWS_PLAYER = true;

	int FRAME_TIMER = 0;
	int frame_changer[2] = { 0 }; //2 for 2 animated objects

	Object* objIt = nullptr;
	Rect* rectIt = nullptr;

	float TIME_PER_FRAME = 0.016;

	//Stuff needed to lock fps
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	

	//The game loop/////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------------------------
	while (!window.isClosed())
	{
		auto frame_start = std::chrono::high_resolution_clock::now();

		FRAME_TIMER++;

		frameStart = SDL_GetTicks();

		pollEvents(window, player1, RS, TIME_PER_FRAME);

		if (CAMERA_FOLLOWS_PLAYER)
		{
			Tools::CameraFollowsPlayer(player1, rects, objects);
			Tools::cameraColiider(player1, rects, objects);
		}
		else
		{
			player1.updatePosition();
			Tools::playerCollider(player1, objects);
		}

		if (FRAME_TIMER % 5 == 0)
		{
			coin.updateSprite(frame_changer[0]);
			frame_changer[0]++;
		}
		if (FRAME_TIMER % 7 == 0)
		{
			player1.getSprite().updateSprite(frame_changer[1]);
			frame_changer[1]++;	
		}
		
		sky.draw(); //will add fixed to the screen items list if there are more such as this one
		for (std::list<Rect*>::iterator it = rects.begin(); it != rects.end(); it++)
		{
			rectIt = *it;
			rectIt->draw();
		}
		for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); it++)
		{
			objIt = *it;
			objIt->draw();
		}

		player1.draw();

		text.display(20, 20, Window::renderer);
		
		window.clear();

		//if all the events ended before the end of the frame we delay until the end of the frame
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}


		auto frame_end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> duration = frame_end - frame_start;
		TIME_PER_FRAME = duration.count();
		//std::cout << duration.count();
	}

	return 0;
}