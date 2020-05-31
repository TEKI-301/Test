#include"PositionMap.h"
#include"GameDefine.h"
PositionMap::PositionMap(int level)
{
	switch (level)
	{
	case 1:
		_row = 8;
		_column = 8;
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _column; j++)
			{
				int x = 90 * i - 315 + GAME_SCREEN_WIDTH / 2;
				int y = 90 * j - 315 + GAME_SCREEN_HEIGHT / 2;
				Point temp = Point(x, y);
				//Anipos[k]  k=i*_row+j
				_AniPos.push_back(temp);
			}
		}
		break;
	default:
		break;
	}
}

Point PositionMap::getPos(int x, int y)
{
	return _AniPos[x*_row + y];
}

int PositionMap::getRow()
{
	return _row;
}

int PositionMap::getColumn()
{
	return _column;
}
