#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x1) ? 1 : 0 )
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>


//������
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode,* pSnakeNode;


//��Ϸ���е�״̬
typedef enum STATE
{
	RUN,
	END,
	BY_MYSELF_KILL,
	BY_WALL_KILL
}STATE;

//���˶�����
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

//��
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

//���ù��λ��
void SetPos(int x, int y);

//��Ϸ��ʼ
void GameStart(pSnake psnake);

//��ӭ����
void WelcomeGame();

//���ܽ���
void IntroduceFunction();

//���Ƶ�ͼ
void MakeMap();

//��ʼ����
void InitSnake(pSnake psnake);

//����ʳ��
void CreatFood(pSnake psnake);

//��Ϸ����
void GameRun(pSnake psnake);

//�ߵ��˶�
void SnakeMove(psnake);

//�����½ڵ�
void CreatNewNode(pSnake psnake,int x, int y);

//��Ϸ����
void GameEnd(pSnake psnake);