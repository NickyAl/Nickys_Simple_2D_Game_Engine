#pragma once
#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include <list>

class Tools
{

public:
	//MATH TOOLS
	static bool inRange(int a, int b, int c)
	{
		return a >= b && a <= c;
	}

	//GAME ENGINE TOOLS
	static bool HorizontalColision(Object& actor, Object& wall); //Tools.cpp line 4
	static bool VerticalColision(Object& actor, Object& wall); //Tools.cpp line 12

	static void playerCollider(Player& player, std::list<Object>& objects); //Tools.cpp line 20
	static void cameraColiider(Player& player, std::list<Rect>& rects, std::list<Object>& objects); //Tools.cpp line 56

	static void CameraFollowsPlayer(Player& player, std::list<Rect>& rects, std::list<Object>& objects); //Tools.cpp line
};

