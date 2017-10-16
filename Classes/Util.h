#ifndef _UTIL_H_
#define _UTIL_H_
#include "cocos2d.h"

struct monsterData
{
	int id;
	std::string name;
	float hpUpper;
	float speed;
	float damage;
	float damageAvg;
	float score;
	float dropPercent;
};

class Util
{
public:
	static void setSw(float s);
	static float getSw();
	static void setSh(float s);
	static float getSh();
	static cocos2d::Size getScreenSize();
	static void setScreenSize(cocos2d::Size s);
	static int getRandom(int x, int y);
	static bool initMonsters();
	static std::vector<monsterData> getMonsterData();
	static int getRandomProps();
};

#endif