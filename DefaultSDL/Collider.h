#pragma once
#include "Object.h"
#include "Player.h"
#include "Rect.h"
#include <list>
#include <string>
#include <stack>
#include "MathTools.h"

class Collider
{
public:
	static bool HorizontalCollision(Object& actor, Object& wall);
	static bool VerticalCollision(Object& actor, Object& wall);

	static void playerCollider(Player& player, std::list<Object*>& objects);

	static void cameraCollider(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects);

	static void CameraFollowsPlayer(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects);
};

