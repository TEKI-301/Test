#pragma once
#ifndef _GAMEDEFINE_H__
#define _GAMEDEFNIE_H__

// ������Ļ���
#define GAME_SCREEN_WIDTH 1280
#define GAME_SCREEN_HEIGHT 800

// ����ÿ�������С
#define SPRITE_WIDTH 90

// С���ﾫ���������
#define TOTAL_SP 5

// ������Ч
#include "SimpleAudioEngine.h"
#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"

// �����洢
#define userDefault CCUserDefault::sharedUserDefault()

// �����״̬��Horizontal��ʾ��������һ�У�Vertical��ʾ��������һ��
enum AnimalsState 
{
	COMMON = 0,
	HORIZONTAL,
	VERTICAL,
	BOMB,
	SUPERBIRD
};


// ��ȡ���� ��ͨ
static const char *Common[TOTAL_SP] = 
{
	"Cat.png",
	"Chook.png",
	"Fox.png",
	"Frog.png",
	"Hippo.png"
};

static const char *CommonPlist[TOTAL_SP] = 
{
	"Animals\\CatCommon.plist",
	"Animals\\ChookCommon.plist",
	"Animals\\FoxCommon.plist",
	"Animals\\FrogCommon.plist",
	"Animals\\HippoCommon.plist",
};

static const char *CommonPng[TOTAL_SP] = 
{
	"Animals\\CatCommon.png",
	"Animals\\ChookCommon.png",
	"Animals\\FoxCommon.png",
	"Animals\\FrogCommon.png",
	"Animals\\HippoCommon.png",
};

static const char *CommonFirstPng[TOTAL_SP] = 
{
	"CatCommon_1.png",
	"ChookCommon_1.png",
	"FoxCommon_1.png",
	"FrogCommon_1.png",
	"HippoCommon_1.png",
};

// ��ֱ
static const char *VerticalPlist[TOTAL_SP] = 
{
	"Animals\\CatVertical.plist",
	"Animals\\ChookVertical.plist",
	"Animals\\FoxVertical.plist",
	"Animals\\FrogVertical.plist",
	"Animals\\HippoVertical.plist",
};

static const char *VerticalPng[TOTAL_SP] =
{
	"Animals\\CatVertical.png",
	"Animals\\ChookVertical.png",
	"Animals\\FoxVertical.png",
	"Animals\\FrogVertical.png",
	"Animals\\HippoVertical.png",
};

static const char *VerticalFirstPng[TOTAL_SP] =
{
	"CatVertical_1.png",
	"ChookVertical_1.png",
	"FoxVertical_1.png",
	"FrogVertical_1.png",
	"HippoVertical_1.png",
};

// ˮƽ
static const char *HorizontalPlist[TOTAL_SP] = 
{
	"Animals/CatHorizontal.plist",
	"Animals/ChookHorizontal.plist",
	"Animals/FoxHorizontal.plist",
	"Animals/FrogHorizontal.plist",
	"Animals/HippoHorizontal.plist"
};

static const char *HorizontalPng[TOTAL_SP] =
{
	"Animals/CatHorizontal.png",
	"Animals/ChookHorizontal.png",
	"Animals/FoxHorizontal.png",
	"Animals/FrogHorizontal.png",
	"Animals/HippoHorizontal.png"
};

static const char *HorizontalFirstPng[TOTAL_SP] = 
{
	"CatHorizontal_1.png",
	"ChookHorizontal_1.png",
	"FoxHorizontal_1.png",
	"FrogHorizontal_1.png",
	"HippoHorizontal_1.png"
};

// ��ը
static const char *BombPlist[TOTAL_SP] = 
{
	"Animals/CatBomb.plist",
	"Animals/ChookBomb.plist",
	"Animals/FoxBomb.plist",
	"Animals/FrogBomb.plist",
	"Animals/HippoBomb.plist"
};

static const char *BombPng[TOTAL_SP] =
{
	"Animals/CatBomb.png",
	"Animals/ChookBomb.png",
	"Animals/FoxBomb.png",
	"Animals/FrogBomb.png",
	"Animals/HippoBomb.png"
};

static const char *BombFirstPng[TOTAL_SP] = 
{
	"CatBomb_1.png",
	"ChookBomb_1.png",
	"FoxBomb_1.png",
	"FrogBomb_1.png",
	"HippoBomb_1.png"
};


// ����  ħ����
static const char *superBird = "Animals/Bird.png";



#endif // 
