#include"snake.h"

//设置光标位置
void SetPos(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOutput = NULL;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//欢迎界面
void WelcomeGame()
{
	SetPos(50, 11);
	printf("欢迎来到贪吃蛇！！");
	SetPos(50, 12);
	printf("贪吃蛇是一款...后面忘了");
	SetPos(50, 15);

	system("pause");
	system("cls");
}

//功能介绍
void IntroduceFunction()
{
	SetPos(50, 11);
	printf("方向键：↑↓←→ 加速键：F1 减速键：F2");
	SetPos(50, 12);
	printf("退出：Esc 暂停：Space");
	SetPos(50, 16);
	system("pause");
	system("cls");
}

//绘制地图
void MakeMap()
{
	
	//上
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i < 70; i+=2)
	{
		printf("□");
	}
	//下
	SetPos(0, 30);
	for (i = 0; i <= 70; i += 2)
	{
		printf("□");
	}
	//左
	for (i = 0; i < 30; i++)
	{
		SetPos(0, i);
		printf("□");
	}
	//右
	for (i = 0; i < 30; i++)
	{
		SetPos(70, i);
		printf("□");
	}

	//右侧帮助信息
	SetPos(80, 14);
	printf("方向键：↑↓←→ 加速键：a 减速键：s");
	SetPos(80, 15);
	printf("退出：Esc 暂停：Space");
	
}

//初始化蛇
void InitSnake(pSnake psnake)
{
	psnake->sleeptime = 200;
	psnake->direction = RIGHT;
	psnake->foodweight = 10;
	psnake->pfood = NULL;
	CreatFood(psnake);
	psnake->score = 0;
	psnake->state = RUN;
	//初始化蛇头
	psnake->psnakehead = (SnakeNode*)malloc(sizeof(SnakeNode));
	psnake->psnakehead->x = 60;
	psnake->psnakehead->y = 14;
	//初始化蛇身
	int i = 0;
	SnakeNode* pur = psnake->psnakehead;
	for (i = 0; i < 4; i++)
	{
		pur->next= (SnakeNode*)malloc(sizeof(SnakeNode));
		pur->next->x = pur->x - 2;
		pur->next->y = pur->y;
		pur = pur->next;
	}
	pur->next = NULL;

}

   
//创建食物
void CreatFood(pSnake psnake)
{
	psnake->pfood = (pFood*)malloc(sizeof(pFood));
	while ((psnake->pfood->x = rand() % 70 + 2) % 2 == 1);
	psnake->pfood->y = rand() % 29 + 1;
	SetPos(psnake->pfood->x, psnake->pfood->y);
	printf("★");
}




//游戏开始
void GameStart(pSnake psnake)
{
	//设置窗口大小
	system("mode con cols=120 lines=35");

	//设置标题
	system("title 贪吃蛇");

	//隐藏光标
	HANDLE hOutput = NULL;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);

	
	//欢迎界面
	WelcomeGame();

	//功能介绍
	IntroduceFunction();

	//绘制地图
	MakeMap();

	//初始化蛇
	InitSnake(psnake);
	
}

//打印分数
void PrintScore(pSnake psnake)
{
	SetPos(80, 17);
	printf("分数：%d", psnake->score);
}


//创建新头节点
void CreatNewNode(pSnake psnake, int x, int y)
{
	pSnakeNode phead = (pSnakeNode)malloc(sizeof(SnakeNode));
	phead->x = x;
	phead->y = y;
	phead->next = psnake->psnakehead;
	psnake->psnakehead = phead;
}


