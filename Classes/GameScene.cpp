#include "GameScene.h"
#include"SelectLevelScene.h"
#include "SimpleAudioEngine.h"
#include"Animals/AnimalsSprite.h"

USING_NS_CC;

GameScene::GameScene()
	:spriteSheet(NULL),_score(0),
	haveEmpty(false),isAction(true),
	isTouchEna(true),staSprite(NULL),endSprite(NULL)
{
}

Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BGM
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying())
	{
		audio->playBackgroundMusic("Audio/PlayBGM.mp3", true);
	}

	auto closeItem = MenuItemImage::create(
		"HelloWorld/CloseNormal.png",
		"HelloWorld/CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuReturnCallBack, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		closeItem->setPosition(Vec2(150.0, 150.0));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite1 = Sprite::create("PlayGame/map1.png");
	if (sprite1 == nullptr)
	{
		problemLoading("'PlayGame/PlayBG.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite1, 1);
	}
	///////////////////////////////////////////////////
	/*
	auto sprite2 = Sprite::create("CatVertical_1.png");
	if (sprite2 == nullptr)
	{
		problemLoading("'Animals/Bird.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x+45, visibleSize.height / 2 + origin.y+45));
		// add the sprite as a child to this layer
		this->addChild(sprite2, 2);
	}
	
	
	*/

	//游戏背景
	auto sprite = Sprite::create("PlayGame/PlayBG.png");
	if (sprite == nullptr)
	{
		problemLoading("'PlayGame/PlayBG.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}
	/*
	if (!userDefault->getIntegerForKey("Int")) {
		userDefault->setIntegerForKey("Int", 0);
	}
	*/
	TTFConfig config("fonts/haibaoti.ttf", 30);
	// 最高分
	
	auto labelHScore = Label::createWithTTF(config, "Highest: 0");
	labelHScore->setPosition(Vec2(GAME_SCREEN_WIDTH - labelHScore->getContentSize().width, GAME_SCREEN_HEIGHT - labelHScore->getContentSize().height));
	labelHScore->setString(StringUtils::format("Highest: %d ", userDefault->getIntegerForKey("Int")));
	this->addChild(labelHScore);
	
	
	// 分数
	auto labelScore = Label::createWithTTF(config, "Score: 0");
	labelScore->setPosition(Vec2(GAME_SCREEN_WIDTH - labelHScore->getContentSize().width, GAME_SCREEN_HEIGHT - labelHScore->getContentSize().height * 2));
	labelScore->setTag(10);
	this->addChild(labelScore);
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimalsList.plist");
	//spriteSheet = SpriteBatchNode::create("AnimalsList.png");
	//addChild(spriteSheet, 2);

	///////////////////////////////////////////////////////
	/*
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("Animals\\CatVertical.plist", "Animals\\CatVertical.png");
	//Sprite *spr = Sprite::createWithSpriteFrameName("CatVertical_1.png");
	Animals *spr = new(std::nothrow) Animals;
	spr->initWithSpriteFrameName("Cat.png");
	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

	for (int i = 1; i <= 3; ++i)
	{
		SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("CatVertical_%d.png", i));
		sfme.pushBack(fname);
	}
	Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
	Animate* animate = Animate::create(animation);

	spr->runAction(RepeatForever::create(animate));

	spr->setPosition(Vec2(visibleSize.width / 2 + origin.x - 45, visibleSize.height / 2 + origin.y - 45));
	this->addChild(spr, 2);
	spr->stopAllActions();

	spr->setState(BOMB);
	
	///////////////////////////////////////////////

	
	getPositionMap(1);
	createSprite(1, 2);
	createSprite(3, 6);
	
	Animals *sp = map[3][6];

	Point staPos = sp->getPosition();
	Point endPos = positionOfItem(3, 0);
	sp->stopAllActions();
	sp->runAction(MoveTo::create(0.5, endPos));
	map[3][0] = sp;
	map[3][6] = NULL;
	sp->setRow(3);
	sp->setState(BOMB);
	sp->stopAllActions();
	sp->runAction(MoveTo::create(0.5, staPos));


	*/
	initMap();
	scheduleUpdate();

	// 触摸事件处理
	//auto mouseListener = EventListenerMouse::create();
	//mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//_eventDispatcher->addEventListenerWithFixedPriority(mouseListener, 2);
	
	return true;
}


void GameScene::createSprite(int row, int col)
{
	// 先创建一个精灵
	
	Animals *spr = Animals::create(row, col);

	// 创建动作动画
	Point endPosition = positionOfItem(row, col);
	Point startPosition = Point(endPosition.x, endPosition.y + GAME_SCREEN_HEIGHT/2 );
	spr->setPosition(startPosition);
	//float speed = startPosition.y / (2.5 * GAME_SCREEN_HEIGHT);
	float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 1.5;
	spr->runAction(MoveTo::create(speed, endPosition));
	// 加入到spriteSheet中,等待绘制
	//spriteSheet->addChild(spr);
	this->addChild(spr, 2);
	// 数组相应位置，置上寿司对象
	map[row][col] = spr;


}

void GameScene::getPositionMap(int level)
{
	 PosMap = PositionMap(level);
	 _row = PosMap.getRow();
	 _column = PosMap.getColumn();
}

// 获取坐标值
Point GameScene::positionOfItem(int row, int col)
{
	Point temp = PosMap.getPos(row, col);
	return temp;

}

// 初始化二维数组
void GameScene::initMap()
{
	getPositionMap(1);
	for (int r = 0; r < _row; ++r)
	{
		for (int c = 0; c < _column; ++c)
		{
			createSprite(r, c);
			//CCLOG("%d ",map[r][c]->getImgIndex() );
		}
		//CCLOG("***");
	}
	
}


void GameScene::fillSprite()
{
	// 重置移动方向标志
	isAction = true;
	int sum = 0;

	int *colEmptyInfo = (int *)malloc(sizeof(int) * _column);
	memset((void *)colEmptyInfo, 0, sizeof(int) * _column);

	// 将存在的寿司降落下来
	Animals *spr = NULL;
	for (int r = 0; r < _row; r++) 
	{
		int removedSpriteOfCol = 0;
		// 自底向上
		for (int c = 0; c < _column; c++) 
		{
			spr = map[r][c];
			if (spr == NULL)
			{
				++removedSpriteOfCol;
			}
			else
			{
				if (removedSpriteOfCol > 0)
				{
					// evey item have its own drop distance
					int newCol = c - removedSpriteOfCol;
					// switch in matrix
					map[r][newCol] = spr;
					map[r][c] = NULL;
					// move to new position
					Point startPosition = spr->getPosition();
					Point endPosition = positionOfItem(r, newCol);
					float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 1.5;
					spr->stopAllActions();// must stop pre drop action
					spr->runAction(CCMoveTo::create(speed, endPosition));
					// set the new row to item
					spr->setColumn(newCol);
				}
			}
		}

		// 记录相应列数移除的数量
		colEmptyInfo[r] = removedSpriteOfCol;
		sum += removedSpriteOfCol;
	}

	// 新建新的寿司，并降落
	for (int r = 0; r < _row; ++r) 
	{
		for (int c = _column - colEmptyInfo[r]; c < _column; ++c) 
		{
			createSprite(r, c);
		}
	}

	setScore(getScore() + sum * 30);
	free(colEmptyInfo);
}

void GameScene::menuReturnCallBack(cocos2d::Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止播放背景音乐。

	auto nextScene = SelectLevel::create();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem *item = (MenuItem*)pSender;

}

void GameScene::checkAndRemoveSprite()
{
	Animals *spr;
	// 设定寿司的忽视检查
	for (int r = 0; r < _row; ++r) 
	{
		for (int c = 0; c < _column; ++c) 
		{
			spr = map[r][c];
			//why
			if (!spr) 
			{
				log("!spr:checkAndRemoveSptite");
				continue;
			}
			spr->setIgnoreCheck(false);
		}
	}

	//why
	//不为空，不需要移动，无需忽视检查
	if (staSprite != NULL && !staSprite->getIsNeedRemove() && !staSprite->getIgnoreCheck()) 
	{
		removeAndPro(staSprite);
		staSprite = NULL;
	}
	if (endSprite != NULL && !endSprite->getIsNeedRemove() && !endSprite->getIgnoreCheck()) 
	{
		removeAndPro(endSprite);
		endSprite = NULL;
	}


	for (int r = 0; r < _row; ++r)
	{
		for (int c = 0; c < _column; ++c)
		{
			spr = map[r][c];
			//why
			if (!spr)
			{
				continue;
			}
			// 新变化的特殊寿司，不消除
			if (spr->getIgnoreCheck())
			{
				continue;
			}
			removeAndPro(spr);
		}
	}

	// 3.消除标记了的寿司
	removeSprite();
}

void GameScene::removeAndPro(Animals *spr)
{
	// 获取 横竖 两方向精灵
	std::list< Animals *> colChainList;
	getColChain(spr, colChainList);

	std::list< Animals *> rowChainList;
	getRowChain(spr, rowChainList);

	// 如果任意一方向的精灵都小于3个，直接return，不需要继续往下看了
	if (rowChainList.size() < 3 && colChainList.size() < 3)
	{
		return;
	}

	// 判断是交换产生的特效消除 还是 自由掉落 产生的特效消除
	//why
	bool isChangePro = false;

	if (rowChainList.size() >= 5) 
	{
		// 两方向精灵全部消除  并  产生五消除精灵（魔力鸟）
		if (colChainList.size() >= 3) 
		{

			removeListSpr(rowChainList, true, SUPERBIRD, isChangePro);
			removeListSpr(colChainList, false, SUPERBIRD, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false)
			{
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(SUPERBIRD);
			}
		}
		// 只消除 横向 精灵 ，产生五消精灵
		else
		{
			removeListSpr(rowChainList, true, SUPERBIRD, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false)
			{
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(SUPERBIRD);
			}
		}

		return;
	}
	if (colChainList.size() >= 5)
	{
		if (rowChainList.size() >= 3) 
		{
			// 两方向精灵全部消除  并  产生五消除精灵（魔力鸟）
			removeListSpr(colChainList, true, SUPERBIRD, isChangePro);

			removeListSpr(rowChainList, false, SUPERBIRD, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(SUPERBIRD);
			}
		}
		else
		{
			// 只消除 纵向 精灵 ，产生五消精灵
			removeListSpr(colChainList, true, SUPERBIRD, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(SUPERBIRD);
			}
		}
		return;
	}


	if (rowChainList.size() >= 4) {
		if (colChainList.size() >= 3) {
			// 两方向精灵都消除，产生爆炸精灵
			removeListSpr(rowChainList, true, BOMB, isChangePro);

			removeListSpr(colChainList, false, BOMB, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(BOMB);
				
			}
		}
		else
		{
			// 消除 横向精灵，产生四消精灵
			removeListSpr(rowChainList, true, VERTICAL, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				
				spr->setState(VERTICAL);
				
			}
		}
		return;
	}
	if (colChainList.size() >= 4) {
		if (rowChainList.size() >= 3) {
			// 两方向精灵都消除，产生爆炸精灵
			removeListSpr(colChainList, true, BOMB, isChangePro);

			removeListSpr(rowChainList, false, BOMB, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(BOMB);
			}
		}
		else
		{
			// 消除 纵向精灵，产生四消精灵
			removeListSpr(colChainList, true, HORIZONTAL, isChangePro);

			// 自由掉落产生
			//cuole?
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(HORIZONTAL);

			}
		}
		return;
	}

	if (rowChainList.size() >= 3) {
		if (colChainList.size() >= 3) {
			// 两方向精灵都消除，产生爆炸精灵
			removeListSpr(rowChainList, true, BOMB, isChangePro);

			removeListSpr(colChainList, false, BOMB, isChangePro);

			// 自由掉落产生
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(BOMB);

			}
		}
		else
		{
			// 消除横向精灵
			removeListSpr(rowChainList, false, BOMB, isChangePro);
		}
		return;
	}

	if (colChainList.size() >= 3) {
		if (rowChainList.size() >= 3) {
			removeListSpr(colChainList, true, BOMB, isChangePro);

			removeListSpr(rowChainList, false, BOMB, isChangePro);

			// 自由掉落产生
			if (isChangePro == false) {
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setState(BOMB);

			}
		}
		else
		{
			// 消除纵向精灵
			removeListSpr(colChainList, false, BOMB, isChangePro);
		}
		return;
	}
}

// 移除精灵
void GameScene::removeSprite()
{
	// 做一套移除的动作
	isAction = true;

	for (int r = 0; r < _row; ++r) 
	{
		for (int c = 0; c < _column; ++c) 
		{
			Animals* spr = map[r][c];
			if (!spr) 
			{
				continue;
			}

			if (spr->getIsNeedRemove())
			{
				haveEmpty = true;

				if (spr->getState() == HORIZONTAL)
				{
					explodeSpecialH(spr->getPosition());
				}
				else if (spr->getState() == VERTICAL)
				{
					explodeSpecialV(spr->getPosition());
				}
				else if (spr->getState() == BOMB) 
				{
					explodeSpecialB(spr);
				}
				explodeSprite(spr);
				
			}
		}
	}
}

void GameScene::getRowChain(Animals *spr, std::list<Animals *> &chainList)
{
	// 添加第一个寿司（自己）
	chainList.push_back(spr);

	// 向左查找
	int neighborCol = spr->getColumn() - 1;
	while (neighborCol >= 0)
	{
		Animals *neighborSprite = map[spr->getRow()][neighborCol];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			//&& neighborSprite->getDisplayMode() != DISPLAY_MODE_ANY
			&& !neighborSprite->getIgnoreCheck()) 
		{
			chainList.push_back(neighborSprite);
			neighborCol--;
		}
		else 
		{
			break;
		}
	}

	// 向右查找
	neighborCol = spr->getColumn() + 1;
	while (neighborCol < _column)
	{
		Animals *neighborSprite = map[spr->getRow()][neighborCol];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			//&& neighborSprite->getDisplayMode() != DISPLAY_MODE_ANY
			&& !neighborSprite->getIgnoreCheck())
		{
			chainList.push_back(neighborSprite);
			neighborCol++;
		}
		else 
		{
			break;
		}
	}
}

