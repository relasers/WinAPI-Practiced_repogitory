#include<iostream>
#include<Windows.h>
#include<conio.h>

#define RAND(x,y) x+rand()%y

using namespace std;

class Particle {
private:
	POINT p{};
	int speed = RAND(10, 10);
	int xvec = 1;
	int yvec = 1;
public:
	Particle() {};
	Particle(int width, int height) {
		p.x = rand() % width;
		p.y = rand() % height;

		switch (int dice = rand() % 2) {
		case 0:
			xvec = 1;
			break;
		case 1:
			xvec = -1;
		}
		switch (int dice = rand() % 2) {
		case 0:
			yvec = 1;
			break;
		case 1:
			yvec = -1;
		}
	};
	void Print() {
	cout << " (" << p.x << "," << p.y << ") ";
	};
	void Update(int width,int height) {
		p.x += speed*xvec;
		p.y += speed*yvec;

		if (p.x < 0) {
			p.x = 0;
			xvec *= -1;
		}
		if (p.x > width) {
			p.x = width;
			xvec *= -1;
		} 
		if (p.y < 0) {
			p.y = 0;
			yvec *= -1;
		} 
		if (p.y > height) {
			p.y = height;
			yvec *= -1;
		}
			
			



	};
};

void print(Particle elem[][5]);
void update(Particle elem[][5],int w, int h);
int main() {
	
	int width;
	int height;

	cout << "Input Width , Height ::";
	cin >> width >> height;
	
	Particle part[5][5];

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			part[i][j] = Particle(width,height);
		}
	}

	while (1) {
		update(part,width,height);
		print(part);
		_getch();
		system("cls");
	}
	return 0;
}

void print(Particle elem[][5])
{
	for (int i = 0; i < 5; ++i) {
	
		for (int j = 0; j < 5; ++j) {
			elem[i][j].Print();
		}
		cout << endl;
	}
}

void update(Particle elem[][5],int w,int h)
{
	for (int i = 0; i < 5; ++i) {

		for (int j = 0; j < 5; ++j) {
			elem[i][j].Update(w,h);
		}
	}

}
