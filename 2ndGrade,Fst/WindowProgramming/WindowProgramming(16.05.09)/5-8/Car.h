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

	RECT getpos(); // ��ġ�� �޾ƿ���
	int getframe();
	int getdir();

	void imageframeinc();
	void setspeed(double); //�ӵ�����
	void setpos(POINT); // ��ġ����
	void setdirection(int); // ���⼳��
	void moving(RECT); // ������?
	void movbak(RECT); // �� ��
};

