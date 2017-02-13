#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include "BOARD.h"
using namespace std;

#define SIZE 10

CBOARD board[SIZE][SIZE];

void Q9_Print();
void Q9_Init();
int Q9_Dice(int pos);
int main() {
	int posit = 0;
	srand((unsigned)time(nullptr));

	Q9_Init();
	
	while (1) {

		
		Q9_Print();
		posit += Q9_Dice(posit);
		system("cls");
		
		if (posit == SIZE*SIZE - 1) {
			Q9_Print();
			cout << "<< Win >>" << endl;
			break;
		}
		else if (posit > SIZE*SIZE-1) {
			Q9_Print();
			cout << " << Lose >>" << endl;
			break;
		}
	}
	return 0;
}

void Q9_Print()
{

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			switch (i % 2) 
			{
			case 0:
				cout << board[i][j];
				break;
			case 1:
				cout << board[i][SIZE-1-j];
				break;
			}
		}

		cout << endl;
	}



}

void Q9_Init()
{
	int num = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			board[i][j] = CBOARD(num);
			++num;
		}

	}


	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			int x = { rand() % SIZE };
			int y = { rand() % SIZE };
			int num = board[i][j].GetNumber();
			board[i][j].InsertNumber(board[y][x].GetNumber());
			board[y][x].InsertNumber(num);
		}

	}

}

int Q9_Dice(int pos)
{
	int x = rand() % 6 + 1;
	
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (board[i][j].GetNumber() == x + pos)
			board[i][j].Changestate();
		}

	}
	cout << "Dice :: " << x << endl;
	cout << "PLZ push any key to continue";
	_getch();

	return x;
}
