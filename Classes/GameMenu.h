#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include "cocos2d.h"

class GameMenu : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	void level_BtnCallBack(cocos2d::Ref* pSender);
	void map_BtnCallBack(cocos2d::Ref* pSender);
	void chara_BtnCallBack(cocos2d::Ref* pSender);
	void settings_BtnCallBack(cocos2d::Ref* pSender);

	CREATE_FUNC(GameMenu);
};
#endif