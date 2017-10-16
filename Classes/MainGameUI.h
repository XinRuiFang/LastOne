#ifndef _MAINGAME_UI_H_
#define _MAINGAME_UI_H_

#include "cocos2d.h"

class MainGameUI : public cocos2d::Layer
{
public:
	bool startRefresh;
	float startTime;
	cocos2d::Label* poslabel;
	cocos2d::Label* testlabel;
	cocos2d::Label* startTimeLabel;
	cocos2d::Label* playerHpLabel;
	cocos2d::Label* defenceLabel;
	cocos2d::Label* stageLabel;
	cocos2d::Label* scoreLabel;
	cocos2d::Sprite* defenceBarBg;
	cocos2d::ProgressTimer* defenceBar;
	cocos2d::Sprite* playerHpBarBg;
	cocos2d::ProgressTimer* playerHpBar;
	cocos2d::Sprite* defenceIcon;
	static MainGameUI* createMainGameUI();
	void MainGameUIInit();
	CREATE_FUNC(MainGameUI);
};
#endif