void GameScene::getColChain(Animals *spr, std::list<Animals *> &chainList)
{
	chainList.push_back(spr);

	int neighborRow = spr->getRow() - 1;
	while (neighborRow >= 0) 
	{
		Animals *neighborSprite = map[neighborRow][spr->getColumn()];

		if (neighborSprite != NULL
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			//&& neighborSprite->getDisplayMode() != DISPLAY_MODE_ANY
			&& neighborSprite->getIgnoreCheck() == false) 
		{

			chainList.push_back(neighborSprite);
			neighborRow--;
		}
		else 
		{
			break;
		}
	}

	neighborRow = spr->getRow() + 1;
	while (neighborRow < _row) 
	{
		Animals *neighborSprite = map[neighborRow][spr->getColumn()];
		if (neighborSprite
			&& (neighborSprite->getImgIndex() == spr->getImgIndex())
			//&& neighborSprite->getDisplayMode() != DISPLAY_MODE_ANY
			&& !neighborSprite->getIgnoreCheck())
		{
			chainList.push_back(neighborSprite);
			neighborRow++;
		}
		else 
		{
			break;
		}
	}
}

void GameScene::explodeSprite(Animals* spr)
{
	/*
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("music/music_explode.ogg", false);
	}
	*/

	float time = 0.2;

	// 精灵的动作
	spr->runAction(Sequence::create(
		ScaleTo::create(time, 0.0),
		CallFuncN::create(CC_CALLBACK_1(GameScene::actionEndCallback, this)),
		NULL));

	// 爆炸效果 圆圈的动作
	auto circleSprite = Sprite::create("circle.png");
	addChild(circleSprite, 10);
	circleSprite->setPosition(spr->getPosition());
	circleSprite->setScale(0);// start size
	circleSprite->runAction(Sequence::create(ScaleTo::create(time, 1.0),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, circleSprite)),
		NULL));


}

