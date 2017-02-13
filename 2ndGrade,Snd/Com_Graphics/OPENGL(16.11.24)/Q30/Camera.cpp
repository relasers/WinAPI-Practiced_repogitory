#include "Camera.h"
#include <gl/glut.h>


CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

void CCamera::Rander()
{
	glLoadIdentity(); // 카메라 적용전 초기화

					//기하와 벡터 구의 방정식 참조

	gluLookAt(m_Eye.x, m_Eye.y, m_Eye.z,	// Eye
			0.0, 0.0, 0.0,					// At
			m_Up.x, m_Up.y, m_Up.z);		// Up
}

bool CCamera::Update()
{

	switch (m_phase) {
	case Phase::Closer:
		m_distance++;
		if (m_distance > -200) {
			(++m_phase) %= Phase::Counter;
		}
		break;
	case Phase::Rotate1:
	case Phase::Rotate2:
	case Phase::Rotate3:
	case Phase::Rotate4:
		m_camera_angle.x++;
		if (m_camera_angle.x >= 360) 
		{
			m_camera_angle.x = 0;
			(++m_phase) %= Phase::Counter;
		}
		break;
	case Phase::FarAway:
		m_distance--;
		if (m_distance < -1000) {
			(++m_phase) %= Phase::Counter;
		}
		break;
	
	}

		//(++m_camera_angle.x) %= 360;
		m_Eye.x = m_distance * -sinf(m_camera_angle.x*(PI / 180)) * cosf((m_camera_angle.y)*(PI / 180));
		m_Eye.y = 60;
		m_Eye.z = -m_distance * cosf((m_camera_angle.x)*(PI / 180)) * cosf((m_camera_angle.y)*(PI / 180));

		if (90 < m_camera_angle.y && m_camera_angle.y < 270
			) {
			m_Up.y = -1;
		}
		else
		{
			m_Up.y = 1;
		}
	return true;
}

void CCamera::KeyInput(unsigned char key, int x, int y)
{
	if (key == 'l' || key == 'L') {
		HandlePosition(Camera_Speed, { 1,0,0 });
	}
	if (key == 'j' || key == 'J') {
		HandlePosition(-Camera_Speed, { 1,0,0 });
	}
	if (key == 'i' || key == 'I') {
		HandlePosition(Camera_Speed, { 0,1,0 });
	}
	if (key == 'k' || key == 'K') {
		HandlePosition(-Camera_Speed, { 0,1,0 });
	}
	if (key == 'u' || key == 'U') {
		HandlePosition(Camera_Speed, { 0,0,1 });
	}
	if (key == 'o' || key == 'O') {
		HandlePosition(-Camera_Speed, { 0,0,1 });
	}
	if (key == '+') {
		HandleDistance(10);
	}
	if (key == '-') {
		HandleDistance(-10);
	}
	if (key == 'r' || key == 'R') {
		ResetPos();
	}
}

void CCamera::ResetPos()
{
	m_camera_angle = { 0,0,0 };
	m_distance = -300;
}

void CCamera::HandleDistance(int distance)
{
	m_distance += distance;
}

void CCamera::HandlePosition(int angle, Vec3i axis)
{
	m_camera_angle += axis*angle;

	if (m_camera_angle.x < 0) m_camera_angle.x += 360;
	if (m_camera_angle.y < 0) m_camera_angle.y += 360;
	if (m_camera_angle.z < 0) m_camera_angle.z += 360;

	m_camera_angle.x %= 360;
	m_camera_angle.y %= 360;
	m_camera_angle.z %= 360;
}
