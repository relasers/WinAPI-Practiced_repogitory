#include <cassert>
#include "GLFramework.h"


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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
}

GLvoid CGLFramework::drawScene(GLvoid)
{
	glClearColor(0.5, 0.5, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	glutSwapBuffers();
}

GLvoid CGLFramework::Timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(m_iFPS, m_pfTimer, val);
}

GLvoid CGLFramework::InputKeyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		exit(0);
}

enum {
	 LBUTTONDOWN = ((GLUT_LEFT_BUTTON << 8) + GLUT_DOWN)
	,RBUTTONDOWN = ((GLUT_RIGHT_BUTTON << 8) + GLUT_DOWN)
	,LBUTTONUP = ((GLUT_LEFT_BUTTON << 8) + GLUT_UP)
	,RBUTTONUP = ((GLUT_RIGHT_BUTTON << 8) + GLUT_UP)
};




GLvoid CGLFramework::InputMouse(int button, int state, int x, int y)
{
	short cond = (button << 8) + state; // condition
	switch (cond) 
	{
	case LBUTTONDOWN:
		std::cout << "hello world!" << std::endl;
		break;
	case RBUTTONDOWN:
		break;
	case LBUTTONUP:
		break;
	case RBUTTONUP:
		break;
	}
}

GLvoid CGLFramework::Run()
{
	assert((m_pfDrawScene && m_pfReshape && m_pfTimer && m_pfInputMouse) 
		&& "No callback function has been set!");
	// assert :: 
	glutDisplayFunc(m_pfDrawScene);
	glutReshapeFunc(m_pfReshape);

	glutKeyboardFunc(m_pfInputKey);
	glutMouseFunc(m_pfInputMouse);

	glutTimerFunc(m_iFPS, m_pfTimer, 1);

	glutMainLoop();
}

void CGLFramework::ChangeScene(CScene::CurrentScene Tag, bool bDestroy)
{
	const int tag = GetEnumValueByType(Tag);
	//
	if (bDestroy) {
		int d_tag = GetEnumValueByType(m_pCurrentScene->GetMyTag());
		delete m_pCurrentScene;
		m_pCurrentScene = nullptr;
		m_arrScene[d_tag] = nullptr;
	}
	if (m_arrScene[tag]) { // 만약 nullptr가 아닐 경우
		m_pCurrentScene = m_arrScene[tag];
		//if (Tag == CScene::CurrentScene::Stage_0)

	}
	else {
		switch (Tag) {
		case CScene::CurrentScene::Title:
			m_arrScene[GetSceneEnumInt(Title)] = new CTitleScene();
			break;
		case CScene::CurrentScene::Lobby:
			m_arrScene[GetSceneEnumInt(Lobby)] = new CLobbyScene();
			break;
		}
		m_pCurrentScene = m_arrScene[tag];
	}
}