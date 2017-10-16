#include "MainGame.h"
#include "Util.h"
#include "Constants.h"
#define HPVISTIME 3
#define PLAYER_TAG 101
#define ROCKER_TAG 102
#define MUI_TAG 103

USING_NS_CC;

//传入参数，关卡号，玩家数据
Scene* MainGame::createScene()
{
	auto scene = Scene::create();

	auto layer = MainGame::create();

	scene->addChild(layer);

	return scene;
}

//createMap-createDecorats-player-monsterRefresh
//怪物掉落
//关卡结算-gameover界面
//虚拟按键
bool MainGame::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	if (!Layer::init() || !createMap(visibleSize, origin))
	{
		return false;
	}

	playerDataInit(visibleSize, origin);
	
	sw = Util::getSw();
	sh = Util::getSh();
	monsterFreshTime = 0;
	monsterCount = 0;
	
	auto* rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", "shooter.png","shooterBG.png", Vec2(100 * sw, 100 * sw), sw);
	rocker->setTag(ROCKER_TAG);
	rocker->startRocker(true);
	addChild(rocker, 1000);

	auto* MUI = MainGameUI::createMainGameUI();
	MUI->setTag(MUI_TAG);
	addChild(MUI, 999);

	if (!createDecorats())
	{
		return false;
	}

	Util::initMonsters();
	levelDataInit();
	scheduleUpdate();
	return true;
}

void MainGame::levelDataInit()
{
	gameover = false;
	stage = 0;
	playerkillcounts = 0;
	monsterFreshTimeConst = 2;
	monsterCountMax = 10;
	score = 0;
}

void MainGame::playerDataInit(Size visibleSize, Vec2 origin)
{
	auto* player = Player::createPlayerSprite(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y), 0);
	player->setTag(PLAYER_TAG);
	player->speed = 1 * Util::getSw();
	player->coldTime = 0.25f;
	player->hp = 100;
	player->hpUpper = 100;
	player->defencePercent = 0.1;
	player->playerDefence = 0.1;
	player->defence = 50;
	player->damagePercent = 0;
	addChild(player, 1);
}

bool MainGame::createMap(Size visibleSize, Vec2 origin)
{
	//根据关卡
	auto* map = Sprite::create("maps/desert_map.png");
	map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width;
	float winh = mywinsize.height;
	float spx = map->getTextureRect().getMaxX();
	float spy = map->getTextureRect().getMaxY();
	map->setScaleX(winw / spx);
	map->setScaleY(winh / spy);
	Util::setSw(winw / spx * 2);
	Util::setSh(winh / spy * 2);
	addChild(map, 0);
	return true;
}

bool MainGame::createDecorats()
{
	auto* player = (Player*)getChildByTag(PLAYER_TAG);
	for (int i = 0; i < 20; i++)
	{
		decorats.pushBack(Decorats::createDecoratsSprite(Vec2((0.5 * PIXELUNIT + PIXELUNIT * i) * sw, 0.5 * PIXELUNIT * sh), "desert", "cactus"));
	}
	for (int i = 0; i < 20; i++)
	{
		decorats.pushBack(Decorats::createDecoratsSprite(Vec2((0.5 * PIXELUNIT + PIXELUNIT * i) * sw, 9.5 * PIXELUNIT * sh), "desert", "cactus"));
	}
	for (int i = 1; i < 9; i++)
	{
		decorats.pushBack(Decorats::createDecoratsSprite(Vec2(0.5 * PIXELUNIT * sw, (0.5 * PIXELUNIT + PIXELUNIT * i) * sh), "desert", "cactus"));
	}
	for (int i = 1; i < 9; i++)
	{
		decorats.pushBack(Decorats::createDecoratsSprite(Vec2((PIXELUNIT * 19.5) * sw, (0.5 * PIXELUNIT + PIXELUNIT * i) * sh), "desert", "cactus"));
	}
	decorats.pushBack(Decorats::createDecoratsSprite(Vec2(288 * sw, 128 * sh), "desert", "cactus"));
	decorats.pushBack(Decorats::createDecoratsSprite(Vec2(288 * sw, 96 * sh), "desert", "cactus"));
	decorats.pushBack(Decorats::createDecoratsSprite(Vec2(288 * sw, 160 * sh), "desert", "cactus"));
	for (auto &decorat : decorats)
	{
		player->addChild(decorat->sprite);
	}
	return true;
}

