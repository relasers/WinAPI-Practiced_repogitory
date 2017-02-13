#pragma once

class C_M_HexTechTower
{
private:
	float m_radius{128};
	float m_height{1024};

	Vec3f m_gray{ 0.5f,0.5f,0.5f };
	Vec3f m_specref{ 1.0f,1.0f,1.0f };

	float m_gearangle{};

public:
	enum class CubePos {
		LTF = 0
		, LTB
		, RTF
		, RTB
		, LBF
		, LBB
		, RBF
		, RBB
	};
public:
	C_M_HexTechTower();
	~C_M_HexTechTower();

	virtual bool Update(const float fTimeElapsed);
	virtual void Rander();

	void RandColumns();
	void RandWallGears();
};

