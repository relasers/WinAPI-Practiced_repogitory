#include "stdafx.h"
#include "Cube.h"


CCube::CCube()
{
	m_Center = { 0.0f , 0.0f , 0.0f };
	m_scale = { 20.0f, 20.0f, 20.0f };
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
	RotateInit();
}
CCube::CCube(CTextureLibraray * texture)
{
	m_TextureLib = texture;
	m_Center.x = static_cast<float>((rand() % MapSize) - MapSize / 2);
	m_Center.y = 0.0f;
	m_Center.z = static_cast<float>((rand() % MapSize) - MapSize / 2);
	float l = sqrt(m_Center.x*m_Center.x + m_Center.z*m_Center.z);
	Vec3f vec = CalcNormalize(m_Center);
	if (l < 400.0f)
	{
		m_Center = 400.0f * vec;
	}
	m_scale.x = 50.0f + rand() % 150;
	m_scale.y = 500.0f + rand() % 350;
	m_scale.z = 50.0f + rand() % 150;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
	m_Angle.pitch = 5 - rand() % 10;
	m_Angle.yaw = 45 - rand() % 90;
	m_Angle.roll =  5 - rand() % 10;
	Rotate(m_Angle.pitch, true, false, false);
	Rotate(m_Angle.yaw, false, true, false);
	Rotate(m_Angle.roll, false, false, true);
	RotateInit();
}
CCube::~CCube()
{
}
void CCube::SetPos(Vec3f & pos)
{
	m_Center = pos;
	RotateInit();
}
void CCube::RotateInit()
{
	Vec3f temp[8];
	for (int i = 0; i < 8; i++) temp[i] = { 0.0f, 0.0f, 0.0f };
	
	m_Cube[CubePos::LTF] = { -1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::LTB] = { -1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::RTF] = { 1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::RTB] = { 1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::LBF] = { -1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::LBB] = { -1.0f, -1.0f, -1.0f };
	m_Cube[CubePos::RBF] = { 1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::RBB] = { 1.0f, -1.0f, -1.0f };
	for (int i = 0; i < 8; i++)
	{
		m_Cube[i].x *= m_scale.x;
		m_Cube[i].y *= m_scale.y;
		m_Cube[i].z *= m_scale.z;
	}
	for (int i = 0; i < 3; i++)  
		for (int j = 0; j < 3; j++)
		{
			temp[CubePos::LTF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LTF].arr[j];
			temp[CubePos::LTB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LTB].arr[j];
			temp[CubePos::RTF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RTF].arr[j];
			temp[CubePos::RTB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RTB].arr[j];
			temp[CubePos::LBF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LBF].arr[j];
			temp[CubePos::LBB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LBB].arr[j];
			temp[CubePos::RBF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RBF].arr[j];
			temp[CubePos::RBB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RBB].arr[j];
		}
	
	for (int i = 0; i < 8; i++)
	{
		m_Cube[i] = temp[i];
		m_Cube[i] += m_Center;
	}
	m_Formular[CTextureLibraray::TextureIndex::TOP].SetFormular(m_Cube[CubePos::RTB], m_Cube[CubePos::RTF], m_Cube[CubePos::LTF]);
	m_Formular[CTextureLibraray::TextureIndex::RIGHT].SetFormular(m_Cube[CubePos::RTF], m_Cube[CubePos::RTB], m_Cube[CubePos::RBB]);
	m_Formular[CTextureLibraray::TextureIndex::LEFT].SetFormular(m_Cube[CubePos::LTB], m_Cube[CubePos::LTF], m_Cube[CubePos::LBF]);
	m_Formular[CTextureLibraray::TextureIndex::FORWARD].SetFormular(m_Cube[CubePos::LTF], m_Cube[CubePos::RTF], m_Cube[CubePos::RBF]);
	m_Formular[CTextureLibraray::TextureIndex::BACK].SetFormular(m_Cube[CubePos::RTB], m_Cube[CubePos::LTB], m_Cube[CubePos::LBB]);
	m_Formular[CTextureLibraray::TextureIndex::BOTTOM].SetFormular(m_Cube[CubePos::LBB], m_Cube[CubePos::LBF], m_Cube[CubePos::RBF]);
}