void GameScene::explodeSpecialV(Point point)
{
	float scaleX = 4;
	float scaleY = 0.7;
	float time = 0.3;
	Point startPosition = point;
	float speed = 0.6f;

	auto colorSpriteRight = Sprite::create("colorHRight.png");
	addChild(colorSpriteRight, 10);
	Point endPosition1 = Point(point.x - GAME_SCREEN_WIDTH, point.y);
	colorSpriteRight->setPosition(startPosition);
	colorSpriteRight->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition1),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteRight)),
		NULL));

	auto colorSpriteLeft = Sprite::create("colorHLeft.png");
	addChild(colorSpriteLeft, 10);
	Point endPosition2 = Point(point.x + GAME_SCREEN_WIDTH, point.y);
	colorSpriteLeft->setPosition(startPosition);
	colorSpriteLeft->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition2),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteLeft)),
		NULL));


}

void GameScene::explodeSpecialH(Point point)
{
	/*
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("music/music_explodeOne.ogg", false);
	}
	*/
	float scaleY = 4;
	float scaleX = 0.7;
	float time = 0.3;
	Point startPosition = point;
	float speed = 0.6f;

	auto colorSpriteDown = Sprite::create("colorVDown.png");
	addChild(colorSpriteDown, 10);
	Point endPosition1 = Point(point.x, point.y - GAME_SCREEN_HEIGHT);
	colorSpriteDown->setPosition(startPosition);
	colorSpriteDown->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition1),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteDown)),
		NULL));

	auto colorSpriteUp = Sprite::create("colorVUp.png");
	addChild(colorSpriteUp, 10);
	Point endPosition2 = Point(point.x, point.y + GAME_SCREEN_HEIGHT);
	colorSpriteUp->setPosition(startPosition);
	colorSpriteUp->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition2),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteUp)),
		NULL));


}

