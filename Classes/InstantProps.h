#ifndef _INSTANTPROPS_H_
#define _INSTANTPROPS_H_

#include "cocos2d.h"

class InstantProps :public cocos2d::Node
{
public:
	cocos2d::Point position;
	int id;
	cocos2d::Sprite* sprite;
	float existTime;
	bool isDelete;
	static InstantProps* createPropsSprite(cocos2d::Point position, int id);
	void initProps(cocos2d::Point position, int id);
	virtual bool init();

	CREATE_FUNC(InstantProps);
};
#endif