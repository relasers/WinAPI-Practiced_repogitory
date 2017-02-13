#pragma once
#include <Windows.h>
#include <atlimage.h>
#define PI 3.141592
class CSpriteImage
{
protected:
	int m_width; // �̹��� �� ����
	int m_height; // �̹��� �� ����
	CImage cimg; //�̹��� Ŭ����
	POINT m_ptcurrent{ 0,0 }; // ������ ��ǥ
	int m_widthlen; // �� ������ ����
	int m_heightlen; // �� ������ ����
	float degree; // ����
	COLORREF m_transcolor;
	HBRUSH m_backcolor;
public:
	CSpriteImage(LPCTSTR path, int w, int h);
	~CSpriteImage();

	void Update();
	void ClearFramePos(); // ��������Ʈ�� ó�� �������� �ʱ�ȭ
	void Draw(HDC hdc, int x, int y,RECT m_rect); //lt ����
	void setdegree(float);

};