void GameScene::explodeSpecialB(Animals *spr)
{
	/*
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect("music/music_explodeOne.ogg", false);
	}
	*/
	int dir[12][2] = { 0,-2,-2,0,0,2,2,0,0,-1,-1,-1,-1,0,-1,1,0,1,1,1,1,0,1,-1 };

	Animals *temp;
	int tempX, tempY;
	for (int i = 0; i < 12; i++) {
		tempX = spr->getRow() + dir[i][0];
		tempY = spr->getColumn() + dir[i][1];
		if (tempX >= 0 && tempX < _row && tempY >= 0 && tempY < _column && map[tempX][tempY] != NULL) {
			explodeSprite(map[tempX][tempY]);
		}
	}

}

void GameScene::actionEndCallback(Node *node)
{
	Animals *spr = (Animals *)node;
	map[spr->getRow()][spr->getColumn()] = NULL;
	spr->removeFromParent();
}

// 移除某个容器的所有精灵
void GameScene::removeListSpr(std::list<Animals *> &chainList, bool findSpe, AnimalsState dm, bool &isChangePro)
{
	// 遍历用的迭代器
	std::list<Animals *>::iterator itList;
	Animals *sprite;

	for (itList = chainList.begin(); itList != chainList.end(); ++itList) 
	{
		//cast why
		sprite = (Animals *)* itList;
		if (!sprite)
		{
			continue;
		}

		if (findSpe)
		{
			if (sprite == staSprite || sprite == endSprite) 
			{
				isChangePro = true;
				sprite->setIsNeedRemove(false);
				sprite->setState(dm);

				/*
				// 如果交换消除的带特效
				if (sprite->getState() != COMMON)
				{
					//重复了？
					//markRemove(sprite);
					sprite->setIsNeedRemove(false);
					sprite->setState(dm);
				}
				else
				{
					sprite->setIgnoreCheck(true);
					sprite->setIsNeedRemove(false);
					sprite->setState(dm);
				}
				*/
			}
		}

		markRemove(sprite);
	}

}

