#pragma once

struct LightParam
{
	float AmbientLight[4];
	float DiffuseLight[4];
	float SpecularLight[4];
	float LightPosition[4];
	float SpotDirection[4];
	float SpotCutOff;
	float SpotExponent;
	bool bSpotLight;
};
class CLight
{
public:
	enum LightTag : const short {
		Light0 = GL_LIGHT0
		, Light1 = GL_LIGHT1
		, Light2 = GL_LIGHT2
		, Light3 = GL_LIGHT3
		, Light4 = GL_LIGHT4
		, Light5 = GL_LIGHT5
		, Light6 = GL_LIGHT6
		, Light7 = GL_LIGHT7
		
	};
private:
	float m_Model_AmbientLight[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float m_Material_SpecularLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int m_Material_Shiness = 64;

	LightParam m_LightParam[8];

public:
	CLight();
	~CLight();

	void LightOn(LightTag LightTag) { glEnable(LightTag); };
	void LightOff(LightTag LightTag) { glDisable(LightTag); };

	void Light(LightTag Tag);

	void SettingLight();

	void SetModelAmbient(const float r, const float g, const float b);
	void SetMaterialSpecular(const float r, const float g, const float b);
	void SetMaterialShiness(const int sh) { m_Material_Shiness = sh; }

	void SetLightAmbient(LightTag Tag, const float r, const float g, const float b);
	void SetLightDiffuse(LightTag Tag, const float r, const float g, const float b);
	void SetLightSpecular(LightTag Tag, const float r, const float g, const float b);
	void SetLightPosition(LightTag Tag, const float x, const float y, const float z);
	void SetSpotDirection(LightTag Tag, const float x, const float y, const float z);
	void SetLightToSpot(LightTag Tag) { m_LightParam[Tag - LightTag::Light0].bSpotLight = true; }
	void SetSpotToLight(LightTag Tag) { m_LightParam[Tag - LightTag::Light0].bSpotLight = false; }
	void SetSpotCutOff(LightTag Tag, const float cutoff) 
	{ m_LightParam[Tag - LightTag::Light0].SpotCutOff = cutoff; }
	void SetSpotExponent(LightTag Tag, const float exponent) 
	{ m_LightParam[Tag - LightTag::Light0].SpotExponent = exponent; }
};

