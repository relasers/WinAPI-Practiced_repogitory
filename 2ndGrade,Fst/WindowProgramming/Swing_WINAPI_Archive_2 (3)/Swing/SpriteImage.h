#pragma once
#include <Windows.h>
#include <atlimage.h>
#define PI 3.141592
class CSpriteImage
{
protected:
	int m_width; // 이미지 총 길이
	int m_height; // 이미지 총 높이
	CImage cimg; //이미지 클래스
	POINT m_ptcurrent{ 0,0 }; // 프레임 좌표
	int m_widthlen; // 한 프레임 길이
	int m_heightlen; // 한 프레임 높이
	float degree; // 각도
	COLORREF m_transcolor;
	HBRUSH m_backcolor;
public:
	CSpriteImage(LPCTSTR path, int w, int h);
	~CSpriteImage();

	void Update();
	void ClearFramePos(); // 스프라이트를 처음 동작으로 초기화
	void Draw(HDC hdc, int x, int y,RECT m_rect); //lt 기준
	void setdegree(float);

};