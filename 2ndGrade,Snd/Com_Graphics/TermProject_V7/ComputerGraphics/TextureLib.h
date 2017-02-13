#pragma once

#include <windows.h>
#include <GL/GLUT.h>
#include <atlImage.h>
#include <vector>

std::vector<GLubyte> GetCImageBits(const CImage& Cimg);

class CTextureLibraray 
{
public:

	enum TextureIndex {
		TOP = 0
		, BOTTOM
		, FORWARD
		, BACK
		, LEFT
		, RIGHT
		, BK_BOTTOM
		, BK_STORM
		, MiniMap
		, Heroes
		, Gear
		, UIBACK
		, LOGO
		, TITLE
		, GAMEOVER
		, GAMECLEAR
		, COUNT
	};

	struct GLTextureData
	{
		GLuint					textureIndex = 0;
		bool					bHasAlpha = false;
		std::vector<GLubyte>	pBytes;
		GLubyte* GetData() { return &(pBytes[0]); }

		GLTextureData(GLuint idx, bool bAlpha, std::vector<GLubyte>&& v) 
			: textureIndex{ idx }
			, bHasAlpha{ bAlpha }
			, pBytes{ v } {}

	};

private:

	static GLuint g_nStartTexture;
	
	std::vector<GLTextureData>	m_vTexData;

public:

	CTextureLibraray();
	~CTextureLibraray();

	const size_t size() const { return m_vTexData.size(); }

	void SetTexture(LPCTSTR str);
	
	void LoadTexture(size_t idx = 0);

	template<typename Fn>
	void Draw(size_t idx, Fn&& func)
	{
		GLboolean bDestAlphaState = false;
		if (m_vTexData[idx].bHasAlpha)
		{
			glGetBooleanv(GL_BLEND, &bDestAlphaState);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
		}

		glBindTexture(GL_TEXTURE_2D, m_vTexData[idx].textureIndex);
		func();

		if (m_vTexData[idx].bHasAlpha && bDestAlphaState == false)
			glDisable(GL_BLEND);
	}

	static void UsingTexture2D(bool usingEnvi = true) { ::glEnable(GL_TEXTURE_2D); if(usingEnvi) ::glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE); }
	static void StopUsingTexture2D() { ::glDisable(GL_TEXTURE_2D); }
};



