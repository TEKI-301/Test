#pragma once
#ifndef __SELECTLEVEL_SCENE_H__
#define __SELECTLEVEL_SCENE_H__

#include"cocos2d.h"

class SelectLevel :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuReturnCallBack(cocos2d::Ref* pSender);
	void menuLevelCallBack_1(cocos2d::Ref* pSender);
	void menuLevelCallBack_2(cocos2d::Ref* pSender);
	void menuLevelCallBack_3(cocos2d::Ref* pSender);

	CREATE_FUNC(SelectLevel);
};

#endif 
