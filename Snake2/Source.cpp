#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
const int width = 20;
const int height = 20;
int xHead = width / 2;
int yHead = height / 2;
int xFruit = rand()%(width-3)+1;
int yFruit = rand()%(width-3)+1;
int Talex[100];
int Taley[100];
int TaleSize=0;
bool gameover = false;
int score = 0;
int Speed=200;
using namespace std;
enum eDirection
{
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
eDirection dir;
void Setup()
{
	gameover = false;
	dir = STOP;
	xHead = width / 2;
	yHead = height / 2;
	TaleSize = 0;
	int xFruit = rand() % (width - 3) + 1;
	int yFruit = rand() % (width - 3) + 1;
	for (int i = 0; i < 100; i++)
	{
		Talex[i] = 0;
	}
	for (int i = 0; i < 100; i++)
	{
		Taley[i] = 0;
	}
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out= GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO		cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);

}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				if (dir != RIGHT)
					dir = LEFT;
					break;
			case 'd':
				if (dir != LEFT)
					dir = RIGHT;
				break;
			case 'w':
				if (dir != DOWN)
					dir = UP;
				break;
			case 's':
				if (dir != UP)
					dir =DOWN;
				break;

		}
	}
}
void logic()
{
	int n = 0;
	if (xHead == width - 1||xHead==0)
	{
		gameover = true;
	}
	if (yHead == height - 1 || yHead == 0)
	{
		gameover = true;
	}
	if ((xHead == xFruit) && (yHead == yFruit))
	{
		xFruit = rand() % (width - 3)+1;
		yFruit = rand() % (width - 3)+1;
		Speed -= 10;
		for (int k = 0; k < TaleSize; k++)
		{
			while (Talex[k] == xFruit && Taley[k] == yFruit)
			{
				xFruit = rand() % (width - 3)+1;
				yFruit = rand() % (width - 3)+1;
				k = 0;
				n++;
				if (n > 15)
				{
					gameover = true;
					break;
				}
			}
		}
		score += 10;
		TaleSize++;

	}
	if (TaleSize != 0)
	{
		for (int i = TaleSize - 1; i >= 1; i--)
		{
			Talex[i] = Talex[i - 1];
			Taley[i] = Taley[i - 1];
		}
		Talex[0] = xHead;
		Taley[0] = yHead;
	}
	switch (dir)
	{
	case RIGHT:
		xHead++;
		break;
	case LEFT:
		xHead--;
		break;
	case UP:
		yHead--;
		break;
	case DOWN:
		yHead++;
		break;
	}
	for (int i = 0; i < 100; i++)
	{
		if ((Talex[i] == xHead) && (Taley[i] == yHead))
		{
			gameover = true;
		}
	}
}
void fruit()
{
	xFruit=rand() % (width - 2);
	yFruit = rand() % (height - 2);
}
void drow()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0,0 });
	SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED|5);
	for (int i = 0; i < width; i++)
	{
		std::cout << "#";
	}
	std::cout << "\n";
	for (int y = 1; y < height-1 ; y++)
	{
		for (int x = 0; x < width; x++)
		{
			bool empty = true;
			if ((x == 0|| x==width-1) && empty==true)
			{
				std::cout << "#";
				empty = false;
			} 
			if (x==xHead&& y==yHead && empty == true)
			{
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "O";
				empty = false;
			}
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED | 5);
			if (empty == true&& x == xFruit && y == yFruit)
			{
				SetConsoleTextAttribute(hConsole, 8);
				std::cout << "F";
				empty = false;
			}
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED | 5);
			for (int k = 0; k < TaleSize; k++)
			{
				if ((Talex[k] == x && Taley[k] == y) && (empty == true))
				{
					std::cout << "o";
					empty = false;
				}
			}
			if (empty == true)
			{
				std::cout << " ";
				empty = false;
			}
		}
		std::cout << "\n";
	}
	for (int i = 0; i < width; i++)
	{
		std::cout << "#";
	}
	printf("\nScore %d",score);
	printf("\ncoordinates %d %d",xFruit,yFruit);
}
int main()
{
	system("cls");
	Setup();
	ShowConsoleCursor(false);
	while (!gameover)
	{
		Sleep(Speed);
		input();
		drow();
		logic();
		
	}
	system("cls");
	setlocale(LC_ALL, "Russian");
	cout << "Нажмите конпку R для рестарта";

	if (_getch() == 'r')
	{
		main();
	}
	return 0;
}
