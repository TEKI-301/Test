#pragma once
#ifndef _ANIMALS_H__
#define _ANIMALS_H__

#include"cocos2d.h"
#include"GameDefine.h"

USING_NS_CC;

class Animals :public cocos2d::Sprite
{
public:
	Animals();
	static Animals* create(int row, int column);

};
#endif // !_ANIMALS_H__
