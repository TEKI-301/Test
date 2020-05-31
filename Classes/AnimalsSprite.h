#pragma once
#ifndef _ANIMALS_SPRITE_H__
#define _ANIMALS_SPRITE_H__

#include"cocos2d.h"
#include"GameDefine.h"

USING_NS_CC;

class Animals :public Sprite
{
public:
	Animals();
	static Animals* create(int row, int column);

	bool init(int row, int column);
	CC_SYNTHESIZE(int, _row, Row);
	CC_SYNTHESIZE(int, _column, Column);
	CC_SYNTHESIZE(int, _imgIndex, ImgIndex);
	CC_SYNTHESIZE(bool, _isNeedRemove, IsNeedRemove);
	CC_SYNTHESIZE(bool, _ignoreCheck, IgnoreCheck);
	CC_SYNTHESIZE_READONLY(AnimalsState, _state, State);

	void setSelected();
	void removeSelected();


	void setState(AnimalsState state);
	void setVertical();
	void setHorizontal();
	void setBomb();
	void setSuperBird();
};
#endif // !_ANIMALS_SPRITE_H__