void MainGame::monsterRefreshHandler()
{
	int oldStage = stage;
	stage = (int)(playerkillcounts / 10);
	if (oldStage != stage)
	{
		monsterFreshTimeConst = 2 - 0.1 * (stage >= 10 ? 10 : stage);
		monsterCountMax = 10 + (stage >= 10 ? 10 : stage);
	}
}

void MainGame::monsterCreateHandler()
{

	auto* player = (Player*)getChildByTag(PLAYER_TAG);
	int y = Util::getRandom(32, 284);
	int x = 0;
	int d = 0;
	if (Util::getRandom(0, 9) > 5)
	{
		x = Util::getRandom(32, 64);
		d = 1;
	}
	else
	{
		x = Util::getRandom(576, 608);
		d = 0;
	}
	int id = 0;
	if (stage < 10)
	{
		id = 0;
	}
	else if (stage >= 10 && stage < 20)
	{
		if (Util::getRandom(0, 10) <= stage - 10)
		{
			id = 1;
		}
		else
		{
			id = 0;
		}
	}
	else if (stage >= 20 && stage < 30)
	{
		if (Util::getRandom(0, 10) <= stage - 20)
		{
			id = 2;
		}
		else
		{
			id = 1;
		}
	}
	else
	{
		id = 2;
	}
	Monster* m = Monster::createMonsterSprite(Vec2(x * sw, y * sh), d, id, stage);
	monsters.pushBack(m);
	player->addChild(m->sprite);
	addChild(m->monsterHpBar, 100);
	addChild(m->monsterHpBarBg, 101);
}

void MainGame::monsterRefresh(float dt)
{
	auto* MUI = (MainGameUI*)getChildByTag(MUI_TAG);
	if (MUI->startRefresh)
	{
		monsterFreshTime += dt;
		if (monsterFreshTime > monsterFreshTimeConst)
		{
			monsterFreshTime = 0;
			if (monsterCount < monsterCountMax)
			{
				monsterCreateHandler();
				monsterCount++;
			}
		}
	}
}

void MainGame::update(float dt)
{
	if (!gameover)
	{
		objectEraseHandler();
		playerActHandler();
		playerMoveHandler();
		playerShootHandler(dt);
		bulletCollide();
		monsterRefreshHandler();
		monsterRefresh(dt);
		monsterHandler(dt);
		propsHandler();
		propsDisplayerHandler(dt);
		UIHandler(dt);
	}	
}

void MainGame::objectEraseHandler()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->isDelete)
		{
			bullets.eraseObject(bullets.at(i));
		}		
	}
}

void MainGame::playerActHandler()
{
	auto* rocker = (HRocker*)getChildByTag(ROCKER_TAG);
	auto* player = (Player*)getChildByTag(PLAYER_TAG);

	if (rocker->isCanMove && rocker->isShooting)
	{
		if (player->isRun == false)
		{
			player->isRun = true;
			player->action = 2;
			player->playerActs();
		}
		if (player->direction != rocker->sdirection)
		{
			player->direction = rocker->sdirection;
			player->action = 2;
			player->playerActs();
		}
		if (player->action != 2)
		{
			player->action = 2;
			player->playerActs();
		}
	}
	else if (rocker->isCanMove && !rocker->isShooting)
	{
		player->isRun = true;
		if (player->action != 1)
		{
			player->action = 1;
			player->playerActs();
		}
	}
	else if (!rocker->isCanMove && rocker->isShooting)
	{
		player->isRun = false;
		if (player->direction != rocker->sdirection)
		{
			player->direction = rocker->sdirection;
			player->playerActs();
		}
		player->action = 3;		
	}
	else if (!rocker->isCanMove && !rocker->isShooting)
	{
		player->isRun = false;
		if (player->action != 0)
		{
			player->playerResume();
		}
	}
}

