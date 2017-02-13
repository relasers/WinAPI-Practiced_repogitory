#include <iostream>
#include <Windows.h>
#include <conio.h>
typedef enum {
 RR,CC,RC
}Command;

using namespace std;

RECT a;
RECT b;

void Q7Print();
void Q7InputCommand();
void Q7CollideCheck(int Command);



float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}


bool Circle_collision(int x1, int y1, int x2, int y2, RECT shape1, RECT shape2)
{
	if (LengthPts(x1, y1, x2, y2) < (shape1.right - shape1.left) / 2 + (shape2.right - shape2.left) / 2)
		return true;
	else
		return false;
}

bool InCircle(double x, double y, double rad, double px, double py)
{
	if (LengthPts(x, y, px, py) < rad)
		return true;
	else
		return false;
}

bool Collision_Rec_Ell(double c_x, double c_y, double c_rad, RECT rec_check) {
	if ((rec_check.left <= c_x && c_x <= rec_check.right) ||
		(rec_check.top <= c_y && c_y <= rec_check.bottom)) {
		RECT rec_ud_chk = {
			rec_check.left,
			rec_check.top - c_rad,
			rec_check.right,
			rec_check.bottom + c_rad,
		};
		RECT rec_sd_chk = {
			rec_check.left - c_rad,
			rec_check.top,
			rec_check.right + c_rad,
			rec_check.bottom,
		};
		if ((rec_ud_chk.left < c_x && c_x < rec_ud_chk.right) && (rec_ud_chk.top < c_y && c_y < rec_ud_chk.bottom)) {
			return true;
		}
		if ((rec_sd_chk.left < c_x && c_x < rec_sd_chk.right) && (rec_sd_chk.top < c_y && c_y < rec_sd_chk.bottom)) {
			return true;
		}
	}

	else {
		if (InCircle(c_x, c_y, c_rad, rec_check.left, rec_check.top))return true;
		if (InCircle(c_x, c_y, c_rad, rec_check.left, rec_check.bottom))return true;
		if (InCircle(c_x, c_y, c_rad, rec_check.right, rec_check.top))return true;
		if (InCircle(c_x, c_y, c_rad, rec_check.right, rec_check.bottom))return true;
	}
	return false;
}

int main() {

	int Command;

	cout << " 0 :: R X R" << endl;
	cout << " 1 :: C X C" << endl;
	cout << " 2 :: R X C" << endl;

	cout << "InPut Mode :: ";
	cin >> Command;
	system("cls");
	cout << "Input First L :: ";
	cin >> a.left;
	cout << "Input First T :: ";
	cin >> a.top;
	cout << "Input First R :: ";
	cin >> a.right;
	cout << "Input First B :: ";
	cin >> a.bottom;

	cout << "Input Second L :: ";
	cin >> b.left;
	cout << "Input Second T :: ";
	cin >> b.top;
	cout << "Input Second R :: ";
	cin >> b.right;
	cout << "Input Second B :: ";
	cin >> b.bottom;
	system("cls");
	while (1) {
		Q7CollideCheck(Command);
		Q7Print();
		Q7InputCommand();
		system("cls");
	}


}

void Q7Print()
{
	cout << "Shape 1" << "(" << a.left << " , " << a.top << ")" << " , " << "(" << a.right << " , " << a.bottom << ")" << endl;
	cout << "Shape 2" << "(" << b.left << " , " << b.top << ")" << " , " << "(" << b.right << " , " << b.bottom << ")" << endl;
	cout << "Left :: a || Right :: d || Top :: w || Down :: s " << endl;
}

void Q7InputCommand()
{
	switch (_getch()) {
	case 'W':
	case 'w':
		OffsetRect(&b,0,-20);
		break;
	case 'A':
	case 'a':
		OffsetRect(&b, -20, 0);
		break;
	case 'S':
	case 's':
		OffsetRect(&b, 0, 20);
		break;
	case 'D':
	case 'd':
		OffsetRect(&b, 20, 0);
		break;
	default:
		break;
	}

}

void Q7CollideCheck(int Command)
{
	switch (Command) {
	case Command::RR: 
		{
			RECT temp;
			if (IntersectRect(&temp, &a, &b)) 
			{
				cout << "R1 & R2 is Collide!!!" << endl;
			}
		}
		break;
	case Command::CC:
	{
		int x1 = a.left + (a.right - a.left) / 2;
		int y1 = a.top + (a.bottom - a.top) / 2;
		int x2 = b.left + (b.right - b.left) / 2;
		int y2 = b.top + (b.bottom - b.top) / 2;

		if (Circle_collision(x1, y1, x2, y2, a, b)) {
			cout << "C1 & C2 is Collide!!!" << endl;
		}
	}
	break;
	case Command::RC:
	{
		RECT temp;
		if (IntersectRect(&temp, &a, &b))
		{
			if(Collision_Rec_Ell(
				b.left + (b.right - b.left / 2) ,
				b.bottom + (b.bottom - b.top / 2) , 
				(b.right - b.left / 2) , 
				a))	cout << "R1 & C2 is Collide!!!" << endl;
		}
	}
	break;
	}
}
