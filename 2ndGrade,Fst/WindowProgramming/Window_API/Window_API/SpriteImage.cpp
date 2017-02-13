#include "SpriteImage.h"
#include <iostream>
#include <cassert>
using namespace std;


CSpriteImage::CSpriteImage(LPCTSTR path, int w, int h)
{

	m_nFrameXNum = w;
	m_nFrameYNum = h;

	// 절대 발생하면 안 되는 코드이기 때문에 발생 시 강제로 프로그램을 종료
	if (FAILED(m_ciSpriteImage.Load(path)))
		assert(!"이미지가 정상적으로 로드되지 않았습니다!");


	m_nFrameWidthSize = m_ciSpriteImage.GetWidth() / m_nFrameXNum;
	m_nFrameHeightSize = m_ciSpriteImage.GetHeight() / m_nFrameYNum;

	m_colTransparent = ::GetPixel(m_ciSpriteImage.GetDC(), 0, 0);
	
}

CSpriteImage::~CSpriteImage()
{
}

void CSpriteImage::OnUpdate()
{
	m_ptCurrentAnimationState.x++;

	if (m_ptCurrentAnimationState.x >= m_nFrameXNum)
	{
		m_ptCurrentAnimationState.x = 0;
		m_ptCurrentAnimationState.y++;
	}

	if (m_ptCurrentAnimationState.y >= m_nFrameYNum)
	{
		m_ptCurrentAnimationState.y = 0;
	}
}

void CSpriteImage::Draw(HDC hDC, int x, int y)
{
	m_ciSpriteImage.TransparentBlt(hDC,
		x, y,
		m_nFrameWidthSize, m_nFrameHeightSize,
		m_ptCurrentAnimationState.x * m_nFrameWidthSize,
		m_ptCurrentAnimationState.y * m_nFrameHeightSize,
		m_nFrameWidthSize, m_nFrameHeightSize,
		m_colTransparent
	);

}
