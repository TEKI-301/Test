#include"AnimalsSprite.h"
#include"GameScene.h"


Animals::Animals()
	:_row(0), _column(0), _imgIndex(0),
	_isNeedRemove(false), 
	_ignoreCheck(false),
	_state(COMMON)
{
}

Animals *Animals::create(int row, int column)
{
	Animals *spr = new(std::nothrow) Animals;
	if (spr&&spr->init(row, column))
	{
		spr->autorelease();
		return spr;
	}
	CC_SAFE_DELETE(spr);
	return nullptr;
	
	/*
	spr->_row = row;
	spr->_column = column;
	spr->_imgIndex = rand() % TOTAL_SP;
	spr->initWithSpriteFrameName(Common[spr->_imgIndex]);
	spr->autorelease();
	return spr;
	*/
}

bool Animals::init(int row, int column)
{
	if (!Sprite::init())
	{
		return false;
	}
	_row = row;
	_column = column;
	_imgIndex = rand() % TOTAL_SP;
	initWithSpriteFrameName(Common[_imgIndex]);
	return true;

}


void Animals::setSelected()
{
	if (_state == COMMON)
	{
		SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
		switch (_imgIndex)
		{
		case 0:
		{
			pCache->addSpriteFramesWithFile("Animals\\CatCommon.plist", "Animals\\CatCommon.png");
			Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(4);
			for (int i = 1; i <= 4; ++i)
			{
				SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("CatCommon_%d.png", i));
				sfme.pushBack(fname);
			}
			Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
			Animate* animate = Animate::create(animation);
			runAction(RepeatForever::create(animate));
			break;
		}
		case 1:
		{
			pCache->addSpriteFramesWithFile("Animals\\ChookCommon.plist", "Animals\\ChookCommon.png");
			Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(5);
			for (int i = 1; i <= 5; ++i)
			{
				SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("ChookCommon_%d.png", i));
				sfme.pushBack(fname);
			}
			Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
			Animate* animate = Animate::create(animation);
			runAction(RepeatForever::create(animate));
			break;
		}
		case 2:
		{
			pCache->addSpriteFramesWithFile("Animals\\FoxCommon.plist", "Animals\\FoxCommon.png");
			Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(7);
			for (int i = 1; i <= 7; ++i)
			{
				SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FoxCommon_%d.png", i));
				sfme.pushBack(fname);
			}
			Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
			Animate* animate = Animate::create(animation);
			runAction(RepeatForever::create(animate));
			break;
		}
		case 3:
		{
			pCache->addSpriteFramesWithFile("Animals\\FrogCommon.plist", "Animals\\FrogCommon.png");
			Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);
			for (int i = 1; i <= 3; ++i)
			{
				SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FrogCommon_%d.png", i));
				sfme.pushBack(fname);
			}
			Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
			Animate* animate = Animate::create(animation);
			runAction(RepeatForever::create(animate));
			break;

		}
		case 4:
		{
			pCache->addSpriteFramesWithFile("Animals\\HippoCommon.plist", "Animals\\HippoCommon.png");
			Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(4);
			for (int i = 1; i <= 4; ++i)
			{
				SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("HippoCommon_%d.png", i));
				sfme.pushBack(fname);
			}
			Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
			Animate* animate = Animate::create(animation);
			runAction(RepeatForever::create(animate));
			break;
		}
		default:
			break;
		}
	}

}

void Animals::removeSelected()
{
	if (_state = COMMON)
	{
		stopAllActions();
	}
}

void Animals::setState(AnimalsState state)
{
	_state = state;
	
	switch (state)
	{
	case VERTICAL:
		this->setVertical();
		break;
	case HORIZONTAL:
		setHorizontal();
		break;
	case BOMB:
		setBomb();
		break;
	case SUPERBIRD:
		setSuperBird();
		break;
	default:
		break;
	}
	return;
}

void Animals::setVertical()
{

	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	switch (_imgIndex)
	{
	case 0:
	{
		pCache->addSpriteFramesWithFile("Animals/CatVertical.plist", "Animals/CatVertical.png");
		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("CatVertical_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
		break;
	}
	case 1:
	{
		pCache->addSpriteFramesWithFile("Animals\\ChookVertical.plist", "Animals\\ChookVertical.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("ChookVertical_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 2:
	{
		pCache->addSpriteFramesWithFile("Animals\\FoxVertical.plist", "Animals\\FoxVertical.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FoxVertical_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 3:
	{
		pCache->addSpriteFramesWithFile("Animals\\FrogVertical.plist", "Animals\\FrogVertical.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FrogVertical_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 4:
	{
		pCache->addSpriteFramesWithFile("Animals\\HippoVertical.plist", "Animals\\HippoVertical.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(2);

		for (int i = 1; i <= 2; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("HippoVertical_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	default:
		break;
	}
}

void Animals::setHorizontal()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	switch (_imgIndex)
	{
	case 0:
	{
		pCache->addSpriteFramesWithFile("Animals\\CatHorizontal.plist", "Animals\\CatHorizontal.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("CatHorizontal_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));

	}
	break;
	case 1:
	{
		pCache->addSpriteFramesWithFile("Animals\\ChookHorizontal.plist", "Animals\\ChookHorizontal.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("ChookHorizontal_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 2:
	{
		pCache->addSpriteFramesWithFile("Animals\\FoxHorizontal.plist", "Animals\\FoxHorizontal.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FoxHorizontal_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 3:
	{
		pCache->addSpriteFramesWithFile("Animals\\FrogHorizontal.plist", "Animals\\FrogHorizontal.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FrogHorizontal_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 4:
	{
		pCache->addSpriteFramesWithFile("Animals\\HippoHorizontal.plist", "Animals\\HippoHorizontal.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(2);

		for (int i = 1; i <= 2; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("HippoHorizontal_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	default:
		break;
	}
}

void Animals::setBomb()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	switch (_imgIndex)
	{
	case 0:
	{
		pCache->addSpriteFramesWithFile("Animals\\CatBomb.plist", "Animals\\CatBomb.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(6);

		for (int i = 1; i <= 6; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("CatBomb_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));

	}
	break;
	case 1:
	{
		pCache->addSpriteFramesWithFile("Animals\\ChookBomb.plist", "Animals\\ChookBomb.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(5);

		for (int i = 1; i <= 5; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("ChookBomb_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 2:
	{
		pCache->addSpriteFramesWithFile("Animals\\FoxBomb.plist", "Animals\\FoxBomb.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(5);

		for (int i = 1; i <= 5; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FoxBomb_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 3:
	{
		pCache->addSpriteFramesWithFile("Animals\\FrogBomb.plist", "Animals\\FrogBomb.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(2);

		for (int i = 1; i <= 2; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("FrogBomb_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	case 4:
	{
		pCache->addSpriteFramesWithFile("Animals\\HippoBomb.plist", "Animals\\HippoBomb.png");

		Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >(3);

		for (int i = 1; i <= 3; ++i)
		{
			SpriteFrame* fname = pCache->spriteFrameByName(StringUtils::format("HippoBomb_%d.png", i));
			sfme.pushBack(fname);
		}
		Animation *animation = Animation::createWithSpriteFrames(sfme, 0.2f);
		Animate* animate = Animate::create(animation);

		runAction(RepeatForever::create(animate));
	}
	break;
	default:
		
		break;
	}

}

void Animals::setSuperBird()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("Animals\\SuperBird.plist", "Animals\\SuperBird.png");
	SpriteFrame *frame;
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("SuperBird_1.png");

	setDisplayFrame(frame);

}