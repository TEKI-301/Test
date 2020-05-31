#include "HelloWorldScene.h"
#include "SetVolumeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SetVolume::createScene()
{
	return SetVolume::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SetVolume::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto setPanel = Sprite::create("SetVolume/SetPanel.png");
	if (setPanel == nullptr)
	{
		problemLoading("SetVolume/SetPanel.png");
	}
	else
	{
		// position the sprite on the center of the screen
		setPanel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(setPanel, 1);
	}

	auto ReturnItem = MenuItemImage::create(
		"SetVolume/Return.png",
		"SetVolume/Return.png",
		CC_CALLBACK_1(SetVolume::menuReturnCallback, this));

	if (ReturnItem == nullptr ||
		ReturnItem->getContentSize().width <= 0 ||
		ReturnItem->getContentSize().height <= 0)
	{
		problemLoading("'Return.png'");
	}
	else
	{
		ReturnItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	}

	auto menu = Menu::create(ReturnItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//ÓÎÏ·±³¾°
	auto sprite = Sprite::create("SetVolume/SetBG.png");
	if (sprite == nullptr)
	{
		problemLoading("'SetVolume/SetBG.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}

	return true;
}

void SetVolume::menuReturnCallback(Ref *pSender)
{
	auto nextScene = HelloWorld::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;
}
