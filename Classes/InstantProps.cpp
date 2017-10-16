#include "InstantProps.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;
InstantProps* InstantProps::createPropsSprite(cocos2d::Point position, int id)
{
	InstantProps* prop = new InstantProps();
	if (prop && prop->init())
	{
		prop->autorelease();
		prop->initProps(position, id);
		return prop;
	}
	CC_SAFE_DELETE(prop);
	return NULL;
}

bool InstantProps::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

//0 ҽ�ư� 1 ���� 2 ������ҩ 3 ������� 4 ���� 5 ���ﾲֹ 6 ���� 7 ���� 8 �޵�  -1���
void InstantProps::initProps(cocos2d::Point position, int id)
{
	this->id = id;
	this->position = position;
	existTime = 0;
	isDelete = false;
	if (id >= 0)
	{
		sprite = Sprite::create("instantProps.png", Rect((id % 6) * PIXELUNIT, (id / 6) * PIXELUNIT, PIXELUNIT, PIXELUNIT));		
	}
	else
	{
		sprite = Sprite::create("instantProps.png", Rect(0, 2 * PIXELUNIT, PIXELUNIT, PIXELUNIT));
		Vector<SpriteFrame*> frameArr;
		for (int i = 0; i < 6; i++)
		{
			auto* frame = SpriteFrame::createWithTexture(sprite->getTexture(), Rect(i * PIXELUNIT, 2 * PIXELUNIT, PIXELUNIT, PIXELUNIT));
			frameArr.pushBack(frame);
		}
		Animation* animation = Animation::createWithSpriteFrames(frameArr);
		animation->setLoops(-1);
		animation->setDelayPerUnit(0.1f);
		sprite->runAction(Animate::create(animation));
	}
	sprite->setPosition(position);
	sprite->setScale(Util::getSw() / 1.25f);

}