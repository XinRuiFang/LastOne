#include "Title.h"
#include "Util.h"
#include "MainGame.h"
#include "GameMenu.h"

USING_NS_CC;
#define UILAYER 98
#define UIMENU 99
#define UIMAIN 100
#define UILABEL 101

Scene* Title::createScene()
{
	auto scene = Scene::create();

	auto layer = Title::create();

	auto uiLayer = Title::uiLayer();
	uiLayer->setTag(UILAYER);
	uiLayer->setVisible(false);

	scene->addChild(layer);
	scene->addChild(uiLayer);

	return scene;
}
bool Title::init()
{
	if (!Layer::init())
	{
		return false;
	}
	show = false;
	opacity = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto* bg = Sprite::create("ui/titleBg.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width;
	float winh = mywinsize.height;
	float spx = bg->getTextureRect().getMaxX();
	float spy = bg->getTextureRect().getMaxY();
	sx = winw / spx;
	sy = winh / spy;
	bg->setScaleX(sy);
	bg->setScaleY(sy);
	Util::setSw(sx);
	Util::setSh(sy);
	
	addChild(bg, 0);

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	// °ó¶¨¼àÌýÊÂ¼þ
	listener->onTouchBegan = CC_CALLBACK_2(Title::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	scheduleUpdate();
	return true;

}

Layer* Title::uiLayer()
{
	auto* chnStrings = Dictionary::createWithContentsOfFile("fonts/CN_library.xml");
	auto* layer = Layer::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto* main = Sprite::create("ui/title_main.png");
	main->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 208 * Util::getSh()));
	main->setScaleX(Util::getSh());
	main->setScaleY(Util::getSh());
	main->setTag(UIMAIN);

	auto btn = MenuItemImage::create("ui/title_btn_up.png", "ui/title_btn_down.png", layer, menu_selector(Title::mainBtnCallBack));	
	btn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 160 * Util::getSh()));
	btn->setScaleX(Util::getSh());
	btn->setScaleY(Util::getSh());
	
	const char *str = ((String*)chnStrings->objectForKey("@start"))->getCString();
	auto* label = LabelTTF::create(str, "Tensentype ENuoJ", 36);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 160 * Util::getSh()));
	label->setScaleX(Util::getSh());
	label->setScaleY(Util::getSh());
	label->setTag(UILABEL);

	auto menu = Menu::create(btn, NULL);
	menu->setPosition(Point::ZERO);
	menu->setTag(UIMENU);

	layer->addChild(label, 2);
	layer->addChild(menu, 1);
	layer->addChild(main, 0);
	return layer;
}

void Title::mainBtnCallBack(Ref* pSender)
{
	//Director::sharedDirector()->replaceScene(TransitionMoveInR::create(3.0f, GameMenu::createScene()));
	Director::sharedDirector()->replaceScene(GameMenu::createScene());
}

bool Title::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	show = true;
	return true;
}
void Title::update(float dt)
{
	if (show && opacity != 255)
	{
		auto layer = getParent()->getChildByTag(UILAYER);

		auto main = layer->getChildByTag(UIMAIN);
		auto menu = layer->getChildByTag(UIMENU);
		auto label = layer->getChildByTag(UILABEL);
		
		if (opacity < 255)
		{			
			opacity += dt * 255 / 2;
		}
		else
		{
			opacity = 255;
		}
		layer->setVisible(true);
		main->setOpacity((int)opacity);
		menu->setOpacity((int)opacity);
		label->setOpacity((int)opacity);
	}
}
