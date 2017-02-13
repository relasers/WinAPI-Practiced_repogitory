#pragma once
#include "stdafx.h"
#include "GLFramework.h"
#include "TitleScene.h"
#include "MainGameScene.h"


CGLFramework::~CGLFramework()
{
	for (auto p : m_arrScene) if (p) delete p;
}

GLvoid CGLFramework::Initialize(GLvoid)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(m_ptWindowPos.x, m_ptWindowPos.y);
	glutInitWindowSize(m_ptWindowSize.x, m_ptWindowSize.y);
	glutCreateWindow(m_szTile);

}

GLvoid CGLFramework::Reshape(int w, int h)
{
	m_ptWindowSize = Point2i { w,h };
	glViewport(0, 0, w, h);
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_pCurrentScene->Render();

	glutSwapBuffers(); // 프레임워크에서 딱 한번만 부르도록 한다
	// 다 끝나고 한번만 불러야 하니까.
}

GLvoid CGLFramework::Timer(int val)
{
	m_pCurrentScene->Update();

	glutPostRedisplay(); // 다른곳에선 redisplay 쓰지 말 것.
	glutTimerFunc(m_iFPS, m_pfTimer, val);
}

GLvoid CGLFramework::Mouse(int button, int state, int x, int y)
{
	m_pCurrentScene->Mouse(button, state, x, y);
}

GLvoid CGLFramework::KeyBoard(unsigned char key, int x, int y)
{
	m_pCurrentScene->KeyBoard(key, x, y);
}

GLvoid CGLFramework::Run()
{
	assert((m_pfDrawScene && m_pfReshape && m_pfTimer && m_pfMouse)
		&& "No callback function has been set!");
	glClearColor(0.5, 0.5, 0.8, 1); // glClearColor는 한번만 써도 된다.
	
	glutMouseFunc(m_pfMouse);
	glutKeyboardFunc(m_pfKeyBoard);
	glutDisplayFunc(m_pfDrawScene);
	glutReshapeFunc(m_pfReshape);
	glutTimerFunc(m_iFPS, m_pfTimer, 1);

	BuildScene<CTitleScene>();

	glutMainLoop();
}
