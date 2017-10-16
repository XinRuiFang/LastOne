#include "Decorats.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;


Decorats* Decorats::createDecoratsSprite(Point position, const char* area, const char* type)
{
	Decorats* decorat = new Decorats();
	if (decorat && decorat->init())
	{
		decorat->autorelease();
		decorat->initDecorats(position, area, type);
		return decorat;
	}
	CC_SAFE_DELETE(decorat);
	return NULL;
}

bool Decorats::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void Decorats::initDecorats(Point position, const char* area, const char* type)
{
	this->position = position;
	this->area = area;
	this->type = type;
	this->radius = 16 * Util::getSw();	
	sprite = Sprite::create(String::createWithFormat("decorats/%s_%s.png", area, type)->getCString(), Rect(0, 0, PIXELUNIT, PIXELUNIT));
	sprite->setPosition(position);
	sprite->runAction(this->createAnimate());
	sprite->setScale(Util::getSw());
	sprite->setZOrder((int)((320 - position.y / Util::getSh()) * 2));
}

Animate* Decorats::createAnimate()
{
	Vector<SpriteFrame*> frameArr;
	for (int i = 0; i < NUMD_1; i++)
	{
		auto* frame = SpriteFrame::createWithTexture(sprite->getTexture(), Rect(i * PIXELUNIT, 0, PIXELUNIT, PIXELUNIT));
		frameArr.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArr);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.6f);
	return Animate::create(animation);
}