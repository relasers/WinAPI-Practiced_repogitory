#pragma once
class CPlayer;

class CCamera_OpenGL
{
public:
	enum class ProjectionType {
		Perspective
		, Ortho
	};
	enum class CameraViewMode {
		TPS
		, FPS
		, TOP
	};
private:
	HWND m_hWnd;

	int m_Client_Width;
	int m_Client_Height;

	double m_fovy;
	double m_aspect;
	double m_zNear;
	double m_zFar;
	double m_Zoom;

	Vec3f m_Angle;
	float m_Sensitivity;

	Vec3f m_Pos;
	Vec3f m_Look;
	Vec3f m_Up;

	CPlayer* m_Target;

	ProjectionType m_P_Type;
	CameraViewMode m_V_Type;

	bool m_bFixTarget;
	bool m_bShake;

public:
	CCamera_OpenGL(); 
	CCamera_OpenGL(HWND hWnd, const int client_width, const int client_height);
	~CCamera_OpenGL();

	void LookAt();
	void LookAt_IgnoreFar();

	void SetProjection(ProjectionType type) { m_P_Type = type; LookAt(); }
	void SetViewMode(CameraViewMode mode) { m_V_Type = mode; LookAt(); }
	void SetTarget(CPlayer* target) { m_Target = target; LookAt(); }
	void SetSensivity(const float sensitivity) { m_Sensitivity = sensitivity; LookAt(); }

	void FixTarget() { m_bFixTarget = true; LookAt(); }
	void ReleaseTarget() { m_bFixTarget = false; LookAt(); }

	void TranslatePos(const float side, const float up, const float forward);
	void RotateViewDirection(const int x, const int y);
	void ZoomScaling(const double scale, const bool smooth = false);
	void ShakeCamera(const float power, const bool axis_x = false, const bool axis_y = true);

	void Update(float fTimeElapsed);

	void Reset();

	const Vec3f& GetLookVec() const { return m_Look; }
};

