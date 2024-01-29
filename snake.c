#include"snake.h"

//���ù��λ��
void SetPos(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOutput = NULL;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//��ӭ����
void WelcomeGame()
{
	SetPos(50, 11);
	printf("��ӭ����̰���ߣ���");
	SetPos(50, 12);
	printf("̰������һ��...��������");
	SetPos(50, 15);

	system("pause");
	system("cls");
}

//���ܽ���
void IntroduceFunction()
{
	SetPos(50, 11);
	printf("��������������� ���ټ���F1 ���ټ���F2");
	SetPos(50, 12);
	printf("�˳���Esc ��ͣ��Space");
	SetPos(50, 16);
	system("pause");
	system("cls");
}

//���Ƶ�ͼ
void MakeMap()
{
	
	//��
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i < 70; i+=2)
	{
		printf("��");
	}
	//��
	SetPos(0, 30);
	for (i = 0; i <= 70; i += 2)
	{
		printf("��");
	}
	//��
	for (i = 0; i < 30; i++)
	{
		SetPos(0, i);
		printf("��");
	}
	//��
	for (i = 0; i < 30; i++)
	{
		SetPos(70, i);
		printf("��");
	}

	//�Ҳ������Ϣ
	SetPos(80, 14);
	printf("��������������� ���ټ���a ���ټ���s");
	SetPos(80, 15);
	printf("�˳���Esc ��ͣ��Space");
	
}

//��ʼ����
void InitSnake(pSnake psnake)
{
	psnake->sleeptime = 200;
	psnake->direction = RIGHT;
	psnake->foodweight = 10;
	psnake->pfood = NULL;
	CreatFood(psnake);
	psnake->score = 0;
	psnake->state = RUN;
	//��ʼ����ͷ
	psnake->psnakehead = (SnakeNode*)malloc(sizeof(SnakeNode));
	psnake->psnakehead->x = 60;
	psnake->psnakehead->y = 14;
	//��ʼ������
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

   
//����ʳ��
void CreatFood(pSnake psnake)
{
	psnake->pfood = (pFood*)malloc(sizeof(pFood));
	while ((psnake->pfood->x = rand() % 70 + 2) % 2 == 1);
	psnake->pfood->y = rand() % 29 + 1;
	SetPos(psnake->pfood->x, psnake->pfood->y);
	printf("��");
}




//��Ϸ��ʼ
void GameStart(pSnake psnake)
{
	//���ô��ڴ�С
	system("mode con cols=120 lines=35");

	//���ñ���
	system("title ̰����");

	//���ع��
	HANDLE hOutput = NULL;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo);

	
	//��ӭ����
	WelcomeGame();

	//���ܽ���
	IntroduceFunction();

	//���Ƶ�ͼ
	MakeMap();

	//��ʼ����
	InitSnake(psnake);
	
}

//��ӡ����
void PrintScore(pSnake psnake)
{
	SetPos(80, 17);
	printf("������%d", psnake->score);
}


//������ͷ�ڵ�
void CreatNewNode(pSnake psnake, int x, int y)
{
	pSnakeNode phead = (pSnakeNode)malloc(sizeof(SnakeNode));
	phead->x = x;
	phead->y = y;
	phead->next = psnake->psnakehead;
	psnake->psnakehead = phead;
}


//�ߵ��˶�
void SnakeMove(pSnake psnake)
{
	switch (psnake->direction)
	{
		
	case UP:  
		CreatNewNode(psnake, psnake->psnakehead->x, psnake->psnakehead->y - 1);
		pSnakeNode pur = psnake->psnakehead;
		if (psnake->psnakehead->x == psnake->pfood->x && psnake->psnakehead->y - 1 == psnake->pfood->y)
		{
			//��ʳ��

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
			
		}
		else
		{
			//����ʳ��
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("��");
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
			//��ʳ��

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
		}
		else
		{
			//����ʳ��
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("��");
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
			//��ʳ��

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
		}
		else
		{
			//����ʳ��
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("��");
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
			//��ʳ��

			while (pur)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			psnake->score += psnake->foodweight;
			CreatFood(psnake);
		}
		else
		{
			//����ʳ��
			while (pur->next->next)
			{
				SetPos(pur->x, pur->y);
				printf("��");
				pur = pur->next;
			}
			SetPos(pur->x, pur->y);
			printf("��");
			SetPos(pur->next->x, pur->next->y);

			printf("  ");
			free(pur->next);
			pur->next = NULL;

		}
		break;
	}
}


//��Ϸ����
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
			//û����
			psnake->sleeptime -= 100;
		}
		else if (KEY_PRESS(VK_F2))
		{
			//û����
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



//��Ϸ����
void GameEnd(pSnake psnake)
{
	if (psnake->state == BY_MYSELF_KILL)
	{
		SetPos(50, 20);
		printf("ײ���Լ��ˣ�������Ϸ����...");
		SetPos(100, 100);

	}
	if (psnake->state == BY_WALL_KILL)
	{
		SetPos(50, 20);
		printf("ײ��ǽ�ˣ�������Ϸ����...");
		SetPos(100, 100);
	}
}