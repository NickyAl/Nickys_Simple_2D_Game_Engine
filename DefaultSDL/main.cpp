#include <iostream>
#include "Window.h"
#include "Rect.h"
#include "Text.h"
#include "Object.h"
#include "Player.h"
#include "Collider.h"
//#include <string>
//#include <list>
#include <chrono>
#include "Texture.h"
#include "Animation.h"

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
	}
}

int main(int argc, char** argv)
{
	//START MENU
	Window startMenu("Settings", 200, 300);
	Texture settingMenu("Resources/testMenu.jpg");
	Rect menu(200.f, 300.f, 0.f, 0.f, settingMenu.texture);

	while (!startMenu.isClosed())
	{

		pollEventsForMenu(startMenu, menu);

		startMenu.setOpndSttng(true);

		menu.draw();

		startMenu.clear();

	}
	float RS = startMenu.getRS(); //resolution settings


	//GAME WINDOW///////////////////////////////////////////////////////////////////////////////
	Window window("Nicky's simple 2D game engine", (int)(640 * RS), (int)(360 * RS));

	//GAME TEXTURES
	Texture nightSky("Resources/sky.jpeg"),
			metalBox("Resources/metal box.png"),
			moonFloor("Resources/moonfloor.jpg"),
			metalPlatform("Resources/platform.jpg"),
			defaultPlayer("Resources/maniken/maniken0.png"),
			goldCoin("Resources/coin/Gold_0.png");


	//GAME PROPS////////////////////////////////////////////////////////////////////////////////

	//simple rectangles no animation no collision
	//------------------------------------------------------------------------------------------
	Rect sky(640.f * RS, 360.f * RS, 0.f, 0.f, nightSky.texture);
	Rect underground(1200.f * RS, 600.f * RS, 0.f, 280.f * RS, 60, 60, 60, 255);

	std::list<Rect*> rects;
	rects.push_back(&underground);


	//complex rectangles possible animations and collisions
	//------------------------------------------------------------------------------------------
	Object floor1(300.f * RS, 60.f * RS, 0.f * RS, 265.f * RS, moonFloor.texture, true);
	Object floor2(300.f * RS, 60.f * RS, 300.f * RS, 265.f * RS, moonFloor.texture, true);
	Object floor3(300.f * RS, 60.f * RS, 600.f * RS, 265.f * RS, moonFloor.texture, true);
	Object floor4(300.f * RS, 60.f * RS, 900.f * RS, 265.f * RS, moonFloor.texture, true);
	Object box(75.f * RS, 75.f * RS, 400.f * RS, 200.f * RS, metalBox.texture, true);
	Object coin(20.f * RS, 20.f * RS, 200.f * RS, 200.f * RS, goldCoin.texture, false);
	Object platform(100.f * RS, 10.f * RS, 700.f * RS, 150.f * RS, metalPlatform.texture, true);
	Object platform1(100.f * RS, 10.f * RS, 500.f * RS, 100.f * RS, metalPlatform.texture, true);
	Object platform2(70.f * RS, 10.f * RS, 100.f * RS, 180.f * RS, metalPlatform.texture, true);
	Object platform3(120.f * RS, 10.f * RS, 510.f * RS, 230.f * RS, metalPlatform.texture, true);

	//coin.loadAnim("Resources/coin/Gold_", 10);

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
	Text text(Window::renderer, "Resources/arial.ttf", (int)(10 * RS), "NS2D", { 30, 10, 10, 255 });


	//Player actor
	//------------------------------------------------------------------------------------------
	Player player1(RS);
	player1.setCollisionBox(40.f *RS, 65.f *RS, 280.f *RS, 180.f *RS, 255, 200, 10, 1);
	player1.setSprite(55.f * RS, 75.f * RS, 272.f * RS, 180.f * RS, defaultPlayer.texture);

	//Player Animations
	Animation runningR("Resources/Yellow bot/running right/", 22),
			  runningL("Resources/Yellow bot/running left/", 22),
			  idleR("Resources/Yellow bot/idle right/", 8),
			  idleL("Resources/Yellow bot/idle left/", 8),
		  	  fallR("Resources/Yellow bot/fall right/", 4),
			  fallL("Resources/Yellow bot/fall left/", 4),
			  jumpR("Resources/Yellow bot/jump right/", 8),
			  jumpL("Resources/Yellow bot/jump left/", 8);

	player1.addAnimation(runningR);
	player1.addAnimation(runningL);
	player1.addAnimation(idleR);
	player1.addAnimation(idleL);
	player1.addAnimation(fallR);
	player1.addAnimation(fallL);
	player1.addAnimation(jumpR);
	player1.addAnimation(jumpL);



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
			Collider::CameraFollowsPlayer(player1, rects, objects);
			Collider::cameraCollider(player1, rects, objects);
		}
		else
		{
			player1.updatePosition();
			Collider::playerCollider(player1, objects);
		}

		player1.updateSprite(TIME_PER_FRAME);

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