void GameScene::markRemove(Animals* spr)
{
	if (spr->getIsNeedRemove())
		return;

	if (spr->getIgnoreCheck()) 
		return;
	

	// 自己本身要消除
	//why?
	spr->setIsNeedRemove(true);
	// 查看所需要消除的精灵是什么类型的

	// 如果是 纵向消除 的精灵
	if (spr->getState() == HORIZONTAL)
	{
		for (int r = 0; r < _row; ++r) 
		{
			Animals* tmp = map[r][spr->getColumn()];
			if (!tmp || tmp == spr) 
				continue;
			

			if (tmp->getState() == COMMON) 
				tmp->setIsNeedRemove(true);
			else 
				markRemove(tmp);
			
		}
	}
	// 如果消除的是 横向消除特效 的精灵

	else if (spr->getState() == VERTICAL)
	{
		for (int c = 0; c < _column; ++c)
		{
			Animals *tmp = map[spr->getRow()][c];
			if (!tmp || tmp == spr) 
				continue;
			

			if (tmp->getState() == COMMON) 
				tmp->setIsNeedRemove(true);
			else 
				markRemove(tmp);
			
		}
	}
	// 消除的是 炸弹特效 的精灵
	else if (spr->getState() == BOMB) 
	{
		int dir[12][2] = { 0,-2,-2,0,0,2,2,0,0,-1,-1,-1,-1,0,-1,1,0,1,1,1,1,0,1,-1 };

		int tempX, tempY;
		for (int i = 0; i < 12; i++) 
		{
			tempX = spr->getRow() + dir[i][0];
			tempY = spr->getColumn() + dir[i][1];
			if (tempX >= 0 && tempX < _row && tempY >= 0 && tempY < _column && map[tempX][tempY]) 
			{

				if (map[tempX][tempY]->getState() == COMMON) 
					map[tempX][tempY]->setIsNeedRemove(true);
				else 
					markRemove(map[tempX][tempY]);
				
			}
		}
	}
	// 消除的是 五消特效 的精灵
	else if (spr->getState() == SUPERBIRD)
	{
		// 如果是交换 执行 五消除

		if (staSprite && endSprite && (staSprite->getState() == COMMON || endSprite->getState() == SUPERBIRD)) 
		{
			if (staSprite->getState() == SUPERBIRD) 
			{
				for (int r = 0; r < _row; r++) 
				{
					for (int c = 0; c < _column; c++) 
					{
						Animals *tmp = map[r][c];
						if (!tmp || tmp == spr) 
							continue;

						if (tmp->getImgIndex() == endSprite->getImgIndex()) 
						{
							if (tmp->getState() == COMMON) 
								tmp->setIsNeedRemove(true);
							else
								markRemove(tmp);
						}
					}
				}
			}
			else
			{
				for (int r = 0; r < _row; r++) 
				{
					for (int c = 0; c < _column; c++) 
					{
						Animals *tmp = map[r][c];
						if (!tmp || tmp == spr) 
							continue;
						if (tmp->getImgIndex() == staSprite->getImgIndex()) 
						{
							if (tmp->getState() == COMMON)
								tmp->setIsNeedRemove(true);
							else 
								markRemove(tmp);
						}
					}
				}
			}

		}
		// 并非交换执行 五消除
		else
		{
			// 随机消除某个
			int _rand = myRand_0_1()*(TOTAL_SP - 1);

			for (int r = 0; r < _row; r++) 
			{
				for (int c = 0; c < _column; c++) 
				{
					Animals *tmp = map[r][c];
					if (!tmp || tmp == spr) 
						continue;

					if (tmp->getImgIndex() == _rand)
					{
						if (tmp->getState() == COMMON) 
							tmp->setIsNeedRemove(true);
						else 
							markRemove(tmp);
					}
				}
			}

		}
	}
}

