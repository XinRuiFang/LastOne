#ifndef _TITLE_H_
#define _TITLE_H_

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
public:
	float sx;
	float sy;
	bool show;
	float opacity;
	static cocos2d::Scene* createScene();
	void mainBtnCallBack(cocos2d::Ref* pSender);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual bool init();
	virtual void update(float dt);
	static cocos2d::Layer* uiLayer();

	CREATE_FUNC(Title);
};
#endif