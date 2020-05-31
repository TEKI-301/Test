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

	// ��ͼ�����½�����λ��
	float mapLBX, mapLBY;
	// ����һ��ͼƬ
	SpriteBatchNode *spriteSheet;
	PositionMap PosMap;
	void getPositionMap(int level);
	int _row;
	int _column;
	// ��ά����
	Animals* map[10][10];
	// �ж��Ƿ���ִ�ж���
	bool isAction;
	// �����¼��Ƿ����ִ��
	bool isTouchEna;
	//�Ƿ��п�ȱ��Ҫ�
	bool haveEmpty;
	// Դ���飬Ŀ�꾫��
	Animals* staSprite;
	Animals* endSprite;
	vector<Vec2>locList;


	//void drop(int row, int column);
	Sprite* _selected;
	void addSelected();
	void removeSelected();
	//�ж��ܷ񽻻�
	bool canSwap();
	//�õ�����
	void getSprite();

	// ��������
	void createSprite(int row, int col);
	//�õ���Ӧ���о��������ֵ
	Point positionOfItem(int row, int col);
	// ��ʼ����ά����
	void initMap();
	// ���ȱλ��
	void fillSprite();

	
	// ��鲢��������
	void checkAndRemoveSprite();
	
	// ���� �� ������Ч����
	void removeAndPro(Animals *spr);

	// ��������
	void removeSprite();

	// ���Chain
	void getColChain(Animals *spr, std::list<Animals *> &chainList);
	void getRowChain(Animals *spr, std::list<Animals *> &chainList);

	// ��ը
	void explodeSprite(Animals* spr);
	void explodeSpecialH(Point point);
	void explodeSpecialV(Point point);
	void explodeSpecialB(Animals* spr);
	//
	void actionEndCallback(Node *node);
	// 
	void markRemove(Animals* spr);
	// �����
	// ���� 0~1�������
	float myRand_0_1();
	// ����Ƿ��п��ƶ��ľ���
	bool isHaveMove();
	int find(int r1, int c1, int r2, int c2, int r3, int c3);

	// �Ƴ�ĳ�����������о���
	void removeListSpr(std::list<Animals *> &chainList, bool findSpe, AnimalsState dm, bool &isChangePro);
	// ��ȡ����λ��
	Animals *spriteOfPoint(Point *point);
	// ��������
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
