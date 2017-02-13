#pragma once
#include "Scene.h"
#include "TextureLib.h"
class CTitleScene :
	public CScene
{
private:
	
	Texture


public:
	CTitleScene();
	virtual ~CTitleScene();
	
public:
	virtual void Update();
	virtual void Render();
	virtual void Reshape();
	virtual void Mouse(int button, int state, int x, int y);

	virtual void BuildScene(	  CGLFramework* pframework
								, int tag
	);

private:

	Point2f			m_ptPos			{100,100}	;

};

