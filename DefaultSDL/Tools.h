#pragma once
#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include <list>
#include <string>
#include <stack>

class Tools
{

public:
	//MATH TOOLS
	static bool inRange(int a, int b, int c)
	{
		return a >= b && a <= c;
	}

	//COMMON TOOLS
	static std::string intToString(int num);

	//GAME ENGINE TOOLS
	static bool HorizontalColision(Object& actor, Object& wall); 
	static bool VerticalColision(Object& actor, Object& wall); 

	static void playerCollider(Player& player, std::list<Object*>& objects); 

	static void cameraColiider(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects); 

	static void CameraFollowsPlayer(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects); 

	
};

