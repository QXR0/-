#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x1) ? 1 : 0 )
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>


//蛇身体
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode,* pSnakeNode;


//游戏进行的状态
typedef enum STATE
{
	RUN,
	END,
	BY_MYSELF_KILL,
	BY_WALL_KILL
}STATE;

//蛇运动方向
typedef enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}DIRECTION;

typedef struct Food
{
	int x;
	int y;
}Food,*pFood;

//蛇
typedef struct Snake
{
	pSnakeNode psnakehead;
	STATE state;
	DIRECTION direction;
	int score;
	int foodweight;
	pFood pfood;
	int sleeptime;
}Snake,*pSnake;

//设置光标位置
void SetPos(int x, int y);

//游戏开始
void GameStart(pSnake psnake);

//欢迎界面
void WelcomeGame();

//功能介绍
void IntroduceFunction();

//绘制地图
void MakeMap();

//初始化蛇
void InitSnake(pSnake psnake);

//创建食物
void CreatFood(pSnake psnake);

//游戏运行
void GameRun(pSnake psnake);

//蛇的运动
void SnakeMove(psnake);

//创建新节点
void CreatNewNode(pSnake psnake,int x, int y);

//游戏结束
void GameEnd(pSnake psnake);