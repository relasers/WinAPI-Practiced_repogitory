#include "stdafx.h"
#include "Surface.h"


CSurface::CSurface()
{
}
CSurface::CSurface(CTextureLibraray * texture)
{
	SetSurface_XZ();
	m_TextureLib = texture;
}
CSurface::~CSurface()
{
}

void CSurface::Rendering()
{
	float t = Reciprocal(DETAIL);
	glPushMatrix();
	CTextureLibraray::UsingTexture2D();
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::BK_BOTTOM);
	glColor4f(1, 1, 1, 1);
	for (int i = 0; i < DETAIL - 1; i++)
	{
		for (int j = 0; j < DETAIL - 1; j++)
		{
			glBegin(GL_QUADS);
			glNormal3fv(m_normal[i][j].arr);
			glTexCoord2f(t*j, t*(i+1));
			glVertex3fv(m_vertex[i][j].arr);
			glTexCoord2f(t*j, t*i);
			glVertex3fv(m_vertex[i + 1][j].arr);
			glTexCoord2f(t*(j+1), t*i);
			glVertex3fv(m_vertex[i + 1][j + 1].arr);
			glTexCoord2f(t*(j+1), t*(i+1));
			glVertex3fv(m_vertex[i][j + 1].arr);
			glEnd();
		}
	}
	CTextureLibraray::StopUsingTexture2D();
	glPopMatrix();
}

void CSurface::Update(const float fTimeElapsed)
{
}

void CSurface::SetScale(const float x, const float y, const float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
	for (int i = 0; i < DETAIL; i++)
	{
		for (int j = 0; j < DETAIL; j++)
		{
			m_vertex[i][j].x *= m_Scale.x;
			m_vertex[i][j].y *= m_Scale.y;
			m_vertex[i][j].z *= m_Scale.z;
		}
	}
}

void CSurface::SetSurface_XZ()
{
	float t = Reciprocal(DETAIL);
	
	for (int i = 0; i < DETAIL; i++)
	{
		for (int j = 0; j < DETAIL; j++)
		{
			float y = -static_cast<float>(rand() % 2) *
				static_cast<float>(rand() % 100) * 0.01f;
			m_vertex[i][j] = 
			{ -(t*(DETAIL *0.5f)) + (t * j),
				y, -(t*(DETAIL *0.5f)) + (t * i) };
		}
	}
	for (int i = 0; i < DETAIL; i++)
	{
		for (int j = 0; j < DETAIL; j++)
		{
			m_vertex[i][j].x *= m_Scale.x;
			m_vertex[i][j].y *= m_Scale.y;
			m_vertex[i][j].z *= m_Scale.z;
		}
	}
	for (int i = 0; i < DETAIL - 1; i++)
	{
		for (int j = 0; j < DETAIL - 1; j++)
		{
			m_normal[i][j] = Normalize(Cross(
				m_vertex[i][j] - m_vertex[i + 1][j],
				m_vertex[i][j] - m_vertex[i + 1][j + 1]));

		}
	}
}

void CSurface::SetSurface_XY()
{
}

void CSurface::SetSurface_YZ()
{
}
