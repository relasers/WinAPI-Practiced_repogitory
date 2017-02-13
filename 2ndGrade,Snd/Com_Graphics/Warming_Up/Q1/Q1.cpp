#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>

using namespace std;

typedef struct {
	int elem[4][4]{};
	bool isthree = true;
}Matrix;

void initMat(Matrix elem[]);
void Plus(Matrix elem[]);
void Minus(Matrix elem[]);
void Multiply(Matrix elem[]);
void Det(Matrix elem);
void Change(Matrix elem[]);
void Print(Matrix elem);
void Getkey(Matrix elem[]);

int main() {
	srand((unsigned)time(nullptr));
	Matrix mat[3];
	initMat(mat);


	while (1) {
		Print(mat[0]);
		Print(mat[1]);
		Getkey(mat);
		system("cls");
	}


	return 0;
}



void initMat(Matrix elem[])
{
	for (int i = 0; i < 2; ++i) {
	
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				elem[i].elem[j][k] = rand() % 5;
			}
		}

		elem[i].elem[3][3] = 1;
	}
}

void Plus(Matrix elem[])
{
	if (elem[0].isthree)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j) {

				for (int k = 0; k < 2; ++k)
				{
					elem[2].elem[i][j] += elem[k].elem[i][j];
				}
			}
		}
	}

	if (!elem[0].isthree)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j) {

				for (int k = 0; k < 2; ++k)
				{
					elem[2].elem[i][j] += elem[k].elem[i][j];
				}
			}
		}
	}
	

	Print(elem[0]);
	cout << '+' << endl;
	Print(elem[1]);
	cout << '=' << endl;
	Print(elem[2]);
	
	memset(elem[2].elem,0,sizeof(elem[2].elem));
}
void Minus(Matrix elem[])
{
	if (elem[0].isthree)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j) {

				elem[2].elem[i][j] += elem[0].elem[i][j];
				elem[2].elem[i][j] -= elem[1].elem[i][j];
				
			}
		}
	}

	if (!elem[0].isthree)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j) {
				elem[2].elem[i][j] += elem[0].elem[i][j];
				elem[2].elem[i][j] -= elem[1].elem[i][j];
			}
		}
	}


	Print(elem[0]);
	cout << '-' << endl;
	Print(elem[1]);
	cout << '=' << endl;
	Print(elem[2]);

	memset(elem[2].elem, 0, sizeof(elem[2].elem));
}

void Multiply(Matrix elem[])
{
	if (elem[0].isthree) 
	{
		for (int i = 0; i<3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k) 
				{
					elem[2].elem[i][j] += elem[0].elem[i][k] * elem[1].elem[k][j];
				}
			}
		}
	}
	
	if (!elem[0].isthree)
	{
		for (int i = 0; i<4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 4; ++k)
				{
					elem[2].elem[i][j] += elem[0].elem[i][k] * elem[1].elem[k][j];
				}
			}
		}
	}
	Print(elem[0]);
	cout << '*' << endl;
	Print(elem[1]);
	cout << '=' << endl;
	Print(elem[2]);

	memset(elem[2].elem, 0, sizeof(elem[2].elem));


}

void Change(Matrix elem[])
{
	for (int i = 0; i < 3; ++i)
	{
		elem[i].isthree = false;

	}
	cout << "is Changed";
}

