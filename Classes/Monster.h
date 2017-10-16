#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "cocos2d.h"
#define NUM_M 4

class Monster : public cocos2d::Node
{
public:
	int direction;
	int action;

	std::string name;
	float hpUpper;
	float hp;
	float lastHp;
	float speed;
	float radius;
	float damage;
	float damageAvg;
	float dropPercent;
	float hpBarVisTime;
	float score;

	cocos2d::Point position;
	cocos2d::Sprite* sprite;
	cocos2d::ProgressTimer* monsterHpBar;
	cocos2d::Sprite* monsterHpBarBg;
	static Monster* createMonsterSprite(cocos2d::Point position, int direction, int id, int stage);
	void initMonster(int direction, cocos2d::Point position, int id, int stage);
	virtual bool init();
	void actionHandler(cocos2d::Vec2 target,cocos2d::Point playerPos);
	void monsterActs();

	cocos2d::Animate* createAnimate(int direction, int action);
	CREATE_FUNC(Monster);
};
#endif