void MainGame::playerMoveHandler()
{
	auto* rocker = (HRocker*)getChildByTag(ROCKER_TAG);
	auto* player = (Player*)getChildByTag(PLAYER_TAG);

	float dx = rocker->dx;
	float dy = rocker->dy;
	float angle = rocker->angle;
	if (dx == 0 && dy == 0 && angle == 0)
	{
		return;
	}
	if (player->isRun)
	{
		float _s = player->getSpeed();
		float a = angle * PI / 180;
		float x = (dx == 0) ? player->position.x : (dx > 0 ? (player->position.x + cos(a) * _s) : (player->position.x - cos(a) * _s));
		float y = (dy == 0) ? player->position.y : (dy > 0 ? (player->position.y + sin(a) * _s) : (player->position.y - sin(a) * _s));
		Vec2 oldPos = player->position;

		Vec2 xPos = Vec2(x, player->position.y);
		Vec2 yPos = Vec2(player->position.x, y);
		Vec2 xyPos = Vec2(dx == 0 ? player->position.x : (dx > 0 ? (player->position.x + cos(a) * _s) : (player->position.x - cos(a) * _s)), dy == 0 ? player->position.y : (dy > 0 ? (player->position.y + sin(a) * _s) : (player->position.y - sin(a) * _s)));
		Vec2 v[4] = { xyPos, xPos, yPos, oldPos };
		int i = 0;
		while (1)
		{
			player->position = v[i];
			player->bodysprite->setPosition(player->position);
			player->legsprite->setPosition(player->position);
			player->gunsprite->setPosition(player->position);
			bool isCollide = false;
			for (auto &decorat : decorats)
			{
				if (decorat->sprite->getBoundingBox().intersectsRect(player->bodysprite->getBoundingBox()))
				{
					isCollide = true;
					break;
				}
			}
			if (!isCollide)
			{
				return;
			}
			i++;
		}
		
		
	}
	
}

void MainGame::playerShootHandler(float dt)
{
	auto* rocker = (HRocker*)getChildByTag(ROCKER_TAG);
	auto* player = (Player*)getChildByTag(PLAYER_TAG);
	player->coldTimeCount += dt;
	if (rocker->isShooting && player->playerCanShoot())
	{
		float x = rocker->sangle;
		if (rocker->sangle > 5 && rocker->sangle < 45)
		{
			x = 5;
		}
		if (rocker->sangle < 85 && rocker->sangle >= 45)
		{
			x = 85;
		}
		//20为子弹伤害
		Bullet* bullet = Bullet::createBulletSprite(player->position, rocker->sdx, rocker->sdy, x, player->direction, Util::getRandom(19, 21));
		bullets.pushBack(bullet);
		bullet->sprite->setScale(sw / 1.75);
		addChild(bullet);
		player->playerActs(1);
	}
}

void MainGame::bulletCollide()
{
	auto* player = (Player*)getChildByTag(PLAYER_TAG);
	for (int j = 0; j < monsters.size(); j++)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (!bullets.at(i)->isDelete && monsters.at(j)->sprite->getBoundingBox().intersectsRect(bullets.at(i)->sprite->getBoundingBox()))
			{
				monsters.at(j)->hp -= bullets.at(i)->damage * (1 + player->damagePercent);
				bullets.at(i)->removeFromParent();
				bullets.at(i)->isDelete = true;
				break;
			}
		}
		if (monsters.at(j)->hp <= 0)
		{
			monsterDeadHandler(monsters.at(j));
			break;
		}
	}
}

