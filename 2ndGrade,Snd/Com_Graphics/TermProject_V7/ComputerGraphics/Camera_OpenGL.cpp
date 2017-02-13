#include "stdafx.h"

#include "Camera_OpenGL.h"


CCamera_OpenGL::CCamera_OpenGL()
{
	
}

CCamera_OpenGL::CCamera_OpenGL(HWND hWnd, const int client_width, const int client_height)
{
	m_hWnd = hWnd;

	m_Client_Width = client_width;
	m_Client_Height = client_height;

	m_fovy = 50.0f;
	m_aspect = static_cast<double>(m_Client_Width) / static_cast<double>(m_Client_Height);

	m_zNear = 1.0f;
	m_zFar = 3000.0f;
	m_Zoom = 1.0f;
	

	m_Angle = { 0.0f, PI * 0.5f, 0.0f };
	m_Sensitivity = 2.0f;

	m_Pos = { 0.0f, 1000.0f, -1024.0f };
	m_Look = { 0.0f, 0.0f, 1.0f };
	m_Up = { 0.0f, 1.0f, 0.0f };

	m_Target = nullptr;

	m_P_Type = ProjectionType::Perspective;
	m_V_Type = CameraViewMode::TPS;

	m_bFixTarget = false;
	m_bShake = false;
}

CCamera_OpenGL::~CCamera_OpenGL()
{
}

