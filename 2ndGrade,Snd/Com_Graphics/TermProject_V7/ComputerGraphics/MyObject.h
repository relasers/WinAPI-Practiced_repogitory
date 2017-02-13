#pragma once
class CMyObject
{
protected:
	Vec3f m_vCenter;
	Vec3f m_Angle;

	float m_fRotateMatrix[16];

	bool m_bDie = false;

public:
	CMyObject();
	~CMyObject();

	virtual void Update(const float fTimeElapsed) = 0;
	virtual void Rendering() = 0;

	virtual void Translate(const Vec3f move) { m_vCenter += move; }
	virtual void Rotate(const float angle, bool x, bool y, bool z);

	Vec3f& GetCenter() { return m_vCenter; }
	bool IsDie() const { return m_bDie; }
};

