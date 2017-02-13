#pragma once

class CM_Sky
{
private:
	float m_size{ 4096.0f };
	float m_angle{};

	

	CTextureLibraray* m_TextureLib;
	CCamera_OpenGL* m_camera;
public:
	CM_Sky();
	CM_Sky(CTextureLibraray *texture, CCamera_OpenGL &camera);
	~CM_Sky();

	bool Update(const float fTimeElapsed);
	void Rander();

};

