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
	int rs = startMenu.getRS(); //resolution settings


	//Stuff needed to lock fps
	//------------------------------------------------------------------------------------------

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;


	//GAME WINDOW///////////////////////////////////////////////////////////////////////////////
	Window window("Nicky's simple 2D game engine", 640 * rs, 360 * rs);

	//GAME PROPS////////////////////////////////////////////////////////////////////////////////

	//simple rectangles no animation no collision
	//------------------------------------------------------------------------------------------
	Rect sky(640 * rs, 360 * rs, 0, 0, "Resources/sky.jpeg");
	Rect floor(900 * rs, 100 * rs, 0, 260 * rs, 75, 45, 10, 255);

	std::list<Rect*> rects;
	rects.push_back(&sky);
	rects.push_back(&floor);


	//complex rectangles possible animations and collisions
	//------------------------------------------------------------------------------------------
	Object grass(1200 * rs, 25 * rs, 0, 245 * rs, 20, 150, 20, 255, true);
	Object wall(6 * rs, 50 * rs, 500 * rs, 100 * rs, 180, 30, 30, 200, true);
	Object ground(100 * rs, 5 * rs, 10 * rs, 150 * rs, 180, 30, 30, 1, true);
	Object box(75 * rs, 75 * rs, 400 * rs, 175 * rs, 180, 100, 50, 1, true);
	Object coin(20 * rs, 20 * rs, 200 * rs, 200 * rs, "Resources/coin/Gold_0.png", false);
	
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
	Player player1(rs);
	player1.setCollisionBox(25*rs, 60*rs, 270*rs, 150*rs, 255, 200, 10, 1);
	player1.setSprite(42 * rs, 72 * rs, 270 * rs, 150 * rs, "Resources/maniken/maniken0.png");
	player1.getSprite().loadAnim("Resources/maniken/maniken", 20);


	//Const and others used in each frames logic
	//------------------------------------------------------------------------------------------
	const bool CAMERA_FOLLOWS_PLAYER = false;

	int FRAME_TIMER = 0;
	int frame_changer[2] = { 0 }; //2 for 2 animated objects

	Object* objIt = nullptr;
	Rect* rectIt = nullptr;
	

	//The game loop/////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------------------------
	while (!window.isClosed())
	{
		FRAME_TIMER++;

		frameStart = SDL_GetTicks();

		pollEvents(window, player1, rs);

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
	}

	return 0;
}