#ifndef _DECORATS_H_
#define _DECORATS_H_

#include "cocos2d.h"
#define NUMD_1 2

class Decorats : public cocos2d::Node
{
public:
	const char* area;
	const char* type;
	cocos2d::Point position;
	cocos2d::Sprite* sprite;
	cocos2d::Sprite* shadow;
	float radius;
	static Decorats* createDecoratsSprite(cocos2d::Point position, const char* area, const char* type);
	void initDecorats(cocos2d::Point position, const char* area, const char* type);
	virtual bool init();
	cocos2d::Animate* createAnimate();
};
#endif