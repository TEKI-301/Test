#include"SelectLevelScene.h"
#include"HelloWorldScene.h"
#include"GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SelectLevel::createScene()
{
	return SelectLevel::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SelectLevel::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//得到屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying())
	{
		audio->playBackgroundMusic("Audio/WorldBGM.mp3", true);
	}

	//backbottom
	
	MenuItemImage* returnItem = MenuItemImage::create(
		"SelectLevel/back.png",
		"SelectLevel/back2.png",
		CC_CALLBACK_1(SelectLevel::menuReturnCallBack, this)
	);
	
	if (returnItem == nullptr ||
		returnItem->getContentSize().width <= 0 ||
		returnItem->getContentSize().height <= 0)
	{
		//改
		problemLoading("'return.png'");
	}
	else
	{
		float x = origin.x + returnItem->getContentSize().width;
		float y = visibleSize.height - returnItem->getContentSize().height;
		returnItem->setPosition(Vec2(x, y));
	}
	
	MenuItemImage* levelItem_1 = MenuItemImage::create(
		"SelectLevel/1.png",
		"SelectLevel/1.png",
		CC_CALLBACK_1(SelectLevel::menuLevelCallBack_1, this)
	);
	
	if (levelItem_1 == nullptr ||
		levelItem_1->getContentSize().width <= 0 ||
		levelItem_1->getContentSize().height <= 0)
	{
		problemLoading("'Level/1.png'");
	}
	else
	{
		float x = origin.x + 80.0;
		float y = visibleSize.height - 550.0;
		levelItem_1->setPosition(Vec2(x, y));
	}

	MenuItemImage* levelItem_2 = MenuItemImage::create(
		"SelectLevel/2.png",
		"SelectLevel/2.png",
		CC_CALLBACK_1(SelectLevel::menuLevelCallBack_2, this)
	);
	
	if (levelItem_2 == nullptr ||
		levelItem_2->getContentSize().width <= 0 ||
		levelItem_2->getContentSize().height <= 0)
	{
		problemLoading("'Level/2.png'");
	}
	else
	{
		float x = origin.x + 200.0;
		float y = visibleSize.height - 550.0;
		levelItem_2->setPosition(Vec2(x, y));
	}

	MenuItemImage* levelItem_3 = MenuItemImage::create(
		"SelectLevel/3.png",
		"SelectLevel/3.png",
		CC_CALLBACK_1(SelectLevel::menuLevelCallBack_3, this)
	);

	if (levelItem_3 == nullptr ||
		levelItem_3->getContentSize().width <= 0 ||
		levelItem_3->getContentSize().height <= 0)
	{
		problemLoading("'Level/3.png'");
	}
	else
	{
		float x = origin.x + 320.0;
		float y = visibleSize.height - 550.0;
		levelItem_3->setPosition(Vec2(x, y));
	}

	Menu* mu = Menu::create(returnItem, levelItem_1, levelItem_2, levelItem_3, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu, 1);


	// add the picture splash screen"
	auto background = Sprite::create("SelectLevel/SelectBG.png");
	if (background == nullptr)
	{
		problemLoading("'SelectLevel/SelectBG.png.png'");
	}
	else
	{

		// position the sprite on the center of the screen
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(background, 0);
	}

	//用处?
	scheduleUpdate();

	return true;
}

void SelectLevel::menuReturnCallBack(Ref * pSender)
{
	unscheduleUpdate();
	auto nextScene = HelloWorld::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
}

void SelectLevel::menuLevelCallBack_1(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止播放背景音乐。

	auto nextScene = GameScene::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;

}

void SelectLevel::menuLevelCallBack_2(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止播放背景音乐。

	auto nextScene = GameScene::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;

	/*
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //停止播放背景音乐。

	static bool once = true;
	if (once)
	{
		clientInit();
		once = false;
	}
	*/
}

void SelectLevel::menuLevelCallBack_3(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止播放背景音乐。
	auto nextScene = GameScene::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;


}