#include<iostream>
#include<conio.h> //pt functii care ajuta citirearea de la tastatura 
#include<windows.h> //pentru functia sleep
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y;
int fruitX, fruitY;
int tailX[100], tailY[100];
int nTail;
int score;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width+2 ; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width ; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k=0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "*";
						print = true;
					}				
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl<< "SCORE: "<<score;
}

void Input()
{
	if(_kbhit())
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
}

void Logic()
{
	int prevX=tailX[0];
	int prevY= tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case STOP:
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--; 
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//Trecerea dintr-un perete in celalalt
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
 
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(200);
	}  
	return 0;
}




//
//int v[n]
//int aux
// for(i=0;i<n-1;i++)
//	 v[i]=v[i+1]