void MainGame::monsterHandler(float dt)
{
	auto* MUI = (MainGameUI*)getChildByTag(MUI_TAG);
	if (MUI->startRefresh)
	{
		auto* player = (Player*)getChildByTag(PLAYER_TAG);
		for (auto &monster : monsters)
		{
			float x = player->position.x - monster->position.x;
			float y = player->position.y - monster->position.y;
			float distance = sqrt(pow(x, 2) + pow(y, 2));
			if (distance < PIXELUNIT * Util::getSw() / 2)
			{
				if (monster->action != 1)
				{
					monster->action = 1;
					monster->monsterActs();
				}
				if (player->protectTime > 2)
				{
					player->protectTime = 0;
					player->protect = true;
					float dAVG = 0;
					if (Util::getRandom(0, 9) > 5)
					{
						dAVG = monster->damageAvg;
					}
					else
					{
						dAVG = -monster->damageAvg;
					}
					player->takeDamage(monster->damage + dAVG);
					if (player->hp < 0)
					{
						player->hp = 0;
						gameover = true;
					}
				}
			}
			else
			{
				if (monster->action != 0)
				{
					monster->action = 0;
					monster->monsterActs();
				}
				float lx = x * 1 / distance; //x轴方向力 1为玩家引力
				float ly = y * 1 / distance;
				for (int i = 0; i < monsters.size(); i++)
				{
					if (sqrt(pow(monster->position.x - monsters.at(i)->position.x, 2) + pow(monster->position.y - monsters.at(i)->position.y, 2)) <= monster->radius + monsters.at(i)->radius && monster != monsters.at(i))
					{
						float mx = monster->position.x - monsters.at(i)->position.x;
						float my = monster->position.y - monsters.at(i)->position.y;
						float mdistance = sqrt(pow(mx, 2) + pow(my, 2));
						float monx = mx * 1 / mdistance;//1为怪物斥力
						float mony = my * 1 / mdistance;
						lx += monx;
						ly += mony;
					}
				}
				for (int i = 0; i < decorats.size(); i++)
				{
					if (sqrt(pow(monster->position.x - decorats.at(i)->position.x, 2) + pow(monster->position.y - decorats.at(i)->position.y, 2)) <= monster->radius + decorats.at(i)->radius)
					{
						float mx = monster->position.x - decorats.at(i)->position.x;
						float my = monster->position.y - decorats.at(i)->position.y;
						float mdistance = sqrt(pow(mx, 2) + pow(my, 2));
						float monx = mx * 1 / mdistance;//1为障碍物斥力
						float mony = my * 1 / mdistance;
						lx += monx;
						ly += mony;
					}
				}

				float dx = lx * monster->speed / 1;
				float dy = ly * monster->speed / 1;
				monster->actionHandler(Vec2(dx, dy), player->position);
			}

			monster->sprite->setZOrder((int)((320 - monster->sprite->getPosition().y / sh) * 2));
			if (monster->hp != monster->hpUpper)
			{
				monster->monsterHpBar->setVisible(true);
				monster->monsterHpBarBg->setVisible(true);
			}
			else
			{
				monster->monsterHpBar->setVisible(false);
				monster->monsterHpBarBg->setVisible(false);
			}
			monster->monsterHpBar->setZOrder((int)((320 - monster->sprite->getPosition().y / sh) * 2 + 1));
			monster->monsterHpBarBg->setZOrder((int)((320 - monster->sprite->getPosition().y / sh) * 2));
			monster->monsterHpBar->setPosition(Vec2(monster->position.x, monster->position.y + 0.5f * PIXELUNIT * Util::getSh()));
			monster->monsterHpBarBg->setPosition(Vec2(monster->position.x, monster->position.y + 0.5f * PIXELUNIT * Util::getSh()));
			monster->monsterHpBar->setPercentage(monster->hp * 100 / monster->hpUpper);
			if (monster->hp != monster->hpUpper)
			{
				if (monster->hpBarVisTime < HPVISTIME)
				{
					monster->hpBarVisTime += dt;
					monster->monsterHpBar->setOpacity(255);
					monster->monsterHpBarBg->setOpacity(255);
				}
				else
				{
					monster->monsterHpBar->setOpacity(100);
					monster->monsterHpBarBg->setOpacity(100);
				}
			}
			if (monster->hp != monster->lastHp)
			{
				monster->hpBarVisTime = 0;
			}
			monster->lastHp = monster->hp;
		}
	}
}

void MainGame::monsterDeadHandler(Monster* monster)
{
	auto* player = (Player*)getChildByTag(PLAYER_TAG);
	score += monster->score;
	

	if (Util::getRandom(0, 100) < monster->dropPercent * 100)
	{
		InstantProps* i = InstantProps::createPropsSprite(monster->position, Util::getRandomProps());
		props.pushBack(i);
		player->addChild(i->sprite);
	}
	

	monster->sprite->removeFromParent();
	monster->monsterHpBar->removeFromParent();
	monster->monsterHpBarBg->removeFromParent();
	monsters.eraseObject(monster);
	monsterCount--;
	playerkillcounts++;
}

