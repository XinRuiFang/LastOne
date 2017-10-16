#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

class Bullet : public cocos2d::Node
{
public:
	cocos2d::Sprite* sprite;
	cocos2d::Point position;
	float speed;
	float distance;
	float movedLength;
	float dx;
	float dy;
	float angle;
	float damage;
	int direction;
	bool isDelete;

	virtual bool init();
	virtual void update(float dt);
	void initBullet(cocos2d::Point position, float dx, float dy, float angle, int direction, float damage);
	static Bullet* createBulletSprite(cocos2d::Point position,float dx, float dy, float angle,int direction,float damage);

	bool bulletMove();
	CREATE_FUNC(Bullet);
};
#endif