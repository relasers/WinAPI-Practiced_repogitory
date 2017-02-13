#pragma once
class CCube
{
private:
	CTextureLibraray *m_TextureLib;

	Vec3f m_Center;
	Vec3f m_Cube[8];
	SFormularf m_Formular[6];

	Scale3f m_scale; 
	Angle3f m_Angle;
	float m_matrix[16];

public:
	CCube();
	CCube(CTextureLibraray *texture);
	~CCube();

	void SetPos(Vec3f & pos);

	void RotateInit();
	void Rend_BB();

	void Rendering();
	void Update(const float fTimeElapsed);

	void Translate(Vec3f move);
	void Rotate(float angle, bool x, bool y, bool z);
	void Scale(Vec3f scale);

	bool isLineCollide(Vec3f * point);
	bool isPointCollide(Vec3f& point);

	const Vec3f GetCenter() const { return m_Center; }
	SFormularf* Get_SFormular() { return m_Formular; }
	Vec3f *Get_BB() { return m_Cube; }
};

