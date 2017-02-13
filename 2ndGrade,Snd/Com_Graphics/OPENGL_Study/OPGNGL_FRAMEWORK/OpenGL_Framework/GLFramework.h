#pragma once
#include<gl/glut.h>

using namespace std;

GLvoid TimerFunction(int value); // 타이머를 선언만 해놓는다.
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

template<typename Ty>
struct Point2D {
	Ty x;
	Ty y;
};

using Point2i = Point2D<int>;
using Point2f = Point2D<float>;

class CGLFramework
{
private:
	char	m_szTile[64] = "OPGNGL_Framework";
	Point2i m_ptWindowPos	{100,100};
	Point2i m_ptWindowSize	{800,600};
	int		m_iFPS = 16;

public:
	CGLFramework() = default;
	~CGLFramework() = default;

public:
	GLvoid Initialize(GLvoid);

	GLvoid drawScene(GLvoid);
	GLvoid Reshape(int w, int h);
	GLvoid TimerFunction(int value);

	GLvoid Run();
};

