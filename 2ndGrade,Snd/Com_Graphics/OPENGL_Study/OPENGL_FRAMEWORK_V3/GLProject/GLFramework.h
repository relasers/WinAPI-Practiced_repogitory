#pragma once


class CScene;

class CGLFramework
{
private:
	
	char	m_szTile[64]	{ STR_TITLE_CAPTION };
	Point2i m_ptWindowPos	{ STARTPOSITION_X	, STARTPOSITION_Y };
	Point2i m_ptWindowSize	{ CLIENTWIDTH		, CLIENTHEIGHT };
	int		m_iFPS			= GAMEFPS;

	void	(*m_pfReshape)(int w, int h)		{ nullptr } ;
	void	(*m_pfDrawScene)()					{ nullptr } ;
	void	(*m_pfTimer)(int val)				{ nullptr } ;
	void	(*m_pfMouse)(int, int, int, int)	{ nullptr }	;

	CScene	*m_arrScene[10] = {nullptr, };
	int		m_nSceneIdx = 0;
	CScene*	m_pCurrentScene;

public:

	CGLFramework() = default;
	~CGLFramework();
	
public:

	GLvoid Initialize(GLvoid);

	GLvoid Reshape(int w, int h);
	GLvoid drawScene(GLvoid);
	GLvoid Timer(int val);
	GLvoid Mouse(int button, int state, int x, int y);
	
	GLvoid Run();

	Point2i GetWindowSize() const { return m_ptWindowSize; }

	void SetReshapeFunc	(void(*func)(int, int))				{ m_pfReshape = func; }
	void SetDrawFunc	(void(*func)())						{ m_pfDrawScene = func; }
	void SetTimerFunc	(void(*func)(int))					{ m_pfTimer = func; }
	void SetMouseFunc	(void(*func)(int, int, int, int))	{ m_pfMouse = func; }

	template<typename CreateScene> // class CreateScene 으로 해도 무방
	void BuildScene(bool SelectNewScene = true)
	{
		m_arrScene[m_nSceneIdx] = new CreateScene(); 
		auto pScene = static_cast<CreateScene* >(m_arrScene[m_nSceneIdx]);

		pScene->BuildScene(this, m_nSceneIdx);

		if (SelectNewScene)
			m_pCurrentScene = pScene;

		++m_nSceneIdx;
	}
};

