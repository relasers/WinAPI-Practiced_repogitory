#include<iostream>
#include<conio.h>
#include"Vec3D.h"

using namespace std;

Vector3D<float>a;
Vector3D<float>b;

int Q3InsertCommand();

void Q3Print();
void Q3Plus();
void Q3Minus();
void Q3Inner();
void Q3Outer();
void Q3EachSize();

int main() {
	
	cout << "Input Vector_1 ::";
	cin >> a.x >> a.y >> a.z;
	cout << "Input Vector_2 ::";
	cin >> b.x >> b.y >> b.z;

	while (1) {
		Q3Print();
		if (Q3InsertCommand() == 0)
			break;
		system("cls");
	}
}


int Q3InsertCommand()
{
	switch (_getche()) {
	case '+':
		cout << endl;
		Q3Plus();
		break;
	case '-':
		cout << endl;
		Q3Minus();
		break;
	case 'D':
	case 'd':
		cout << endl;
		Q3Inner();
		break;
	case 'C':
	case 'c':
		cout << endl;
		Q3Outer();
		break;
	case 'L':
	case 'l':
		cout << endl;
		Q3EachSize();
		break;
	case 'Q':
	case 'q':
		cout << endl;
		return 0;
	default:
		break;
	}
	_getch();
	return 1;
}

void Q3Print()
{
	cout << "+ : 더하기" << endl;
	cout << "- : 빼기" << endl;
	cout << "d : 내적과 두 벡터의 사잇각" << endl;
	cout << "c : 외적" << endl;
	cout << "l : 두 벡터 각각의 크기" << endl;
	cout << "q : 종료" << endl;
}

void Q3Plus()
{
	Vector3D<float>c;
	c = a + b;
	cout << a << "+" << b << "=" << c << endl;
}

void Q3Minus()
{
	Vector3D<float>c;
	c = a - b;
	cout << a << "-" << b << "=" << c << endl;
}

void Q3Inner()
{
	float c;
	c = a * b;
	
	cout << a << "*" << b << "=" << c << endl;
	float angle = c / (a.Length()*b.Length());
	cout << "cos :: " << angle << endl;
}

void Q3Outer()
{
	Vector3D<float>c;
	c = a / b;
	cout << a << "X" << b << "=" << c << endl;
}

void Q3EachSize()
{
	cout << a << "=" << a.Length() << endl;
	cout << b << "=" << b.Length() << endl;
}
