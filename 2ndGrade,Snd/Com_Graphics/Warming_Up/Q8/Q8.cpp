#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#define SIZE 50

typedef enum {
	Left,Top,Right,Bottom
}Direction;

typedef enum {
	Start,Pass,Wall,PTOW,WTOP
}CNT_State;

using namespace std;
int MAZE[SIZE][SIZE];


int GenerateMAZE();
POINT start;
void PrintMAZE();
POINT DIG();
int main() {

	srand((unsigned)time(nullptr));

	while (1) {
	GenerateMAZE();
	PrintMAZE();
	_getch();
	system("cls");
	}




}

int GenerateMAZE()
{
	
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			MAZE[i][j] = 1;

			if(i!=0 && j!=0 && i!=SIZE-1 && j != SIZE-1 && i%2==1 && j%2==1) 	MAZE[i][j] = 0;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 1; i < SIZE - 1; i += 2) {
		for (int j = 0; j < SIZE; ++j) {
			int dice = rand() % 2;
			if (dice == 0 && j % 2 != 1 && j != 0) 	MAZE[i][j] = 0;
		}
	}

	for (int j = 1; j < SIZE - 1; j += 2) {
		for (int i = 0; i < SIZE; ++i) {
			int dice = rand() % 2;
			if (dice == 0 && i % 2 != 1 && i != 0) 	MAZE[i][j] = 0;
		}
	}

	for (int i = 1; i < SIZE - 1; i += 2) {
		for (int j = 1; j < SIZE - 1; j += 2) {
			if (MAZE[i][j] == 0 &&
				MAZE[i - 1][j] == 1 &&
				MAZE[i + 1][j] == 1 &&
				MAZE[i][j - 1] == 1 &&
				MAZE[i][j + 1] == 1
				) {

				bool iscomplete = false;

				while (!iscomplete) {

					int dice = rand() % 4;

					switch (dice) {
					case Direction::Left:
						if (j != 1) {
							MAZE[i][j - 1] = 0;
							iscomplete = true;
						}
						break;
					case Direction::Right:
						if (j != SIZE - 1) {
							MAZE[i][j + 1] = 0;
							iscomplete = true;
						}
						break;
					case Direction::Top:
						if (i != 1) {
							MAZE[i - 1][j] = 0;
							iscomplete = true;
						}
						break;
					case Direction::Bottom:
						if (i != SIZE - 1) {
							MAZE[i + 1][j] = 0;
							iscomplete = true;
						}
						break;




					}
				}


			}


		}
	}

	for (int i = 2; i < SIZE; i += 2) {
		for (int j = 2; j < SIZE; j += 2) {
			if (MAZE[i][j] == 1 &&
				MAZE[i - 1][j] == 0 &&
				MAZE[i + 1][j] == 0 &&
				MAZE[i][j - 1] == 0 &&
				MAZE[i][j + 1] == 0
				) {

				bool iscomplete = false;

				while (!iscomplete) {

					int dice = rand() % 4;

					switch (dice) {
					case Direction::Left:
						if (j != 0) {
							MAZE[i][j - 1] = 1;
							iscomplete = true;
						}
						break;
					case Direction::Right:
						if (j != SIZE) {
							MAZE[i][j + 1] = 1;
							iscomplete = true;
						}
						break;
					case Direction::Top:
						if (i != 0) {
							MAZE[i - 1][j] = 1;
							iscomplete = true;
						}
						break;
					case Direction::Bottom:
						if (i != SIZE) {
							MAZE[i + 1][j] = 1;
							iscomplete = true;
						}
						break;




					}
				}


			}


		}
	}


	return 0;
}

void PrintMAZE()
{
	POINT end = DIG();
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			switch (MAZE[i][j]) {
			case 0:
				if (i == 1 && j == 1)
					cout << "IN";
				else if (i == end.y && j == end.x)
					cout << "UT";
				else
				cout << "  ";
				break;
			case 1:
				cout << "¢Æ";
				break;
			}
		}
		cout << endl;
	}
}

POINT DIG()
{
	POINT start = { 1,1 };

	while (start.y != SIZE - 1 && start.x != SIZE - 1) {
	
		if (MAZE[start.y + 1][start.x] == 0) {
			MAZE[start.y + 1][start.x] = 0;
			start.y++;
			continue;
		}

		else if (MAZE[start.y][start.x+1] == 0) {
			MAZE[start.y][start.x+1] = 0;
			start.x++;
			continue;
		}

	
		else {
			int dice = rand() % 2;

			if (dice == 0) {
				MAZE[start.y][start.x+1] = 0;
				start.x++;
			}
			else {
				MAZE[start.y + 1][start.x] = 0;
				start.y++;
			}
			
			continue;
		}
	
	
	}

	return start;
}
