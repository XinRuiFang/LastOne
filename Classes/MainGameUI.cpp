#include "MainGameUI.h"
#include "Util.h"

USING_NS_CC;

MainGameUI* MainGameUI::createMainGameUI()
{
	MainGameUI* layer = MainGameUI::create();
	if (layer)
	{
		layer->MainGameUIInit();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

void MainGameUI::MainGameUIInit()
{
	startRefresh = false;
	startTime = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	poslabel = Label::create("0,0", "Arial", (int)(18 * Util::getSw()), Size::ZERO, TextHAlignment::RIGHT, TextVAlignment::TOP);
	poslabel->setPosition(Vec2(100, visibleSize.height - 50));
	testlabel = Label::create("0,0", "Arial", (int)(18 * Util::getSw()), Size::ZERO, TextHAlignment::RIGHT, TextVAlignment::TOP);
	testlabel->setPosition(Vec2(100, visibleSize.height - 100));

	startTimeLabel = Label::create("0", "Arial", (int)(50 * Util::getSw()), Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	startTimeLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	playerHpLabel = Label::create("0", "Arial", (int)(18 * Util::getSw()), Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	defenceLabel = Label::create("0", "Arial", (int)(14 * Util::getSw()), Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);

	auto phb = Sprite::create("ui/playerHpBar.png");
	playerHpBarBg = Sprite::create("ui/playerHpBarBg.png");
	
	playerHpBarBg->setScale(Util::getSw());
	playerHpBarBg->setPosition(Vec2(10 + playerHpBarBg->getBoundingBox().size.width / 2, visibleSize.height - playerHpBarBg->getBoundingBox().size.height));

	playerHpBar = ProgressTimer::create(phb);
	playerHpBar->setType(ProgressTimer::Type::BAR);
	playerHpBar->setScale(Util::getSw());
	playerHpBar->setPosition(Vec2(10 + playerHpBarBg->getBoundingBox().size.width / 2, visibleSize.height - playerHpBar->getBoundingBox().size.height));
	playerHpBar->setColor(Color3B::RED);
	playerHpBar->setPercentage(99.99f);
	playerHpBar->setMidpoint(Point(0, 0.5));
	playerHpBar->setBarChangeRate(Point(1, 0));
	playerHpLabel->setPosition(Vec2(10 + playerHpBarBg->getBoundingBox().size.width / 2, visibleSize.height - playerHpBar->getBoundingBox().size.height));

	auto pdb = Sprite::create("ui/defenceBar.png");
	defenceBarBg = Sprite::create("ui/defenceBarBg.png");

	defenceBarBg->setScale(Util::getSw());
	defenceBarBg->setPosition(Vec2(10 + 16 * Util::getSw() + defenceBarBg->getBoundingBox().size.width / 2, visibleSize.height - defenceBarBg->getBoundingBox().size.height - playerHpBar->getBoundingBox().size.height - 10));

	defenceBar = ProgressTimer::create(pdb);
	defenceBar->setType(ProgressTimer::Type::BAR);
	defenceBar->setScale(Util::getSw());
	defenceBar->setPosition(Vec2(10 + 16 * Util::getSw() + defenceBarBg->getBoundingBox().size.width / 2, visibleSize.height - defenceBar->getBoundingBox().size.height - playerHpBar->getBoundingBox().size.height - 10));
	defenceBar->setColor(Color3B::BLUE);
	defenceBar->setPercentage(99.99f);
	defenceBar->setMidpoint(Point(0, 0.5));
	defenceBar->setBarChangeRate(Point(1, 0));
	defenceLabel->setPosition(Vec2(10 + 16 * Util::getSw() + defenceBarBg->getBoundingBox().size.width / 2, visibleSize.height - defenceBar->getBoundingBox().size.height - playerHpBar->getBoundingBox().size.height - 10));
	defenceIcon = Sprite::create("ui/defenceIcon.png");
	defenceIcon->setPosition(Vec2(10 * Util::getSw() + defenceIcon->getBoundingBox().size.width / 2, visibleSize.height - defenceBar->getBoundingBox().size.height - playerHpBar->getBoundingBox().size.height - 10));
	defenceIcon->setScale(Util::getSw());

	stageLabel = Label::create("0,0", "Arial", (int)(18 * Util::getSw()), Size::ZERO, TextHAlignment::CENTER, TextVAlignment::TOP);
	stageLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - playerHpBar->getBoundingBox().size.height));

	scoreLabel = Label::create("0,0", "Arial", (int)(18 * Util::getSw()), Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	scoreLabel->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - playerHpBar->getBoundingBox().size.height));

	addChild(scoreLabel, 0);
	addChild(stageLabel, 0);
	addChild(playerHpBar, 1);
	addChild(playerHpBarBg, 0);
	addChild(playerHpLabel, 2);
	addChild(defenceBar, 1);
	addChild(defenceBarBg, 0);
	addChild(defenceLabel, 2);
	addChild(defenceIcon, 2);
	addChild(poslabel, 3);
	//addChild(testlabel, 3);
	addChild(startTimeLabel, 3);
}