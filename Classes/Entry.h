#ifndef _ENTRY_H_
#define _ENTRY_H_

#include "cocos2d.h";

class Entry : public cocos2d::Layer
{
public:
	float showTime;
	bool cs;
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	CREATE_FUNC(Entry);
};
#endif