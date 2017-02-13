#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "Cardialspline.h"


CMainGameScene::CMainGameScene()
{
}


CMainGameScene::~CMainGameScene()
{
}

void CMainGameScene::Update()
{

}

void CMainGameScene::Render()
{
	glColor3ub(100,100,100);
	//glutSolidCube(1.f);

	glPushMatrix();
	{
		glColor3f(1.f, 0.f, 0.f);


		glBegin(GL_LINE_STRIP);
		for(float f = 0.f;f <=1.f;++f)
			glVertex3fv(CCardinalspline::CalcCardinal(
			f, 0.5f, 
			Vec3f{-0.5,-0.5,0}, 
			Vec3f{ -0.5,+0.5,0 },
			Vec3f{ +0.5,+0.5,0 },
			Vec3f{ +0.5,-0.5,0 }
		).arr);
		glEnd();

		glPointSize(20.0);
		glColor3f(1.f,1.f,1.f);
		glBegin(GL_POINTS); 
		{
			glVertex3fv(Vec3f{ -0.5,-0.5,0 }.arr);
			glVertex3fv(Vec3f{ -0.5,+0.5,0 }.arr);
			glVertex3fv(Vec3f{ +0.5,+0.5,0 }.arr);
			glVertex3fv(Vec3f{ +0.5,-0.5,0 }.arr);

		
		}
		glEnd();
	
	}
	glPopMatrix();

}

void CMainGameScene::Reshape()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	m_camera.SetAspect(static_cast<float>(sz.x) / static_cast<float>(sz.y));

	m_camera.LookAt();
}

void CMainGameScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_camera.Move({ 0, 0, 1 });
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		m_camera.Move({ 0, 0, -1 });
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.5, 0.5, 0.8, 1);
}
