#pragma once
#include"stdafx.h"

class CShape
{
private:
	Vec2i m_cpt{};
	int m_n_vertex;
	float m_size = 1.0;
	int x_reflet = 1;
	int y_reflet = 1;

	list <Vec2i> vertex;
public:
	CShape();
	CShape(POINT pt, int number_vertex);
	~CShape();

	GLvoid Update();
	GLvoid Draw();

	GLvoid InputKeyBoard(int direction);
	GLvoid Reflect(int direction);
	GLvoid Reshape(int number_vertex);

	Vec2i GetPoint() { return m_cpt; }
	float GetSize() { return m_size; }
	int GetNVertex() { return m_n_vertex; }
};

