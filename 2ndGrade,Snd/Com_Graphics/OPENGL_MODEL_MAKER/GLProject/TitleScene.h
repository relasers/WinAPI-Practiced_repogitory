#pragma once
#include "Scene.h"

class CTitleScene :
	public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();
	
public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void KeyBoard(unsigned char key, int x, int y);
	virtual void BuildScene(	  CGLFramework* pframework
								, int tag
	);

private:

	Point2f			m_ptPos			{100,100}	;

};

