#include "Player.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;
#define PI 3.1415926

Player* Player::createPlayerSprite(Point position, int direction)
{
	Player* player = new Player();
	if (player && player->init())
	{
		player->autorelease();
		player->initPlayer(direction, position);
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void Player::initPlayer(int direction, cocos2d::Point position)
{
	this->position = position;
	this->action = 0;
	this->direction = direction;
	this->protectTime = 0;
	this->protect = false;
	this->coldTimeCount = 0;
	this->isRun = false;
	this->pTime = 0;
	this->playerVisable = true;
	bodysprite = Sprite::create("hero.png", Rect(0, 0, PIXELUNIT, PIXELUNIT));
	bodysprite->setPosition(position);
	bodysprite->runAction(this->createBodyAnimate(direction, action));
	bodysprite->setScale(Util::getSw());

	legsprite = Sprite::create("hero.png", Rect(4 * PIXELUNIT, 0, PIXELUNIT, PIXELUNIT));
	legsprite->setPosition(position);
	legsprite->runAction(this->createLegAnimate(direction, action));
	legsprite->setScale(Util::getSw());

	gunsprite = Sprite::create("gun_pistol.png", Rect(0, 0, PIXELUNIT, PIXELUNIT));
	gunsprite->setPosition(position);
	gunsprite->runAction(this->createGunAnimate(direction, action));
	gunsprite->setScale(Util::getSw());
	scheduleUpdate();
	
	addChild(legsprite);
	addChild(bodysprite);
	addChild(gunsprite);
}

// idle 0 walk 1 shoot-move 2 shoot 3
Animate* Player::createBodyAnimate(int direction, int action)
{
	Vector<SpriteFrame*> frameArr;
	setAnchorPoint(Point(0.5f, 0.5f));
	int a = action;
	if (a > 2)
	{
		a = 2;
	}
	for (int i = 0; i < NUM; i++)
	{
		auto* frame = SpriteFrame::createWithTexture(bodysprite->getTexture(), Rect(i * PIXELUNIT, (a * 4 + direction)* PIXELUNIT, PIXELUNIT, PIXELUNIT));
		frameArr.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameArr);
	animation->setLoops(-1);
	if (a == 2)
	{
		animation->setDelayPerUnit(0.1f);
	}
	else
	{
		animation->setDelayPerUnit(0.3f);
	}
	
	return Animate::create(animation);
}

Animate* Player::createGunAnimate(int direction, int action)
{
	Vector<SpriteFrame*> frameArr;
	switch (direction)
	{
	case 0:
		gunsprite->setAnchorPoint(Vec2(0.5f, 0.75f));
		break;
	case 1:
		gunsprite->setAnchorPoint(Vec2(0.75f, 0.5f));
		break;
	case 2:
		gunsprite->setAnchorPoint(Vec2(0.25f, 0.5f));
		break;
	case 3:
		gunsprite->setAnchorPoint(Vec2(0.5f, 0.25f));
		break;
	default:
		break;
	}
	int a = action;
	if (a >= 2)
	{
		gunVisable = true;
	}
	else
	{
		gunVisable = false;		
	}
	gunsprite->setVisible(gunVisable);
	
		switch (direction)
		{
		case 0:
			for (int i = 0; i < NUM; i++)
			{
				auto* frame = SpriteFrame::createWithTexture(gunsprite->getTexture(), Rect(i * 2 * PIXELUNIT, 0, PIXELUNIT, 2 * PIXELUNIT));
				frameArr.pushBack(frame);
			}
			break;
		case 1:
			for (int i = 0; i < NUM; i++)
			{
				auto* frame = SpriteFrame::createWithTexture(gunsprite->getTexture(), Rect(i * 2 * PIXELUNIT, 2 * PIXELUNIT, 2 * PIXELUNIT, PIXELUNIT));
				frameArr.pushBack(frame);
			}
			break;
		case 2:
			for (int i = 0; i < NUM; i++)
			{
				auto* frame = SpriteFrame::createWithTexture(gunsprite->getTexture(), Rect(i * 2 * PIXELUNIT, 3 * PIXELUNIT, 2 * PIXELUNIT, PIXELUNIT));
				frameArr.pushBack(frame);
			}
			break;
		case 3:
			for (int i = 0; i < NUM; i++)
			{
				auto* frame = SpriteFrame::createWithTexture(gunsprite->getTexture(), Rect(i * 2 * PIXELUNIT, 4 * PIXELUNIT, PIXELUNIT, 2 * PIXELUNIT));
				frameArr.pushBack(frame);
			}
			break;
		default:
			break;
		}	
	

	Animation* animation = Animation::createWithSpriteFrames(frameArr);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

Animate* Player::createLegAnimate(int direction, int action)
{
	Vector<SpriteFrame*> frameArr;
	setAnchorPoint(Point(0.5f, 0.5f));
	int a = 0;
	if (action == 0 || action == 3)
	{
		a = 1;
	}
	for (int i = 0; i < NUM; i++)
	{
		auto* frame = SpriteFrame::createWithTexture(legsprite->getTexture(), Rect((4 + i) * PIXELUNIT, (a * 4 + direction)* PIXELUNIT, PIXELUNIT, PIXELUNIT));
		frameArr.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameArr);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.3f);

	return Animate::create(animation);
}

void Player::playerActs()
{
	bodysprite->stopAllActions();
	legsprite->stopAllActions();
	gunsprite->stopAllActions();
	auto* animategun = this->createGunAnimate(direction, action);
	gunsprite->runAction(animategun);
	auto* animatebody = this->createBodyAnimate(direction, action);
	bodysprite->runAction(animatebody);
	auto* animateleg = this->createLegAnimate(direction, action);
	legsprite->runAction(animateleg);
}

void Player::playerActs(int i)
{
	bodysprite->stopAllActions();
	gunsprite->stopAllActions();
	auto* animategun = this->createGunAnimate(direction, action);
	gunsprite->runAction(animategun);
	auto* animatebody = this->createBodyAnimate(direction, action);
	bodysprite->runAction(animatebody);
}

void Player::takeDamage(float damage)
{
	//»¤¶Ü·ÀÓùdefencePercent¹ÖÎï¹¥»÷»¤¶ÜÉËº¦*2£¬ÈËÎï·ÀÓùplayerDefence£¬»¤¶ÜÈËÎï·ÀÓùÓÐ50%¼õÉË (2 - playerDefence - defencePercent) / 2 * damage  * 0.5
	if (defence > 0)
	{
		defence -= damage * (1 - defencePercent) * 2;
		hp -= (2 - playerDefence - defencePercent) / 2 * damage  * 0.5;
		if (defence <= 0)
		{
			defence = 0;
		}
	}
	else
	{
		hp -= damage * (1 - playerDefence);
	}
	
}

void Player::playerResume()
{
	gunsprite->stopAllActions();
	bodysprite->stopAllActions();
	legsprite->stopAllActions();
	this->action = 0;
	gunsprite->runAction(createGunAnimate(this->direction, this->action));
	bodysprite->runAction(createBodyAnimate(this->direction, this->action));
	legsprite->runAction(createLegAnimate(this->direction, this->action));
}

bool Player::playerCanShoot()
{
	if (coldTimeCount > coldTime)
	{
		coldTimeCount = 0;
		return true;
	}
	return false;
}

float Player::getSpeed()
{
	float _speed = speed;
	for (int i = 0; i < STATUSMAX;i++)
	{
		if (statusArr[i]._exec &&statusArr[i].addition == ADDI(SPEED))
		{
			_speed *= (1 + statusArr[i].percent);
		}
	}
	return _speed;
}

void Player::update(float dt)
{
	legsprite->setZOrder((int)((320 - bodysprite->getPosition().y / Util::getSh()) * 2) - 1);
	bodysprite->setZOrder((int)((320 - bodysprite->getPosition().y / Util::getSh()) * 2));
	gunsprite->setZOrder((int)((320 - gunsprite->getPosition().y / Util::getSh()) * 2) + 1);
	if (protectTime < 3)
	{
		protectTime += dt;
		if (protectTime > 2)
		{
			protect = false;
			bodysprite->setVisible(true);
			legsprite->setVisible(true);
			if (gunVisable)
			{
				gunsprite->setVisible(true);
			}
		}
	}
	if (protect)
	{
		pTime += dt;
		if (pTime > 0.2f)
		{

			playerVisable = !playerVisable;
			pTime = 0;
			bodysprite->setVisible(playerVisable);
			legsprite->setVisible(playerVisable);
			if (gunVisable)
			{
				gunsprite->setVisible(playerVisable);
			}
		}
	}
	for (int i = 0; i < STATUSMAX; i++)
	{
		if (statusArr[i]._exec)
		{
			statusArr[i].execTime += dt;
			if (statusArr[i].time < statusArr[i].execTime)
			{
				statusArr[i]._exec = false;
			}
		}	
	}
}