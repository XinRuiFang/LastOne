#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#define NUM 4
#define STATUSMAX 10

enum ADDI
{
	SPEED,
	AMMO,
	SHOOT,
};
struct Status
{
	bool _exec = false;
	ADDI addition;
	float percent;
	float time;
	float execTime;
};
class Player : public cocos2d::Node
{
public:
	int direction;
	int action;
	float speed;
	bool isRun;
	float coldTime;
	float coldTimeCount;
	float hpUpper;
	float hp;
	float playerDefence;
	float defence;
	float protectTime;
	float defencePercent;
	float damagePercent;
	bool protect;
	float pTime;
	bool playerVisable;
	bool gunVisable;

	struct Status statusArr[STATUSMAX];

	cocos2d::Point position;
	cocos2d::Sprite* bodysprite;
	cocos2d::Sprite* legsprite;
	cocos2d::Sprite* gunsprite;
	static Player* createPlayerSprite(cocos2d::Point position, int direction);
	void initPlayer(int direction, cocos2d::Point position);
	virtual bool init();
	virtual void update(float dt);

	void playerActs();
	void playerActs(int i);
	void playerResume();
	bool playerCanShoot();
	void takeDamage(float damage);
	float getSpeed();
	float getDamagePercent();
	int getAmmo();

	cocos2d::Animate* createGunAnimate(int direction, int action);
	cocos2d::Animate* createBodyAnimate(int direction, int action);
	cocos2d::Animate* createLegAnimate(int direction, int action);
	CREATE_FUNC(Player);
};
#endif