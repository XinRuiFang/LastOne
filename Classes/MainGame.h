#ifndef _MAINGAME_H_
#define _MAINGAME_H_

#include "cocos2d.h"
#include "Player.h"
#include "HRocker.h"
#include "Bullet.h"
#include "MainGameUI.h"
#include "Decorats.h"
#include "Util.h"
#include "Monster.h"
#include "InstantProps.h"

class MainGame : public cocos2d::Layer
{
public:
	float sw;
	float sh;
	cocos2d::Vector<Bullet*> bullets;
	cocos2d::Vector<Decorats*> decorats;
	cocos2d::Vector<Monster*> monsters;
	cocos2d::Vector<InstantProps*> props;
	float monsterFreshTime;
	int monsterCount;
	float monsterFreshTimeConst;
	int monsterCountMax;
	int stage;
	int playerkillcounts;
	float score;
	bool gameover;

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	bool createMap(Size visibleSize, Vec2 origin);
	bool createDecorats();

	void levelDataInit();
	void playerDataInit(Size visibleSize, Vec2 origin);
	void objectEraseHandler();
	void playerActHandler();
	void playerMoveHandler();
	void playerShootHandler(float dt);
	void bulletCollide();
	void monsterRefreshHandler();
	void monsterCreateHandler();
	void monsterRefresh(float dt);
	void monsterHandler(float dt);
	void monsterDeadHandler(Monster* monster);

	void propsHandler();
	void propsDisplayerHandler(float dt);
	void getProps(int id);
	void UIHandler(float dt);
	
	CREATE_FUNC(MainGame);
};
#endif