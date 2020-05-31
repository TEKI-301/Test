#pragma once
#ifndef _POSITION_MAP_H__
#define _POSITION_MAP_H__

#include<vector>
#include"cocos2d.h"

USING_NS_CC;
using namespace std;

class PositionMap
{
private:
	int _row;
	int _column;
	vector<Point>_AniPos;
	
public:
	PositionMap() {}
	PositionMap(int level);
	Point getPos(int x, int y);
	int getRow();
	int getColumn();
};

#endif // !_POSITION_MAP_H__