// 产生 0~1的随机数
float GameScene::myRand_0_1()
{
	timeval psv;
	gettimeofday(&psv, NULL);    // 获取本地时间

	//根据时间产生随机种子
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;
	srand(tsrans);    //设定随机数种子

	return CCRANDOM_0_1();
}

bool GameScene::isHaveMove()
{
	for (int r = 0; r < _row; ++r) {
		for (int c = 0; c < _column; ++c) {
			if (map[r][c]->getImgIndex() == find(r, c - 1, r - 1, c + 1, r + 1, c + 1))
				return true;
			if (map[r][c]->getImgIndex() == find(r, c + 1, r - 1, c - 1, r + 1, c - 1))
				return true;
			if (map[r][c]->getImgIndex() == find(r - 1, c, r + 1, c - 1, r + 1, c + 1))
				return true;
			if (map[r][c]->getImgIndex() == find(r + 1, c, r - 1, c - 1, r - 1, c + 1))
				return true;
		}
	}
	return false;
}

int GameScene::find(int r1, int c1, int r2, int c2, int r3, int c3)
{
	bool isr1, isr2, isr3;
	isr1 = false;
	isr2 = false;
	isr3 = false;

	if (r1 >= 0 && r1 < _row && c1 >= 0 && c1 < _column)	isr1 = true;
	if (r2 >= 0 && r2 < _row && c2 >= 0 && c2 < _column)  isr2 = true;
	if (r3 >= 0 && r3 < _row && c3 >= 0 && c3 < _column)	isr3 = true;

	if (isr1) {
		if (isr2)
			if (map[r1][c1]->getImgIndex() == map[r2][c2]->getImgIndex())
				return map[r1][c1]->getImgIndex();

		if (isr3)
			if (map[r1][c1]->getImgIndex() == map[r3][c3]->getImgIndex())
				return map[r1][c1]->getImgIndex();
	}

	if (isr2 && isr3)
		if (map[r2][c2]->getImgIndex() == map[r3][c3]->getImgIndex())
			return map[r2][c2]->getImgIndex();

	return -1;
}

Animals *GameScene::spriteOfPoint(Point *point)
{
	Animals *spr = NULL;
	Rect rect = Rect(0, 0, SPRITE_WIDTH, SPRITE_WIDTH);
	for (int r = 0; r < _row; ++r) 
	{
		for (int c = 0; c < _column; ++c) 
		{
			spr = map[r][c];
			if (spr) 
			{
				rect.origin.x = spr->getPositionX() - (SPRITE_WIDTH / 2);
				rect.origin.y = spr->getPositionY() - (SPRITE_WIDTH / 2);

				if (rect.containsPoint(*point)) 
				{
					return spr;
				}
			}
		}
	}

	return NULL;
}
/////////////////////////////////////////

bool GameScene::bothUncommon()
{
	return (staSprite->getState() != COMMON && endSprite->getState() != COMMON);
}

bool GameScene::oneSuperBird()
{
	return (staSprite->getState() == SUPERBIRD || endSprite->getState() == SUPERBIRD);
}

bool GameScene::oneBomb()
{
	return (staSprite->getState() == BOMB || endSprite->getState() == BOMB);
}

bool GameScene::bothSameUncommon()
{
	return (staSprite->getState() == endSprite->getState());
}

void GameScene::bothSuperBird()
{
	// 全屏消除
	Animals *spr;
	for (int r = 0; r < _row; r++)
	{
		for (int c = 0; c < _column; c++)
		{
			spr = map[r][c];
			markRemove(spr);
		}
	}
}

