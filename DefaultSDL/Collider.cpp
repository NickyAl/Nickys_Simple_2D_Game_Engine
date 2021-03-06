#include "Collider.h"

bool Collider::HorizontalCollision(Object& actor, Object& wall)
{
	if (actor.getY() + actor.getH() <= wall.getY() || wall.getY() + wall.getH() <= actor.getY())
		return false; //no horizontal colisions

	return true;
}

bool Collider::VerticalCollision(Object& actor, Object& wall)
{
	if (actor.getX() + actor.getW() <= wall.getX() || wall.getX() + wall.getW() <= actor.getX())
		return false; //no vertical colisions

	return true;
}

void Collider::playerCollider(Player& player, std::list<Object*>& objects)
{
	Object actor = player.getCollisionBox();
	Object* obj = nullptr;
	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		obj = *it;

		if (obj->getCollision() == false)
			continue;

		if (HorizontalCollision(actor, *obj) && VerticalCollision(actor, *obj))
		{
			Object prevPos(actor.getW(), actor.getH(), actor.getX() - (player.getAcclrtn().right - player.getAcclrtn().left), actor.getY() - (player.getAcclrtn().down - player.getAcclrtn().up), 0, 0, 0, 0, true);

			if (HorizontalCollision(prevPos, **it))
			{
				if (MathTools::inRange(actor.getX(), obj->getX(), obj->getX() + obj->getW()))
				{
					player.setLocX(obj->getX() + obj->getW()); //stick to the right side
				}
				else if (MathTools::inRange(actor.getX() + actor.getW(), obj->getX(), obj->getX() + obj->getW()))
				{
					player.setLocX(obj->getX() - actor.getW()); //stick to the left side
				}
			}
			else
			{
				if (MathTools::inRange(actor.getY(), obj->getY(), obj->getY() + obj->getH()))
				{
					player.setLocY(obj->getY() + obj->getH()); //stick to the bottom
				}
				else
				{
					player.setLocY(obj->getY() - actor.getH()); //stick to the top
					player.canJump = true;
				}
			}
		}
	}
}

void Collider::cameraCollider(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects)
{
	Object actor = player.getCollisionBox();
	Object* obj = nullptr;
	Rect* rect = nullptr;
	float movement = 0;

	for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		obj = *it;

		if (obj->getCollision() == false)
			continue;

		if (HorizontalCollision(actor, *obj) && VerticalCollision(actor, *obj))
		{
			Object prevPos(actor.getW(), actor.getH(), actor.getX() - (player.getAcclrtn().right - player.getAcclrtn().left), actor.getY() - (player.getAcclrtn().down - player.getAcclrtn().up), 0, 0, 0, 0, true);

			if (HorizontalCollision(prevPos, *obj))
			{
				if (MathTools::inRange(actor.getX(), obj->getX(), obj->getX() + obj->getW()))
				{
					movement = (player.getLocX() - obj->getW()) - obj->getX();
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
				else if (MathTools::inRange(actor.getX() + actor.getW(), obj->getX(), obj->getX() + obj->getW()))
				{

					movement = player.getLocX() - (obj->getX() - player.getW());
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
				if (MathTools::inRange(actor.getY(), obj->getY(), obj->getY() + obj->getH()))
				{
					movement = (player.getLocY() - obj->getH()) - obj->getY();
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
				else if (MathTools::inRange(actor.getY() + actor.getH(), obj->getY(), obj->getY() + obj->getH()))
				{

					movement = player.getLocY() - (obj->getY() - player.getH());
					for (std::list<Object*>::iterator j = objects.begin(); j != objects.end(); j++)
					{
						obj = *j;
						obj->moveY(movement);  //stick to the bottom of the player
						player.canJump = true;
					}
					for (std::list<Rect*>::iterator j = rects.begin(); j != rects.end(); j++)
					{
						rect = *j;
						rect->moveY(movement);  //stick to the bottom of the player
						player.canJump = true;
					}
				}
			}
		}
	}
}



void Collider::CameraFollowsPlayer(Player& player, std::list<Rect*>& rects, std::list<Object*>& objects)
{
	float xMovement = -1 * (player.getAcclrtn().right - player.getAcclrtn().left);
	float yMovement = -1 * (player.getAcclrtn().down - player.getAcclrtn().up);

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