void MainGame::propsHandler()
{
	auto* player = (Player*)getChildByTag(PLAYER_TAG);	
		
	for (int j = 0; j < props.size(); j++)
	{
		if (props.at(j)->isDelete)
		{
			props.at(j)->sprite->removeFromParent();
			props.eraseObject(props.at(j));
			continue;
		}
		float x = player->position.x - props.at(j)->position.x;
		float y = player->position.y - props.at(j)->position.y;
		float distance = sqrt(pow(x, 2) + pow(y, 2));
		if (distance < PIXELUNIT * Util::getSw() / 2)
		{
			getProps(props.at(j)->id);
			props.at(j)->isDelete = true;
		}
	}
}

void MainGame::propsDisplayerHandler(float dt)
{
	if (props.size() > 0)
	{
		for (auto &prop : props)
		{
			prop->existTime += dt;
			if (prop->existTime > 3 && prop->existTime < 7)
			{
				prop->sprite->setOpacity((255 - (prop->existTime - 3) * 255 / 4));
			}
			else if (prop->existTime >= 7)
			{
				prop->isDelete = true;
			}
		}
	}	
}

void MainGame::getProps(int id)
{
	auto* player = (Player*)getChildByTag(PLAYER_TAG);

	if (id == 0)
	{
		player->hp += 10 + stage / 10;
		if (player->hp > player->hpUpper)
		{
			player->hp = player->hpUpper;
		}
	}
	else if (id == 1)
	{
		for (int i = 0; i < STATUSMAX; i++)
		{
			if (!player->statusArr[i]._exec)
			{
				player->statusArr[i]._exec = true;
				player->statusArr[i].addition = ADDI(SPEED);
				player->statusArr[i].execTime = 0;
				player->statusArr[i].time = 10;
				player->statusArr[i].percent = 0.5;
				break;
			}
		}	
	}
	else if (id == 2)
	{
		player->damagePercent += (0.8 + stage / 50);
	}
	else if (id == 4)
	{
		player->defence += 20 + stage / 10;
	}
	else if (id == -1)
	{
		score += 66;
	}
}

void MainGame::UIHandler(float dt)
{
	auto* player = (Player*)getChildByTag(PLAYER_TAG);
	auto* MUI = (MainGameUI*)getChildByTag(MUI_TAG);
	MUI->poslabel->setString(StringUtils::format("%d,%d", (int)(player->position.x / sw), (int)(player->position.y / sh)));
	MUI->playerHpBar->setPercentage(player->hp * 100 / player->hpUpper);
	MUI->playerHpLabel->setString(StringUtils::format("%d/%d", (int)(player->hp), (int)(player->hpUpper)));
	MUI->stageLabel->setString(StringUtils::format("Level: %d Kill: %d", stage, playerkillcounts));
	MUI->scoreLabel->setString(StringUtils::format("Score: %d", (int)score));
	MUI->defenceBar->setPercentage(player->defence >= 100 ? 99.99 : player->defence);
	MUI->defenceLabel->setString(StringUtils::format("%d", (int)(player->defence)));
	if (!MUI->startRefresh)
	{
		MUI->startTime += dt;
		if (5 - MUI->startTime < 0)
		{
			MUI->startRefresh = true;
			MUI->startTime = 0;
			MUI->startTimeLabel->setVisible(false);
		}
		else
		{
			if ((int)(5 - MUI->startTime) != 0)
			{
				MUI->startTimeLabel->setString(StringUtils::format("%d!", (int)(5 - MUI->startTime)));
			}
			else
			{
				MUI->startTimeLabel->setString(StringUtils::format("Begin!"));
			}
		}		
	}
	if (gameover)
	{
		MUI->startTimeLabel->setString("GAMEOVER!");
		MUI->startTimeLabel->setVisible(true);
	}
}
