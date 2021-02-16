#include "Tools.h"
//#include <iostream>

std::string Tools::intToString(int num)
{
	if (num == 0)
		return "0";

	std::string result = "";
	std::stack<char> buffer;

	while (num)
	{
		buffer.push('0' + (num % 10));
		num /= 10;
	}

	while (!buffer.empty())
	{
		result += buffer.top();
		buffer.pop();
	}
	
	return result;
}

bool Tools::HorizontalColision(Object& actor, Object& wall)
{
	if (actor.yCoord + actor.getH() <= wall.yCoord || wall.yCoord + wall.getH() <= actor.yCoord)
		return false; //no horizontal colisions

	return true;
}

bool Tools::VerticalColision(Object& actor, Object& wall)
{
	if (actor.xCoord + actor.getW() <= wall.xCoord || wall.xCoord + wall.getW() <= actor.xCoord)
		return false; //no vertical colisions

	return true;
}

void Tools::playerCollider(Player& player, std::list<Object*>& objects)
{
	Object actor = player.getCollisionBox();
	Object* obj = nullptr;
	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		 obj = *it;

		 if (obj->getCollision() == false)
			 continue;

		if (HorizontalColision(actor, *obj) && VerticalColision(actor, *obj))
		{
			Object prevPos(actor.getW(), actor.getH(), actor.xCoord - (player.getAcclrtn().right - player.getAcclrtn().left), actor.yCoord - (player.getAcclrtn().down - player.getAcclrtn().up), 0, 0, 0, 0, true);

			if (HorizontalColision(prevPos, **it))
			{
				if (inRange(actor.xCoord, obj->xCoord, obj->xCoord + obj->getW()))
				{
					player.setLocX(obj->xCoord + obj->getW()); //stick to the right side
				}
				else if (inRange(actor.xCoord + actor.getW(), obj->xCoord, obj->xCoord + obj->getW()))
				{
					player.setLocX(obj->xCoord - actor.getW()); //stick to the left side
				}
			}
			else
			{
				if (inRange(actor.yCoord, obj->yCoord, obj->yCoord + obj->getH()))
				{
					player.setLocY(obj->yCoord + obj->getH()); //stick to the bottom	
				}
				else
				{
					player.setLocY(obj->yCoord - actor.getH()); //stick to the top
				}
			}
		}
	}
}

void Tools::cameraColiider(Player& player, std::list<Rect*>& rects,std::list<Object*>& objects)
{
	Object actor = player.getCollisionBox();
	Object* obj = nullptr;
	Rect* rect = nullptr;
	int movement = 0;

	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		obj = *it;

		if (obj->getCollision() == false)
			continue;

		if (HorizontalColision(actor, *obj) && VerticalColision(actor, *obj))
		{
			Object prevPos(actor.getW(), actor.getH(), actor.xCoord - (player.getAcclrtn().right - player.getAcclrtn().left), actor.yCoord - (player.getAcclrtn().down - player.getAcclrtn().up), 0, 0, 0, 0, true);

			if (HorizontalColision(prevPos, *obj))
			{
				if (inRange(actor.xCoord, obj->xCoord, obj->xCoord + obj->getW()))
				{
					movement = (player.getLocX() - obj->getW()) - obj->xCoord;
					for (std::list<Object*>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						obj = *j;
						obj->moveX(movement);  //stick to the right of the player
					}
					for (std::list<Rect*>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						rect = *j;
						rect->moveX(movement);  //stick to the right of the player
					}
					
				}
				else if (inRange(actor.xCoord + actor.getW(), obj->xCoord, obj->xCoord + obj->getW()))
				{
					
					movement = player.getLocX() - (obj->xCoord - player.getW());
					for (std::list<Object*>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						obj = *j;
						obj->moveX(movement);  //stick to the left of the player
					}
					for (std::list<Rect*>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						rect = *j;
						rect->moveX(movement);  //stick to the left of the player
					}
				}
			}
			else
			{
				if (inRange(actor.yCoord, obj->yCoord, obj->yCoord + obj->getH()))
				{
					movement = (player.getLocY() - obj->getH()) - obj->yCoord;
					for (std::list<Object*>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						obj = *j;
						obj->moveY(movement);  //stick to the top of the player
					}
					for (std::list<Rect*>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						rect = *j;
						rect->moveY(movement);  //stick to the top of the player
					}

				}
				else if (inRange(actor.yCoord + actor.getH(), obj->yCoord, obj->yCoord + obj->getH()))
				{

					movement = player.getLocY() - (obj->yCoord - player.getH());
					for (std::list<Object*>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						obj = *j;
						obj->moveY(movement);  //stick to the bottom of the player
					}
					for (std::list<Rect*>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						rect = *j;
						rect->moveY(movement);  //stick to the bottom of the player
					}
				}
			}
		}
	}
}



void Tools::CameraFollowsPlayer(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects)
{
	int xMovement = -1 * (player.getAcclrtn().right - player.getAcclrtn().left);
	int yMovement = -1 * (player.getAcclrtn().down - player.getAcclrtn().up);

	Object* obj = nullptr;
	Rect* rect = nullptr;

	for (std::list<Rect*>::iterator it = rects.begin(); it != rects.end(); it++)
	{
		rect = *it;
		rect->moveX(xMovement);
		rect->moveY(yMovement);
	}

	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		obj = *it;
		obj->moveX(xMovement);
		obj->moveY(yMovement);
	}
}
