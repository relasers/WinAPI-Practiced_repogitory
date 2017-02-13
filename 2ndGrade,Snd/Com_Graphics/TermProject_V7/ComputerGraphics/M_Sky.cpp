#include "stdafx.h"
#include "M_Sky.h"
#include "RanderProp.h"

CM_Sky::CM_Sky()
{
}

CM_Sky::CM_Sky(CTextureLibraray * texture,CCamera_OpenGL & camera)
{
	m_TextureLib = texture;
	m_camera = &camera;
}
CM_Sky::~CM_Sky()
{
}

bool CM_Sky::Update(const float fTimeElapsed)
{
	m_angle += 60.0f * fTimeElapsed;
	if (m_angle > 360.0f) m_angle = 0.0f;
	return false;
}

void CM_Sky::Rander()
{
	glEnable(GL_BLEND);
	

	glPushMatrix();
	{
		

		glPushMatrix();
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0f, 0.0f, 0.23f, 0.3f);
			glRotatef(m_angle*0.1,0,1,1);
			glutWireSphere(m_size*0.5f, 200, 100);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		glPopMatrix();

		m_camera->LookAt_IgnoreFar();
		glTranslatef(0,m_size*0.1,0);
		glRotatef(m_angle, 1, 1, 1);
		

		CTextureLibraray::UsingTexture2D();
		{
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::BK_STORM);
			glColor4f(1.0, 1.0, 1.0,0.9f);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			glutSolidSphere(m_size, 64, 64);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		}
		CTextureLibraray::StopUsingTexture2D();

	}
	glPopMatrix();
	
	glPushMatrix();
	{
	glTranslatef(0, m_size*0.15, m_size*0.8);

	CTextureLibraray::UsingTexture2D();
	{
		
		m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::Heroes);
		glRotatef(m_angle, 0, 0, 1);

		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		RandQuad({ 0,0,-1 }, m_size*0.5 + sin(m_angle*PI / 180.0)*m_size*0.4, true);
		

	}
	CTextureLibraray::StopUsingTexture2D();

	}
	glPopMatrix();
	glDisable(GL_BLEND);
	m_camera->LookAt();
}
