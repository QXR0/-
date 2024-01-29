#include"snake.h"

Snake snake = { 0 };
pSnake psnake = &snake;
void test()
{
	GameStart(psnake);
	GameRun(psnake);
	GameEnd(psnake);
}




int main()
{
	setlocale(LC_ALL,""); 
	srand(time(NULL));
	test();
	return 0;
}