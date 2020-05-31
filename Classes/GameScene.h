#pragma once
#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include"cocos2d.h"
#include"GameDefine.h"
#include"PositionMap.h"
//#include<vector>
USING_NS_CC;

class Animals;
class PositionMap;

class GameScene :public Scene
{
public:
	static cocos2d::Scene* createScene();

	GameScene();



	virtual bool init();
	bool onTouchBegan(Touch *touch, Event *unused);

	void update(float dt);
	//void gameOver(float dt);

	void menuReturnCallBack(cocos2d::Ref* pSender);
	CC_SYNTHESIZE(int, _score, Score);

	CREATE_FUNC(GameScene);
private:

	// 绘图的最下角坐标位置
	float mapLBX, mapLBY;
	// 绘制一批图片
	SpriteBatchNode *spriteSheet;
	PositionMap PosMap;
	void getPositionMap(int level);
	int _row;
	int _column;
	// 二维数组
	Animals* map[10][10];
	// 判断是否在执行动作
	bool isAction;
	// 触摸事件是否可以执行
	bool isTouchEna;
	//是否有空缺需要填补
	bool haveEmpty;
	// 源精灵，目标精灵
	Animals* staSprite;
	Animals* endSprite;
	vector<Vec2>locList;


	//void drop(int row, int column);
	Sprite* _selected;
	void addSelected();
	void removeSelected();
	//判断能否交换
	bool canSwap();
	//得到精灵
	void getSprite();

	// 创建精灵
	void createSprite(int row, int col);
	//得到对应行列精灵的坐标值
	Point positionOfItem(int row, int col);
	// 初始化二维数组
	void initMap();
	// 填补空缺位置
	void fillSprite();

	
	// 检查并消除精灵
	void checkAndRemoveSprite();
	
	// 消除 并 生成特效精灵
	void removeAndPro(Animals *spr);

	// 消除精灵
	void removeSprite();

	// 检查Chain
	void getColChain(Animals *spr, std::list<Animals *> &chainList);
	void getRowChain(Animals *spr, std::list<Animals *> &chainList);

	// 爆炸
	void explodeSprite(Animals* spr);
	void explodeSpecialH(Point point);
	void explodeSpecialV(Point point);
	void explodeSpecialB(Animals* spr);
	//
	void actionEndCallback(Node *node);
	// 
	void markRemove(Animals* spr);
	// 随机数
	// 产生 0~1的随机数
	float myRand_0_1();
	// 检测是否有可移动的精灵
	bool isHaveMove();
	int find(int r1, int c1, int r2, int c2, int r3, int c3);

	// 移除某个容器的所有精灵
	void removeListSpr(std::list<Animals *> &chainList, bool findSpe, AnimalsState dm, bool &isChangePro);
	// 获取精灵位置
	Animals *spriteOfPoint(Point *point);
	// 交换精灵
	void swapSprite();



	bool bothUncommon();
	bool oneSuperBird();
	bool oneBomb();
	bool bothSameUncommon();
	void bothSuperBird();
	void BombAndHorizonral(Animals *spr);
	void BombAndVertical(Animals *spr);
	void BomdAndSuperBird(Animals *spr);
	void SuperBirdAndBlue(Animals *spr);
};


#endif // !_GAME_SCENE_H__