void Det(Matrix elem)
{
	int det=0;
	Print(elem);
	if(elem.isthree)
	{
		det += (
			elem.elem[0][0] *
			elem.elem[1][1] *
			elem.elem[2][2]
			);
		det += (
			elem.elem[0][1] *
			elem.elem[1][2] *
			elem.elem[2][0]
			);
		det += (
			elem.elem[1][0] *
			elem.elem[2][1] *
			elem.elem[0][2]
			);
		det -= (
			elem.elem[0][2] *
			elem.elem[1][1] *
			elem.elem[2][0]
			);
		det -= (
			elem.elem[0][1] *
			elem.elem[1][0] *
			elem.elem[2][2]
			);
		det -= (
			elem.elem[0][0] *
			elem.elem[2][1] *
			elem.elem[1][2]
			);
	}
	if (!elem.isthree)
	{
		////////////////////////////
		{
			det += (
				elem.elem[0][0] *
				elem.elem[1][1] *
				elem.elem[2][2] *
				elem.elem[3][3]
				);
			det += (
				elem.elem[0][0] *
				elem.elem[1][2] *
				elem.elem[2][3] *
				elem.elem[3][1]
				);
			det += (
				elem.elem[0][0] *
				elem.elem[1][3] *
				elem.elem[2][1] *
				elem.elem[3][2]
				);
		}
		
		//////////////////////////////
		{
			det += (
				elem.elem[0][1] *
				elem.elem[1][0] *
				elem.elem[2][3] *
				elem.elem[3][2]
				);
			det += (
				elem.elem[0][1] *
				elem.elem[1][2] *
				elem.elem[2][0] *
				elem.elem[3][3]
				);
			det += (
				elem.elem[0][1] *
				elem.elem[1][3] *
				elem.elem[2][2] *
				elem.elem[3][0]
				);
		}
		
		//////////////////////////////
		{
			det += (
				elem.elem[0][2] *
				elem.elem[1][0] *
				elem.elem[2][1] *
				elem.elem[3][3]
				);
			det += (
				elem.elem[0][2] *
				elem.elem[1][1] *
				elem.elem[2][3] *
				elem.elem[3][0]
				);
			det += (
				elem.elem[0][2] *
				elem.elem[1][3] *
				elem.elem[2][0] *
				elem.elem[3][1]
				);
		}
		
		//////////////////////////////
		{
			det += (
				elem.elem[0][3] *
				elem.elem[1][0] *
				elem.elem[2][2] *
				elem.elem[3][1]
				);
			det += (
				elem.elem[0][3] *
				elem.elem[1][1] *
				elem.elem[2][0] *
				elem.elem[3][2]
				);
			det += (
				elem.elem[0][3] *
				elem.elem[1][2] *
				elem.elem[2][1] *
				elem.elem[3][0]
				);
		}
		//////////////////////////////
		////////////////////////////
		{
			det -= (
				elem.elem[0][0] *
				elem.elem[1][1] *
				elem.elem[2][3] *
				elem.elem[3][2]
				);
			det -= (
				elem.elem[0][0] *
				elem.elem[1][2] *
				elem.elem[2][1] *
				elem.elem[3][3]
				);
			det -= (
				elem.elem[0][0] *
				elem.elem[1][3] *
				elem.elem[2][2] *
				elem.elem[3][1]
				);
		}

		//////////////////////////////
		{
			det -= (
				elem.elem[0][1] *
				elem.elem[1][0] *
				elem.elem[2][2] *
				elem.elem[3][3]
				);
			det -= (
				elem.elem[0][1] *
				elem.elem[1][2] *
				elem.elem[2][3] *
				elem.elem[3][0]
				);
			det -= (
				elem.elem[0][1] *
				elem.elem[1][3] *
				elem.elem[2][0] *
				elem.elem[3][2]
				);
		}

		//////////////////////////////
		{
			det -= (
				elem.elem[0][2] *
				elem.elem[1][0] *
				elem.elem[2][3] *
				elem.elem[3][1]
				);
			det -= (
				elem.elem[0][2] *
				elem.elem[1][1] *
				elem.elem[2][0] *
				elem.elem[3][3]
				);
			det -= (
				elem.elem[0][2] *
				elem.elem[1][3] *
				elem.elem[2][1] *
				elem.elem[3][0]
				);
		}

		//////////////////////////////
		{
			det -= (
				elem.elem[0][3] *
				elem.elem[1][0] *
				elem.elem[2][1] *
				elem.elem[3][1]
				);
			det -= (
				elem.elem[0][3] *
				elem.elem[1][1] *
				elem.elem[2][2] *
				elem.elem[3][0]
				);
			det -= (
				elem.elem[0][3] *
				elem.elem[1][2] *
				elem.elem[2][0] *
				elem.elem[3][1]
				);
		}
		//////////////////////////////
	}
	cout << "Det ::" << det << endl;
}

void Print(Matrix elem)
{
	if (elem.isthree) 
	{
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j)
			{
				cout << elem.elem[i][j] << ' ';
			}
			cout << endl;
		}
	}
	if (!elem.isthree)
	{
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j)
			{
				cout << elem.elem[i][j] << ' ';
			}
			cout << endl;
		}


	}
	cout << endl;

}

void Getkey(Matrix elem[])
{
	cout << "Input Command :: ";
	switch (_getche()) {
	case 'A':
	case 'a':
		cout << endl;
		Plus(elem);
		_getch();
		break;
	case 'D':
	case 'd':
		cout << endl;
		Minus(elem);
		_getch();
		break;
	case 'H':
	case 'h':
		cout << endl;
		Change(elem);
		_getch();
		break;
	case 'M':
	case 'm':
		cout << endl;
		Multiply(elem);
		_getch();
		break;
	case 'R':
	case 'r':
		cout << endl;
		Det(elem[0]);
		cout << endl;
		Det(elem[1]);
		_getch();
		break;
	default:
		break;
	}


}
