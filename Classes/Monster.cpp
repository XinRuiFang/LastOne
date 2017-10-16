#include "Monster.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;
#define PI 3.1415926

Monster* Monster::createMonsterSprite(Point position, int direction, int id, int stage)
{
	Monster* monster = new Monster();
	if (monster && monster->init())
	{
		monster->autorelease();
		monster->initMonster(direction, position, id, stage);
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Monster::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void Monster::initMonster(int direction, cocos2d::Point position, int id, int stage)
{
	this->position = position;
	this->action = 0;	
	this->radius = 10 * Util::getSw();	
	this->hpBarVisTime = 0;

	auto mhb = Sprite::create("ui/monsterHpBar.png");
	monsterHpBar = ProgressTimer::create(mhb);
	monsterHpBar->setType(ProgressTimer::Type::BAR);
	monsterHpBar->setScale(Util::getSw());
	monsterHpBar->setPosition(Vec2(position.x, position.y + 0.5f * PIXELUNIT * Util::getSh()));
	monsterHpBar->setColor(Color3B::RED);
	monsterHpBar->setPercentage(99.99f);
	monsterHpBar->setMidpoint(Point(0, 0.5));
	monsterHpBar->setBarChangeRate(Point(1, 0));
	monsterHpBarBg = Sprite::create("ui/monsterHpBarBg.png");	
	monsterHpBarBg->setScale(Util::getSw());	
	monsterHpBarBg->setPosition(Vec2(position.x, position.y + 0.5f * PIXELUNIT * Util::getSh()));

	for (auto &data : Util::getMonsterData())
	{
		if (id == data.id)
		{
			name = data.name;
			hpUpper = data.hpUpper * (1 + stage / 15);
			speed = data.speed * Util::getSw();
			damage = data.damage * (1 + stage / 30);
			damageAvg = data.damageAvg * (1 + stage / 30);
			score = data.score * (1 + stage / 30);
			dropPercent = data.dropPercent - (stage / 100) / 10;
			break;
		}
	}
	this->hp = hpUpper;
	this->lastHp = hpUpper;
	const char* str = String::createWithFormat("monsters/%s.png", name.c_str())->getCString();
	sprite = Sprite::create(str, Rect(0, 0, PIXELUNIT, PIXELUNIT));
	sprite->setPosition(position);
	sprite->setScale(Util::getSw());
	sprite->runAction(this->createAnimate(direction, action));

	monsterHpBar->setVisible(false);
	monsterHpBarBg->setVisible(false);
}
// walk 0
Animate* Monster::createAnimate(int direction, int action)
{
	Vector<SpriteFrame*> frameArr;
	for (int i = 0; i < NUM_M; i++)
	{
		auto* frame = SpriteFrame::createWithTexture(sprite->getTexture(), Rect(i * PIXELUNIT, (action * 2 + direction)* PIXELUNIT, PIXELUNIT, PIXELUNIT));
		frameArr.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArr);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.3f);
	return Animate::create(animation);
}

void Monster::monsterActs()
{
	sprite->stopAllActions();
	auto* animate = this->createAnimate(direction, action);
	sprite->runAction(animate);
}

void Monster::actionHandler(Vec2 target,Point playerPos)
{
	float dx = playerPos.x - position.x;
	float dy = playerPos.y - position.y;
	float r = sqrt(dx*dx + dy*dy);
	int oldDir = direction;
	if (dx >= 0)
	{
		direction = 1;
	}
	else
	{
		direction = 0;
	}	
	if (oldDir != direction)
	{
		monsterActs();
	}
	position = Vec2(position.x + target.x, position.y + target.y);
	sprite->setPosition(position);
}