void GameScene::BombAndHorizonral(Animals *spr)
{
	int dir[3] = { -1,0,1 };
	Animals *other;

	for (int i = 0; i < 3; i++) 
	{
		if (spr->getRow() + dir[i] >= 0 && spr->getRow() + dir[i] < _row) 
		{
			other = map[spr->getRow() + dir[i]][spr->getColumn()];
			other->setState(HORIZONTAL);

			markRemove(other);
		}
	}
}

void GameScene::BombAndVertical(Animals *spr)
{
	int dir[3] = { -1,0,1 };
	Animals *other;

	for (int i = 0; i < 3; i++)
	{
		if (spr->getColumn() + dir[i] >= 0 && spr->getColumn() + dir[i] < _column)
		{
			other = map[spr->getRow()][spr->getColumn() + dir[i]];
			other->setState(VERTICAL);

			markRemove(other);
		}
	}
}

void GameScene::BomdAndSuperBird(Animals* spr)
{
	Animals *other;
	for (int r = 0; r < _row; r++)
	{
		for (int c = 0; c < _column; c++)
		{
			other = map[r][c];
			if (other->getImgIndex() == spr->getImgIndex())
			{
				other->setState(BOMB);

				markRemove(other);
			}
		}
	}
}

void GameScene::SuperBirdAndBlue(Animals *spr)
{
	Animals *other;
	for (int r = 0; r < _row; r++)
	{
		for (int c = 0; c < _column; c++)
		{
			other = map[r][c];
			if (other->getImgIndex() == spr->getImgIndex())
			{
				// 随机 横消或者竖消
				float _rand = myRand_0_1();
				if (_rand < 0.5)
				{
					other->setState(HORIZONTAL);

				}
				else
				{
					other->setState(VERTICAL);

				}

				markRemove(other);
			}
		}
	}
}

void GameScene::swapSprite()
{
	// 移动中，不允许再次触摸，执行动作设置为true
	isAction = true;
	isTouchEna = false;

	if (!staSprite || !endSprite)
	{
		return;
	}

	Point posOfSrc = staSprite->getPosition();
	Point posOfDest = endSprite->getPosition();

	float time = 0.1;

	// 在数组中交换位置
	map[staSprite->getRow()][staSprite->getColumn()] = endSprite;
	map[endSprite->getRow()][endSprite->getColumn()] = staSprite;

	int tmpRow = staSprite->getRow();
	int tmpCol = staSprite->getColumn();
	staSprite->setRow(endSprite->getRow());
	staSprite->setColumn(endSprite->getColumn());
	endSprite->setRow(tmpRow);
	endSprite->setColumn(tmpCol);


	if (bothUncommon())
	{
		// 如果能够消除，仅仅进行移动（不会移动回来）
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));

		if (bothSameUncommon())
		{
			if (oneSuperBird())
			{
				bothSuperBird();
			}
			else
			{
				markRemove(staSprite);
				markRemove(endSprite);
			}
		}
		if (oneBomb())
		{
			// 找到哪个是炸弹
			if (staSprite->getState() == BOMB)
			{
				// 查看另一个特效
				// 横向消除特效
				if (endSprite->getState() == HORIZONTAL)
					BombAndHorizonral(endSprite);
				if (endSprite->getState() == VERTICAL)
					BombAndVertical(endSprite);
				if (endSprite->getState() == SUPERBIRD)
					BomdAndSuperBird(endSprite);
			}
			else
			{
				// 查看另一个特效
				// 横向消除特效
				if (staSprite->getState() == HORIZONTAL)
					BombAndHorizonral(staSprite);
				if (staSprite->getState() == VERTICAL)
					BombAndVertical(staSprite);
				if (staSprite->getState() == SUPERBIRD)
					BomdAndSuperBird(staSprite);
			}
		}
		markRemove(staSprite);
		markRemove(endSprite);
		removeSprite();

		return;

	}

	if (oneSuperBird())
	{
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));
		if (staSprite->getState() == SUPERBIRD)
		{
			if (endSprite->getState() == COMMON)
			{
				markRemove(staSprite);
				markRemove(endSprite);
			}
			else
				SuperBirdAndBlue(endSprite);
		}
		else
		{
			if (staSprite->getState() == COMMON)
			{
				markRemove(staSprite);
				markRemove(endSprite);
			}
			else
				SuperBirdAndBlue(staSprite);
		}
		removeSprite();

		return;

	}

	// 检查是否能消除
	std::list<Animals *> colChainListOfFirst;
	getColChain(staSprite, colChainListOfFirst);

	std::list<Animals *> rowChainListOfFirst;
	getRowChain(staSprite, rowChainListOfFirst);

	std::list<Animals *> colChainListOfSecond;
	getColChain(endSprite, colChainListOfSecond);

	std::list<Animals *> rowChainListOfSecond;
	getRowChain(endSprite, rowChainListOfSecond);

	if (colChainListOfFirst.size() >= 3
		|| rowChainListOfFirst.size() >= 3
		|| colChainListOfSecond.size() >= 3
		|| rowChainListOfSecond.size() >= 3
		//why 
		//|| staSprite->getState() == SUPERBIRD
		//|| endSprite->getState() == SUPERBIRD
		) 
	{
		// 如果能够消除，仅仅进行移动（不会移动回来）
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));
		return;
	}

	// 不能消除，则移动过去还要返回
	map[staSprite->getRow()][staSprite->getColumn()] = endSprite;
	map[endSprite->getRow()][endSprite->getColumn()] = staSprite;

	tmpRow = staSprite->getRow();
	tmpCol = staSprite->getColumn();
	staSprite->setRow(endSprite->getRow());
	staSprite->setColumn(endSprite->getColumn());
	endSprite->setRow(tmpRow);
	endSprite->setColumn(tmpCol);

	staSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfDest),
		MoveTo::create(time, posOfSrc),
		NULL));
	endSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfSrc),
		MoveTo::create(time, posOfDest),
		NULL));
}

