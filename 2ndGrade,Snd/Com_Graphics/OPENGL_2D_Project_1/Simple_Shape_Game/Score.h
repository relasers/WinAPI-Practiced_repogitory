#pragma once
#include "stdafx.h"
class CScore
{
private:
	Vec2i m_cpt{ 550,650 };
	int m_score = 0;
public:
	

	CScore();
	~CScore();

	GLvoid Draw();
	GLvoid Update();
	GLvoid GainScore();

	int GetScore() { return m_score; }
};

