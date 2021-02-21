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

void pollEvents(Window& window, Player& player1, float time_per_frame)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		window.pollEvents(event);
		player1.pollEvents(event, time_per_frame);
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
	Rect underground(1200 * RS, 600 * RS, 0, 280 * RS, 60, 60, 60, 255);

	std::list<Rect*> rects;
	rects.push_back(&underground);


	//complex rectangles possible animations and collisions
	//------------------------------------------------------------------------------------------
	Object floor1(300 * RS, 60 * RS, 0 * RS, 265 * RS, "Resources/moonfloor.jpg", true);
	Object floor2(300 * RS, 60 * RS, 300 * RS, 265 * RS, "Resources/moonfloor.jpg", true);
	Object floor3(300 * RS, 60 * RS, 600 * RS, 265 * RS, "Resources/moonfloor.jpg", true);
	Object floor4(300 * RS, 60 * RS, 900 * RS, 265 * RS, "Resources/moonfloor.jpg", true);
	Object box(75 * RS, 75 * RS, 400 * RS, 200 * RS, "Resources/metal box.png", true);
	Object coin(20 * RS, 20 * RS, 200 * RS, 200 * RS, "Resources/coin/Gold_0.png", false);
	Object platform(100 * RS, 10 * RS, 700 * RS, 150 * RS, "Resources/platform.jpg", true);
	Object platform1(100 * RS, 10 * RS, 500 * RS, 100 * RS, "Resources/platform.jpg", true);
	Object platform2(70 * RS, 10 * RS, 100 * RS, 180 * RS, "Resources/platform.jpg", true);
	Object platform3(120 * RS, 10 * RS, 510 * RS, 230 * RS, "Resources/platform.jpg", true);

	coin.loadAnim("Resources/coin/Gold_", 10);

	std::list<Object*> objects;
	objects.push_back(&platform2);
	objects.push_back(&platform1);
	objects.push_back(&floor1);
	objects.push_back(&floor2);
	objects.push_back(&floor3);
	objects.push_back(&floor4);
	objects.push_back(&box);
	objects.push_back(&coin);
	objects.push_back(&platform);
	objects.push_back(&platform3);


	//text for UI
	//------------------------------------------------------------------------------------------
	Text text(Window::renderer, "Resources/arial.ttf", 30, "NS2D", { 30, 10, 10, 255 });


	//Player actor
	//------------------------------------------------------------------------------------------
	Player player1(RS);
	player1.setCollisionBox(40*RS, 70*RS, 280*RS, 180*RS, 255, 200, 10, 1);
	player1.setSprite(55 * RS, 75 * RS, 272 * RS, 180 * RS, "Resources/maniken/maniken0.png");
	//player1.getSprite().loadAnim("Resources/Yellow bot/running right/", 22);
	player1.loadAnim("Resources/Yellow bot/running left/", 22, player1.getRunLeft(), player1.getRunLeftFrames());
	player1.loadAnim("Resources/Yellow bot/running right/", 22, player1.getRunRight(), player1.getRunRightFrames());
	player1.loadAnim("Resources/Yellow bot/idle right/", 8, player1.getIdleRight(), player1.getIdleRightFrames());
	player1.loadAnim("Resources/Yellow bot/idle left/", 8, player1.getIdleLeft(), player1.getIdleLeftFrames());
	player1.loadAnim("Resources/Yellow bot/fall right/", 4, player1.getFallRight(), player1.getFallRightFrames());
	player1.loadAnim("Resources/Yellow bot/fall left/", 4, player1.getFallLeft(), player1.getFallLeftFrames());
	player1.loadAnim("Resources/Yellow bot/jump right/", 8, player1.getJumpRight(), player1.getJumpRightFrames());
	player1.loadAnim("Resources/Yellow bot/jump left/", 8, player1.getJumpLeft(), player1.getJumpLeftFrames());

	//Const and others used in each frames logic
	//------------------------------------------------------------------------------------------
	const bool CAMERA_FOLLOWS_PLAYER = true;

	Object* objIt = nullptr;
	Rect* rectIt = nullptr;

	float TIME_PER_FRAME = 0;

	//Stuff needed to lock fps
	const int FPS = 144;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	

	//The game loop/////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------------------------
	while (!window.isClosed())
	{
		auto frame_start = std::chrono::high_resolution_clock::now();

		frameStart = SDL_GetTicks();

		pollEvents(window, player1, TIME_PER_FRAME);
		player1.gravity(TIME_PER_FRAME);
		player1.canJump = false;


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

		player1.updateSprite(TIME_PER_FRAME);
		coin.updateSprite(TIME_PER_FRAME, 0.07);

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
	}

	return 0;
}