void CCube::Rend_BB()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 0, 0, 0.2f);
	// À­¸é
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::TOP].Normal.arr);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glEnd();
	// ¿À¸¥ÂÊ¸é
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::RIGHT].Normal.arr);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glEnd();
	// ¿ÞÂÊ¸é
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::LEFT].Normal.arr);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glEnd();
	// ¾Õ¸é
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::FORWARD].Normal.arr);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glEnd();
	// µÞ¸é
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::BACK].Normal.arr);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glEnd();
	// ¾Æ·§¸é
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::BOTTOM].Normal.arr);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
}

void CCube::Rendering()
{
	glPushMatrix();
	glColor4f(1, 1, 1, 1);
	CTextureLibraray::UsingTexture2D();
	// À­¸é
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::TOP);
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::TOP].Normal.arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glEnd();
	// ¿À¸¥ÂÊ¸é
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::RIGHT);
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::RIGHT].Normal.arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glEnd();
	// ¿ÞÂÊ¸é
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::LEFT);
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::LEFT].Normal.arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glEnd();
	// ¾Õ¸é
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::FORWARD);
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::FORWARD].Normal.arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glEnd();
	// µÞ¸é
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::BACK);
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::BACK].Normal.arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glEnd();
	// ¾Æ·§¸é
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::BOTTOM);
	glBegin(GL_QUADS);
	glNormal3fv(m_Formular[CTextureLibraray::TextureIndex::BOTTOM].Normal.arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glEnd();
	CTextureLibraray::StopUsingTexture2D();
	glPopMatrix();
}

void CCube::Update(const float fTimeElapsed)
{
}

void CCube::Translate(Vec3f move)
{
	m_Center += move;
	for (int i = 0; i < 8; i++)
	{
		m_Cube[i] += move;
	}
	RotateInit();
}

void CCube::Rotate(float angle, bool x, bool y, bool z)
{
	glPushMatrix();
	glLoadIdentity();
	if (x) glRotatef(angle, 1.0f, 0.0f, 0.0f);
	if (y) glRotatef(angle, 0.0f, 1.0f, 0.0f);
	if (z) glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(m_matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);
	glPopMatrix();
	m_Angle.pitch += angle;
	m_Angle.yaw += angle;
	m_Angle.roll += angle;
	
	RotateInit();
}

void CCube::Scale(Vec3f scale)
{
	
	m_scale.x = scale.x;
	m_scale.y = scale.y;
	m_scale.z = scale.z;
	RotateInit();
}

bool CCube::isLineCollide(Vec3f * point)
{
	if (point == nullptr) return false;
	Vec3f startpoint = *(point - 1);
	Vec3f endpoint = *point;
	Vec3f dvec = endpoint - startpoint;
	Vec3f checkpoint = { 0.0f, 0.0f, 0.0f };
	Normalize(dvec);

	for (float t = 0.0f; t < Length(endpoint - startpoint); t += 0.1f)
	{
		checkpoint = startpoint + t*dvec;
		if (checkpoint.x < m_Center.x + (m_scale.x*1.4f+10.0f) &&
			checkpoint.x > m_Center.x - (m_scale.x*1.4f+10.0f) &&
			checkpoint.y < m_Center.y + (m_scale.y*1.4f+10.0f) &&
			checkpoint.y > m_Center.y - (m_scale.y*1.4f+10.0f) &&
			checkpoint.z < m_Center.z + (m_scale.z*1.4f+10.0f) &&
			checkpoint.z > m_Center.z - (m_scale.z*1.4f+10.0f))
			return true;
	}
	return false;
}

bool CCube::isPointCollide(Vec3f& point)
{
	if (point.x < m_Center.x + m_scale.x*1.4f &&
		point.x > m_Center.x - m_scale.x*1.4f &&
		point.y < m_Center.y + m_scale.y*1.4f &&
		point.y > m_Center.y - m_scale.y*1.4f &&
		point.z < m_Center.z + m_scale.z*1.4f &&
		point.z > m_Center.z - m_scale.z*1.4f)
		return true;
	return false;
}
