#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BattleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	//////////////////////////////
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(BattleScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	auto label = Label::createWithTTF("Time Killer", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + label->getContentSize().height));
	this->addChild(label, 1);

	// add "BattleScene" splash screen"
	auto sprite = Sprite::create("bg.jpg");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(visibleSize.width / sprite->getContentSize().width, 
					visibleSize.height / sprite->getContentSize().height);
	this->addChild(sprite, 0);

	// 添加英雄标签
	for (int i = 0; i < 4; ++i){
		// 背景
		auto label = Sprite::create("label.png");
		label->setScale(100 / label->getContentSize().width,
			100 / label->getContentSize().height);
		label->setPosition(Vec2(128 + i * 100, 730));
		sprite->addChild(label);
		// 回形针
		auto clip = Sprite::create("clip.png");
		clip->setScale(20 / clip->getContentSize().width,
			40 / clip->getContentSize().height);
		clip->setPosition(Vec2(128 + i * 100, 764));
		sprite->addChild(clip);
	}

	// 添加标签页
	for (int i = 0; i < 4; ++i){
		auto tap_name = String::createWithFormat("tap_%d.png", i);
		auto tap = Sprite::create(tap_name->getCString());
		tap->setScale(50 / tap->getContentSize().width,
			35 / tap->getContentSize().height);
		tap->setPosition(Vec2(525 - i * 1, 720 - i * 80));
		sprite->addChild(tap);
	}

	// 战斗画面
	auto screen = Sprite::create("screen.png");
	screen->setScale(400 / screen->getContentSize().width,
		375 / screen->getContentSize().height);
	screen->setPosition(Vec2(270, 465));
	sprite->addChild(screen);
	
	//加载魔理沙动画
	auto marisa = Animation::create();
	for (int i = 0; i < 8; i++)
	{
		auto frame_name = String::createWithFormat("character/walkFront%03d.png", i);
		marisa->addSpriteFrameWithFileName(frame_name->getCString());
	}
	marisa->setDelayPerUnit(1.0 / 8.0); // 这个动画包含14帧，将会持续2.8秒.  
	marisa->setRestoreOriginalFrame(true); // 14帧播放完之后返回到第一帧 
	marisa->setLoops(-1);
	CCAnimate *action = CCAnimate::create(marisa);
	auto marisa_sprite = Sprite::create();
	marisa_sprite->runAction(action);// 
	marisa_sprite->setPosition(Vec2(180, 410));
	sprite->addChild(marisa_sprite, 5);

	// 背景动画


	// 战报
	auto standings = Label::createWithTTF("standings... standings... \nstandings... standings... \nstandings... ",
		"fonts/Marker Felt.ttf", 13);
	standings->setAlignment(TextHAlignment::CENTER);
	standings->setPosition(Vec2(origin.x + visibleSize.width / 2,
		115 + origin.y + label->getContentSize().height));
	this->addChild(standings, 4);

	return true;
}


void BattleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
