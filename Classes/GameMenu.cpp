#include "GameMenu.h"
#include "Util.h"
#include "MainGame.h"

USING_NS_CC;

Scene* GameMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMenu::create();

	scene->addChild(layer);

	return scene;
}

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto* chnStrings = Dictionary::createWithContentsOfFile("fonts/CN_library.xml");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = Sprite::create("maps/game_map.png");

	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width;
	float winh = mywinsize.height;
	float spx = backGround->getTextureRect().getMaxX();
	float spy = backGround->getTextureRect().getMaxY();
	backGround->setScaleX(winw / spx);
	backGround->setScaleY(winh / spy);

	Util::setSw(winw / spx);
	Util::setSh(winh / spy);

	addChild(backGround, 0);

	auto level_btn = MenuItemImage::create("ui/gameMap_btn_up.png", "ui/gameMap_btn_down.png", this, menu_selector(GameMenu::level_BtnCallBack));
	level_btn->setPosition(Vec2(visibleSize.width / 2 + origin.x - 416 * Util::getSw(), visibleSize.height / 2 + origin.y + 192 * Util::getSh()));
	level_btn->setScale(Util::getSw());

	auto level_btn_label = LabelTTF::create("1", "Tensentype ENuoJ", 36);
	level_btn_label->setPosition(Vec2(visibleSize.width / 2 + origin.x - 416 * Util::getSw(), visibleSize.height / 2 + origin.y + 192 * Util::getSh()));
	level_btn_label->setScale(Util::getSw());

	auto map_btn = MenuItemImage::create("ui/gameMap_map_up.png", "ui/gameMap_map_down.png", this, menu_selector(GameMenu::map_BtnCallBack));
	map_btn->setPosition(Vec2(visibleSize.width / 2 + origin.x + 224 * Util::getSw(), visibleSize.height / 2 + origin.y - 208 * Util::getSh()));
	map_btn->setScale(Util::getSw());

	const char *str0 = ((String*)chnStrings->objectForKey("@menu0"))->getCString();
	const char *str1 = ((String*)chnStrings->objectForKey("@menu1"))->getCString();
	const char *str2 = ((String*)chnStrings->objectForKey("@menu2"))->getCString();
	auto map_btn_label = LabelTTF::create(str0, "Tensentype ENuoJ", 36);
	map_btn_label->setPosition(Vec2(visibleSize.width / 2 + origin.x + 224 * Util::getSw(), visibleSize.height / 2 + origin.y - 245 * Util::getSh()));
	map_btn_label->setScale(Util::getSw());

	auto chara_btn = MenuItemImage::create("ui/gameMap_chara_up.png", "ui/gameMap_chara_down.png", this, menu_selector(GameMenu::chara_BtnCallBack));
	chara_btn->setPosition(Vec2(visibleSize.width / 2 + origin.x + 384 * Util::getSw(), visibleSize.height / 2 + origin.y - 208 * Util::getSh()));
	chara_btn->setScale(Util::getSw());

	auto chara_btn_label = LabelTTF::create(str1, "Tensentype ENuoJ", 36);
	chara_btn_label->setPosition(Vec2(visibleSize.width / 2 + origin.x + 384 * Util::getSw(), visibleSize.height / 2 + origin.y - 245 * Util::getSh()));
	chara_btn_label->setScale(Util::getSw());

	auto settings_btn = MenuItemImage::create("ui/gameMap_settings_up.png", "ui/gameMap_settings_down.png", this, menu_selector(GameMenu::settings_BtnCallBack));
	settings_btn->setPosition(Vec2(visibleSize.width / 2 + origin.x + 544 * Util::getSw(), visibleSize.height / 2 + origin.y - 208 * Util::getSh()));
	settings_btn->setScale(Util::getSw());

	auto settings_btn_label = LabelTTF::create(str2, "Tensentype ENuoJ", 36);
	settings_btn_label->setPosition(Vec2(visibleSize.width / 2 + origin.x + 544 * Util::getSw(), visibleSize.height / 2 + origin.y - 245 * Util::getSh()));
	settings_btn_label->setScale(Util::getSw());

	auto menu = Menu::create(level_btn, map_btn, chara_btn, settings_btn, NULL);
	menu->setPosition(Point::ZERO);

	/*addChild(map_btn, 1);
	addChild(chara_btn, 1);
	addChild(settings_btn, 1);*/
	addChild(level_btn_label, 2);
	addChild(map_btn_label, 2);
	addChild(chara_btn_label, 2);
	addChild(settings_btn_label, 2);
	addChild(menu, 1);

	return true;
}

void GameMenu::level_BtnCallBack(Ref* pSender)
{
	Director::sharedDirector()->replaceScene(TransitionFade::create(3.0f, MainGame::createScene()));
}

void GameMenu::map_BtnCallBack(Ref* pSender)
{

}

void GameMenu::chara_BtnCallBack(Ref* pSender)
{

}

void GameMenu::settings_BtnCallBack(Ref* pSender)
{

}