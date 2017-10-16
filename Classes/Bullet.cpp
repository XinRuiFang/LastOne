#include "Bullet.h"
#include "Util.h"

USING_NS_CC;
#define PI 3.1415926

Bullet* Bullet::createBulletSprite(Point position, float dx, float dy, float angle, int direction, float damage)
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->init())
	{
		bullet->autorelease();
		bullet->initBullet(position, dx, dy, angle, direction, damage);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void Bullet::initBullet(cocos2d::Point position, float dx, float dy, float angle, int direction, float damage)
{	
	this->speed = 6 * Util::getSw();
	this->movedLength = 0;
	this->distance = 160 * Util::getSw();
	this->dx = dx;
	this->dy = dy;
	this->angle = angle;
	this->direction = direction;
	this->damage = damage;
	this->isDelete = false;
	switch (direction)
	{
	case 0:
		this->position = Vec2(position.x - 3 * Util::getSw(), position.y - 6 * Util::getSh());
		break;
	case 1:
		this->position = Vec2(position.x - 16 * Util::getSw(), position.y - 3 * Util::getSh());
		break;
	case 2:
		this->position = Vec2(position.x + 15 * Util::getSw(), position.y - 2 * Util::getSh());
		break;
	case 3:
		this->position = Vec2(position.x - 1 * Util::getSw(), position.y + 12 * Util::getSh());
		break;
	default:
		break;
	}
	
	sprite = Sprite::create("bullet.png");
	if (dx == 0 && dy == 0 && angle == 0)
	{
		switch (direction)
		{
		case 0:
			sprite->setRotation(270);
			break;
		case 1:
			sprite->setRotation(0);
			break;
		case 2:
			sprite->setRotation(180);
			break;
		case 3:
			sprite->setRotation(90);
			break;
		default:
			break;
		}
	}
	else if (dx > 0 && dy > 0)
	{
		sprite->setRotation(180 - angle);
	}
	else if (dx < 0 && dy > 0)
	{
		sprite->setRotation(angle);
	}
	else if (dx > 0 && dy < 0)
	{
		sprite->setRotation(180 + angle);
	}
	else if (dx < 0 && dy < 0)
	{
		sprite->setRotation(-angle);
	}
	else if (dx == 0 && dy != 0)
	{
		sprite->setRotation(dy > 0 ? 90 : 270);
	}
	else if (dx != 0 && dy == 0)
	{
		sprite->setRotation(dx > 0 ? 180 : 0);
	}
	sprite->setPosition(this->position);
	addChild(sprite, 2);
	scheduleUpdate();
}

bool Bullet::bulletMove()
{
	if (movedLength < distance)
	{
		if (angle == 0 && dx == 0 && dy == 0)
		{
			switch (direction)
			{
			case 0:
				position = Vec2(position.x, position.y - speed);
				break;
			case 1:
				position = Vec2(position.x - speed, position.y);
				break;
			case 2:
				position = Vec2(position.x + speed, position.y);
				break;
			case 3:
				position = Vec2(position.x, position.y + speed);
				break;
			default:
				break;
			}
		}
		else
		{
			float a = angle * PI / 180;
			position = Vec2(dx == 0 ? position.x : (dx > 0 ? (position.x + cos(a) * speed) : (position.x - cos(a) * speed)), dy == 0 ? position.y : (dy>0 ? (position.y + sin(a) * speed) : (position.y - sin(a) * speed)));
		}		
		sprite->setPosition(position);
		movedLength += speed;
		return false;
	}
	else
	{
		return true;
	}
}

void Bullet::update(float dt)
{
	if (bulletMove())
	{
		isDelete = true;
		removeFromParent();
	}
}