//蛇的运动
void SnakeMove(pSnake psnake)
{
	switch (psnake->direction)
	{
		
	case UP:  
		CreatNewNode(psnake, psnake->psnakehead->x, psnake->psnakehead->y - 1);
		pSnakeNode pur = psnake->psnakehead;
		if (psnake->psnakehead->x == psnake->pfood->x && psnake->psnakehead->y - 1 == psnake->pfood->y)
		{
			//吃食物

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
			
		}
		else
		{
			//不吃食物
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("●");
			SetPos(pur->next->x, pur->next->y);

			printf("  ");
			free(pur->next);
			pur->next = NULL;

		}
		break;
	case DOWN:
		CreatNewNode(psnake, psnake->psnakehead->x, psnake->psnakehead->y +1);
		pur = psnake->psnakehead;

		if (psnake->psnakehead->x == psnake->pfood->x && psnake->psnakehead->y +1 == psnake->pfood->y)
		{
			//吃食物

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
		}
		else
		{
			//不吃食物
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("●");
			SetPos(pur->next->x, pur->next->y);

			printf("  ");
			free(pur->next);
			pur->next = NULL;

		}
		break;
	case LEFT:
		CreatNewNode(psnake, psnake->psnakehead->x-2, psnake->psnakehead->y );
		pur = psnake->psnakehead;

		if (psnake->psnakehead->x-2 == psnake->pfood->x && psnake->psnakehead->y  == psnake->pfood->y)
		{
			//吃食物

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
		}
		else
		{
			//不吃食物
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("●");
			SetPos(pur->next->x, pur->next->y);

			printf("  ");
			free(pur->next);
			pur->next = NULL;

		}
		break;
	case RIGHT:
		CreatNewNode(psnake, psnake->psnakehead->x+2, psnake->psnakehead->y );
		pur = psnake->psnakehead;

		if (psnake->psnakehead->x + 2 == psnake->pfood->x && psnake->psnakehead->y  == psnake->pfood->y)
		{
			//吃食物

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
		}
		else
		{
			//不吃食物
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("●");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("●");
			SetPos(pur->next->x, pur->next->y);

			printf("  ");
			free(pur->next);
			pur->next = NULL;

		}
		break;
	}
}


//游戏运行
void GameRun(pSnake psnake)
{
	do
	{
		PrintScore(psnake);
		if (KEY_PRESS(VK_UP) && psnake->direction != DOWN)
		{
			psnake->direction = UP;
		}
		else if (KEY_PRESS(VK_DOWN) && psnake->direction != UP)
		{
			psnake->direction = DOWN;
		}
		else if (KEY_PRESS(VK_LEFT) && psnake->direction != RIGHT)
		{
			psnake->direction = LEFT;
		}
		else if (KEY_PRESS(VK_RIGHT) && psnake->direction != LEFT)
		{
			psnake->direction = RIGHT;
		}
		else if (KEY_PRESS(VK_SPACE))
		{
			while (1)
			{
				if (KEY_PRESS(VK_SPACE))
					break;
			}
		}
		else if (KEY_PRESS(VK_ESCAPE))
		{
			psnake->state = END;
		}
		else if (KEY_PRESS(VK_F1))
		{
			//没限速
			psnake->sleeptime -= 100;
		}
		else if (KEY_PRESS(VK_F2))
		{
			//没限速
			psnake->sleeptime += 100;
		}
		Sleep(psnake->sleeptime);
		SnakeMove(psnake);
		if (psnake->psnakehead->x < 2 || psnake->psnakehead->x>70 || psnake->psnakehead->y < 1 || psnake->psnakehead->y>30)
		{
			psnake->state = BY_WALL_KILL;
		}
		pSnakeNode pur = psnake->psnakehead->next;
		while (pur)
		{			
			if (psnake->psnakehead->x == pur->x&& psnake->psnakehead->y == pur->y)
			{
				psnake->state = BY_MYSELF_KILL;
				break;
			}
			pur = pur->next;
		}

	} while (psnake->state==RUN);
	
}



//游戏结束
void GameEnd(pSnake psnake)
{
	if (psnake->state == BY_MYSELF_KILL)
	{
		SetPos(50, 20);
		printf("撞到自己了！！！游戏结束...");
		SetPos(100, 100);

	}
	if (psnake->state == BY_WALL_KILL)
	{
		SetPos(50, 20);
		printf("撞到墙了！！！游戏结束...");
		SetPos(100, 100);
	}
}