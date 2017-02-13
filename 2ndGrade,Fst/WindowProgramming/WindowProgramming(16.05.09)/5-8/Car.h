#pragma once
class CCar
{
private:
	RECT pos;
	double speed = 12.0;
	int frame =0;
	int direction = Direction::to_right;
	bool driving = true;
public:
	CCar();
	~CCar();

	RECT getpos(); // 위치를 받아오자
	int getframe();
	int getdir();

	void imageframeinc();
	void setspeed(double); //속도설정
	void setpos(POINT); // 위치설정
	void setdirection(int); // 방향설정
	void moving(RECT); // 움직여?
	void movbak(RECT); // 백 백
};