void GameScene::addSelected()
{
	_selected = Sprite::create("PlayGame/selected.png");
	if (_selected == nullptr)
	{
		problemLoading("'selected.jpg'");
	}
	else
	{
		_selected->setPosition(Vec2(staSprite->getPositionX(), staSprite->getPositionY()));
		this->addChild(_selected, 1);
		//staSprite->setSelected();
	}

}

void GameScene::removeSelected()
{
	//staSprite->removeSelected();
	log("remove!!!");
	this->removeChild(_selected);
}/////////////////////////

bool GameScene::onTouchBegan(Touch *touch, Event *unused)
{
	if (isTouchEna)
	{
		log("touch began");
		auto location = touch->getLocation();
		locList.push_back(location);
		getSprite();
	}
	return isTouchEna;
}

void GameScene::getSprite()
{
	if (locList.size() == 1)
	{
		staSprite = spriteOfPoint(&locList[0]);
		if(staSprite)
			addSelected();
		log("get startSprite and add");
		return;
	}
	if (locList.size() == 2)
	{
		staSprite = spriteOfPoint(&locList[0]);
		endSprite = spriteOfPoint(&locList[1]);
		log("get endSprite and add");
		if (canSwap())
		{
			removeSelected();
			log("Can swap");
			swapSprite();

			staSprite = NULL;
			endSprite = NULL;
			locList.erase(locList.begin(), locList.begin() + 2);
			log("swaped: %d", locList.size());
		}
		else
		{
			removeSelected();
			log("can not swap");
			staSprite = endSprite;
			endSprite = NULL;
			addSelected();
			log("end=sta");
			log("end=sta: %d", locList.size());
			locList.assign(2, locList[1]);
			locList.pop_back();
			log("ended: %d", locList.size());

		}
		return;
	}
}

//unused 
bool GameScene::canSwap()
{
	//先判断sta和end是否都在
	int staRow = staSprite->getRow();
	int staCol = staSprite->getColumn();
	int endRow = endSprite->getRow();
	int endCol = endSprite->getColumn();

	int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };

	for (int i = 0; i < 4; i++)
	{
		if (endRow == staRow + dir[i][0] && endCol == staCol + dir[i][1])
		{
			return true;
		}
	}
	return false;
}

// 更新函数
void GameScene::update(float t)
{
	// 检测是否在执行动作
	if (isAction) 
	{
		// 设置为false
		isAction = false;
		for (int r = 0; r < _row; ++r)
		{
			for (int c = 0; c < _column; ++c)
			{
				Animals* spr = map[r][c];
				if (spr) 
				{
					if (spr->getState() == COMMON && spr->getNumberOfRunningActions() > 0)
					{
						isAction = true;
						break;
					}	
				}
			}
			if (isAction)
				break;
		}
	}

	// 如果寿司正在移动中，忽视触摸事件
	isTouchEna = !isAction;

	if (!isAction)
	{
		if (haveEmpty)
		{
			staSprite = NULL;
			endSprite = NULL;

			//爆炸效果结束后才掉落新寿司，增强打击感
			fillSprite();
			haveEmpty = false;

		}
		else 
		{	
			checkAndRemoveSprite();
		}
	}

	// 分数变化
	Label *labelScore = (Label *)this->getChildByTag(10);
	labelScore->setString(StringUtils::format("Score: %d ", this->getScore()));

}
