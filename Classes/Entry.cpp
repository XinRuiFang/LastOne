#include "Entry.h"
#include "Util.h"
#include "Title.h"

USING_NS_CC;
#define ENTRYSHOW 5

Scene* Entry::createScene()
{
	auto scene = Scene::create();

	auto layer = Entry::create();

	scene->addChild(layer);

	return scene;
}
bool Entry::init()
{
	if (!Layer::init())
	{
		return false;
	}
	showTime = 0;
	cs = true;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto* bg = Sprite::create("ui/entryBg.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width;
	float winh = mywinsize.height;
	float spx = bg->getTextureRect().getMaxX();
	float spy = bg->getTextureRect().getMaxY();
	bg->setScaleX(winw / spx);
	bg->setScaleY(winh / spy);
	Util::setSw(winw / spx * 2);
	Util::setSh(winh / spy * 2);
	addChild(bg, 0);

	scheduleUpdate();
	return true;
}

void Entry::update(float dt)
{
	showTime += dt;
	if (showTime > ENTRYSHOW && cs)
	{
		Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, Title::createScene()));
		cs = false;
	}
}