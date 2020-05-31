#pragma once
#ifndef __SETVOLUME_SCENE_H__
#define __SETVOLUME_SCENE_H__


#include"cocos2d.h"

class SetVolume : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuStartCallBack(cocos2d::Ref* pSender);
	//void menuCloseCallBack(cocos2d::Ref* pSender);
	void menuReturnCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually

	CREATE_FUNC(SetVolume);
};

#endif 