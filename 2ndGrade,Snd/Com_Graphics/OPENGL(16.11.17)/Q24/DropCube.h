#pragma once
#include"Vec3D.h"

class CDropCube
{
private:
	Vec3f m_pt{0.0f,0.0f,0.0f};
	Vec3f m_mvector{ 0.0f,0.0f,0.0f };
	Vec3f m_color{};
	int m_size{};

	float m_speed = 4.0f;
public:
	CDropCube();
	CDropCube(int size,int depth,Vec3f Color);
	~CDropCube();

	void Rander();
	void Update();
	void SetDirection(int x);
	void CollisionCheck(int cubesize);
};