void CCamera_OpenGL::LookAt()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (m_P_Type == ProjectionType::Perspective)
	{
		gluPerspective(m_fovy / m_Zoom, m_aspect, m_zNear, m_zFar);

		if (m_bFixTarget) {
			Vec3f pos = m_Target->GetCenter();
			gluLookAt(
				m_Pos.x, m_Pos.y, m_Pos.z,
				pos.x, pos.y, pos.z,
				m_Up.x, m_Up.y, m_Up.z);
		}
		else
		{
			if (m_V_Type == CameraViewMode::TPS)
			{
				Vec3f pos = (m_Target->GetCenter()) - 200.0f*m_Look;
				pos.y += 50.0f;
				gluLookAt(
					pos.x, pos.y, pos.z,
					pos.x + m_Look.x, pos.y + m_Look.y, pos.z + m_Look.z,
					m_Up.x, m_Up.y, m_Up.z);
			}
			else if (m_V_Type == CameraViewMode::FPS)
			{
				Vec3f pos = (m_Target->GetCenter()) + 7.0f*m_Look;
				gluLookAt(
					pos.x, pos.y, pos.z,
					pos.x + m_Look.x, pos.y + m_Look.y, pos.z + m_Look.z,
					m_Up.x, m_Up.y, m_Up.z);
			}
			//gluLookAt(
			//	m_Pos.x, m_Pos.y, m_Pos.z,
			//	m_Pos.x + m_Look.x, m_Pos.y + m_Look.y, m_Pos.z + m_Look.z,
			//	m_Up.x, m_Up.y, m_Up.z);
		}
	}
	else if (m_P_Type == ProjectionType::Ortho)
	{
		glOrtho(-MapSize / 2, MapSize / 2, -MapSize / 2, MapSize / 2, -MapSize / 2, MapSize / 2);
		m_Pos = {0.0f, 0.0f, 0.0f};
		m_Angle.x = 0.0f;
		m_Angle.y = PI / 2.0f;
		m_Look = { cosf(m_Angle.y), tanf(m_Angle.x), sinf(m_Angle.y) };
		Normalize(m_Look);

		gluLookAt(
				m_Pos.x, 100, m_Pos.z,
				m_Pos.x + m_Look.x, m_Pos.y + 1, m_Pos.z + m_Look.z,
				m_Up.x, m_Up.y, m_Up.z);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CCamera_OpenGL::LookAt_IgnoreFar()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (m_P_Type == ProjectionType::Perspective)
	{
		gluPerspective(m_fovy / m_Zoom, m_aspect, m_zNear, 10000.0f);

		if (m_bFixTarget) {
			Vec3f pos = m_Target->GetCenter();
			gluLookAt(
				m_Pos.x, m_Pos.y, m_Pos.z,
				pos.x, pos.y, pos.z,
				m_Up.x, m_Up.y, m_Up.z);
		}
		else gluLookAt(
			m_Pos.x, m_Pos.y, m_Pos.z,
			m_Pos.x + m_Look.x, m_Pos.y + m_Look.y, m_Pos.z + m_Look.z,
			m_Up.x, m_Up.y, m_Up.z);
	}
	else if (m_P_Type == ProjectionType::Ortho)
	{
		glOrtho(-MapSize / 2, MapSize / 2, -MapSize / 2, MapSize / 2, -MapSize / 2, MapSize / 2);
		m_Angle.x = 0.0f;
		m_Angle.y = PI / 2.0f;
		m_Look = { cosf(m_Angle.y), tanf(m_Angle.x), sinf(m_Angle.y) };
		Normalize(m_Look);

		gluLookAt(
			m_Pos.x, 100, m_Pos.z,
			m_Pos.x + m_Look.x, m_Pos.y + 1, m_Pos.z + m_Look.z,
			m_Up.x, m_Up.y, m_Up.z);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CCamera_OpenGL::TranslatePos(const float side, const float up, const float forward)
{
	m_Pos += m_Look * forward;
	m_Pos.y += up;
	m_Pos += { sinf(m_Angle.y)*side, 0.0f, -cosf(m_Angle.y)*side };
	LookAt();
	if(m_Target != nullptr)
		m_Target->SetPos(m_Pos);
}

void CCamera_OpenGL::RotateViewDirection(const int x, const int y)
{	
	if (m_P_Type == ProjectionType::Ortho) return;
	if (m_Client_Width / 2 + 1 < x)
	{
		m_Angle.y += m_Sensitivity * radius_per_one_degree;
	}
	else if (m_Client_Width / 2 - 1 > x)
	{
		m_Angle.y -= m_Sensitivity * radius_per_one_degree;
	}
	if (m_Client_Height / 2 + 1 < y)
	{
		m_Angle.x -= m_Sensitivity * radius_per_one_degree;
	}
	else if (m_Client_Height / 2 - 1> y)
	{
		m_Angle.x += m_Sensitivity * radius_per_one_degree;
	}
	if (m_Angle.x > (PI / 2.0f) - (PI / 18.0f)) m_Angle.x = (PI / 2.0f) - (PI / 18.0f);
	else if (m_Angle.x < -(PI / 2.0f) + (PI / 18.0f)) m_Angle.x = -(PI / 2.0f) + (PI / 18.0f);
	m_Look = { cosf(m_Angle.y), tanf(m_Angle.x), sinf(m_Angle.y) };
	Normalize(m_Look);
	LookAt();
	if (m_Target != nullptr)
	{
		m_Target->RotateToDirection(m_Look, m_Angle);
		m_Target->SetPos(m_Pos);
	}
}

void CCamera_OpenGL::ZoomScaling(const double scale, const bool smooth)
{
	if(smooth) m_Zoom += scale;
	else m_Zoom = scale;
	LookAt();
}

void CCamera_OpenGL::ShakeCamera(const float power, const bool axis_x, const bool axis_y)
{
	LookAt();
}

void CCamera_OpenGL::Update(float fTimeElapsed)
{
	if (m_P_Type == ProjectionType::Ortho) return;
	POINT point{0,0};
	ClientToScreen(m_hWnd, &point);
	SetCursorPos(point.x + (m_Client_Width / 2), point.y + (m_Client_Height / 2));
}

void CCamera_OpenGL::Reset()
{

	m_fovy = 50.0f;
	m_aspect = static_cast<double>(m_Client_Width) / static_cast<double>(m_Client_Height);

	m_zNear = 1.0f;
	m_zFar = 3000.0f;
	m_Zoom = 1.0f;


	m_Angle = { 0.0f, PI * 0.5f, 0.0f };
	m_Sensitivity = 2.0f;

	m_Pos = { 0.0f, 1000.0f, -1024.0f };
	m_Look = { 0.0f, 0.0f, 1.0f };
	m_Up = { 0.0f, 1.0f, 0.0f };

	m_Target = nullptr;

	m_P_Type = ProjectionType::Perspective;
	m_V_Type = CameraViewMode::TPS;

	m_bFixTarget = false;
	m_bShake = false;
}
