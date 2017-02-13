#pragma once
#include"stdafx.h"

class CLine
{
private:
	Vec2i m_pt{}; // {left, top}
	int m_size{0};
public:
	CLine();
	CLine(int x,int lineNum, int Client_w,int Client_h);
	// 
	~CLine();

	GLvoid draw();
};

