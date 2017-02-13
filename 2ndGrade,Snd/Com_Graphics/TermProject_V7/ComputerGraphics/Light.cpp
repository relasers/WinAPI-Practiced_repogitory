#include "stdafx.h"
#include "Light.h"


CLight::CLight()
{
	for (int i = 0; i < 8; i++)
	{
		m_LightParam[i].AmbientLight[0] = 0.0f;
		m_LightParam[i].AmbientLight[1] = 0.0f;
		m_LightParam[i].AmbientLight[2] = 0.0f;
		m_LightParam[i].AmbientLight[3] = 1.0f;
		m_LightParam[i].DiffuseLight[0] = 1.0f;
		m_LightParam[i].DiffuseLight[1] = 1.0f;
		m_LightParam[i].DiffuseLight[2] = 1.0f;
		m_LightParam[i].DiffuseLight[3] = 1.0f;
		m_LightParam[i].SpecularLight[0] = 1.0f;
		m_LightParam[i].SpecularLight[1] = 1.0f;
		m_LightParam[i].SpecularLight[2] = 1.0f;
		m_LightParam[i].SpecularLight[3] = 1.0f;
		m_LightParam[i].LightPosition[0] = 0.0f;
		m_LightParam[i].LightPosition[1] = 0.0f;
		m_LightParam[i].LightPosition[2] = 0.0f;
		m_LightParam[i].LightPosition[3] = 1.0f;
		m_LightParam[i].SpotDirection[0] = 0.0f;
		m_LightParam[i].SpotDirection[1] = 0.0f;
		m_LightParam[i].SpotDirection[2] = 0.0f;
		m_LightParam[i].SpotDirection[3] = 0.0f;
		m_LightParam[i].SpotExponent = 5.0f;
		m_LightParam[i].SpotCutOff = 30.0f;
		m_LightParam[i].bSpotLight = false;
	}
}
CLight::~CLight()
{
}

void CLight::Light(LightTag Tag)
{
	glLightfv(Tag, GL_AMBIENT, m_LightParam[Tag - LightTag::Light0].AmbientLight);
	glLightfv(Tag, GL_DIFFUSE, m_LightParam[Tag - LightTag::Light0].DiffuseLight);
	glLightfv(Tag, GL_SPECULAR, m_LightParam[Tag - LightTag::Light0].SpecularLight);
	glLightfv(Tag, GL_POSITION, m_LightParam[Tag - LightTag::Light0].LightPosition);
	if (m_LightParam[Tag - LightTag::Light0].bSpotLight)
	{
		glLightf(Tag, GL_SPOT_CUTOFF, m_LightParam[Tag - LightTag::Light0].SpotCutOff);
		glLightf(Tag, GL_SPOT_EXPONENT, m_LightParam[Tag - LightTag::Light0].SpotExponent);
		glLightfv(Tag, GL_SPOT_DIRECTION, m_LightParam[Tag - LightTag::Light0].SpotDirection);
	}
}

void CLight::SettingLight()
{
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, m_Model_AmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0f);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0f);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_Material_SpecularLight);
	glMateriali(GL_FRONT, GL_SHININESS, m_Material_Shiness);
}

void CLight::SetModelAmbient(const float r, const float g, const float b)
{
	m_Model_AmbientLight[0] = r;
	m_Model_AmbientLight[1] = g;
	m_Model_AmbientLight[2] = b;
}

void CLight::SetMaterialSpecular(const float r, const float g, const float b)
{
	m_Material_SpecularLight[0] = r;
	m_Material_SpecularLight[0] = g;
	m_Material_SpecularLight[0] = b;
}

void CLight::SetLightAmbient(LightTag Tag, const float r, const float g, const float b)
{
	m_LightParam[Tag - LightTag::Light0].AmbientLight[0] = r;
	m_LightParam[Tag - LightTag::Light0].AmbientLight[1] = g;
	m_LightParam[Tag - LightTag::Light0].AmbientLight[2] = b;
}

void CLight::SetLightDiffuse(LightTag Tag, const float r, const float g, const float b)
{
	m_LightParam[Tag - LightTag::Light0].DiffuseLight[0] = r;
	m_LightParam[Tag - LightTag::Light0].DiffuseLight[1] = g;
	m_LightParam[Tag - LightTag::Light0].DiffuseLight[2] = b;
}

void CLight::SetLightSpecular(LightTag Tag, const float r, const float g, const float b)
{
	m_LightParam[Tag - LightTag::Light0].SpecularLight[0] = r;
	m_LightParam[Tag - LightTag::Light0].SpecularLight[1] = g;
	m_LightParam[Tag - LightTag::Light0].SpecularLight[2] = b;
}

void CLight::SetLightPosition(LightTag Tag, const float x, const float y, const float z)
{
	m_LightParam[Tag - LightTag::Light0].LightPosition[0] = x;
	m_LightParam[Tag - LightTag::Light0].LightPosition[1] = y;
	m_LightParam[Tag - LightTag::Light0].LightPosition[2] = z;
}

void CLight::SetSpotDirection(LightTag Tag, const float x, const float y, const float z)
{
	m_LightParam[Tag - LightTag::Light0].SpotDirection[0] = x;
	m_LightParam[Tag - LightTag::Light0].SpotDirection[1] = y;
	m_LightParam[Tag - LightTag::Light0].SpotDirection[2] = z;
}