#include "Tools.h"
//#include <iostream>

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

void Tools::playerCollider(Player& player, std::list<Object>& objects)
{
	Object actor = player.getCollisionBox();

	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		if (HorizontalColision(actor, *it) && VerticalColision(actor, *it))
		{
			Object prevPos(actor.getW(), actor.getH(), actor.xCoord - (player.getAcclrtn().right - player.getAcclrtn().left), actor.yCoord - (player.getAcclrtn().down - player.getAcclrtn().up), 0, 0, 0, 0);

			if (HorizontalColision(prevPos, *it))
			{
				if (inRange(actor.xCoord, it->xCoord, it->xCoord + it->getW()))
				{
					player.setLocX(it->xCoord + it->getW()); //stick to the right side
				}
				else if (inRange(actor.xCoord + actor.getW(), it->xCoord, it->xCoord + it->getW()))
				{
					player.setLocX(it->xCoord - actor.getW()); //stick to the left side
				}
			}
			else
			{
				if (inRange(actor.yCoord, it->yCoord, it->yCoord + it->getH()))
				{
					player.setLocY(it->yCoord + it->getH()); //stick to the bottom	
				}
				else
				{
					player.setLocY(it->yCoord - actor.getH()); //stick to the top
				}
			}
		}
	}
}

void Tools::cameraColiider(Player& player, std::list<Rect>& rects,std::list<Object>& objects)
{
	Object actor = player.getCollisionBox();
	int movement = 0;

	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		if (HorizontalColision(actor, *it) && VerticalColision(actor, *it))
		{
			Object prevPos(actor.getW(), actor.getH(), actor.xCoord - (player.getAcclrtn().right - player.getAcclrtn().left), actor.yCoord - (player.getAcclrtn().down - player.getAcclrtn().up), 0, 0, 0, 0);

			if (HorizontalColision(prevPos, *it))
			{
				if (inRange(actor.xCoord, it->xCoord, it->xCoord + it->getW()))
				{
					movement = (player.getLocX() - it->getW()) - it->xCoord;
					for (std::list<Object>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						j->moveX(movement);  //stick to the right of the player
					}
					for (std::list<Rect>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						j->moveX(movement);  //stick to the right of the player
					}
					
				}
				else if (inRange(actor.xCoord + actor.getW(), it->xCoord, it->xCoord + it->getW()))
				{
					
					movement = player.getLocX() - (it->xCoord - player.getW());
					for (std::list<Object>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						j->moveX(movement);  //stick to the left of the player
					}
					for (std::list<Rect>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						j->moveX(movement);  //stick to the left of the player
					}
				}
			}
			else
			{
				if (inRange(actor.yCoord, it->yCoord, it->yCoord + it->getH()))
				{
					movement = (player.getLocY() - it->getH()) - it->yCoord;
					for (std::list<Object>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						j->moveY(movement);  //stick to the top of the player
					}
					for (std::list<Rect>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						j->moveY(movement);  //stick to the top of the player
					}

				}
				else if (inRange(actor.yCoord + actor.getH(), it->yCoord, it->yCoord + it->getH()))
				{

					movement = player.getLocY() - (it->yCoord - player.getH());
					for (std::list<Object>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						j->moveY(movement);  //stick to the bottom of the player
					}
					for (std::list<Rect>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						j->moveY(movement);  //stick to the bottom of the player
					}
				}
			}
		}
	}
}



void Tools::CameraFollowsPlayer(Player& player, std::list<Rect>& rects, std::list<Object>& objects)
{
	int xMovement = -1 * (player.getAcclrtn().right - player.getAcclrtn().left);
	int yMovement = -1 * (player.getAcclrtn().down - player.getAcclrtn().up);

	for (std::list<Rect>::iterator it = rects.begin(); it != rects.end(); it++)
	{
		it->moveX(xMovement);
		it->moveY(yMovement);
	}

	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		it->moveX(xMovement);
		it->moveY(yMovement);
	}
}
