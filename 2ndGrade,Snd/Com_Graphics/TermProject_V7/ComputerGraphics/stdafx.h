// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// Set Console
//#if _DEBUG
#pragma comment (linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#endif

// Link lib
#pragma comment (lib, "winmm.lib")     /* link with Windows MultiMedia lib */
#pragma comment (lib, "opengl32.lib")  /* link with Microsoft OpenGL lib */
#pragma comment (lib, "glu32.lib")     /* link with OpenGL Utility lib */

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <chrono>
#include <string>
#include <list>
#include <thread>

// C 런타임 헤더 파일입니다.
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>

// 추가 포함 라이브러리 헤더입니다.
#include "SoundManager.h"
#include "Vec2f.h"
#include "Vector3D.h"
#include "DataStructure3D.h"
#include "Camera_OpenGL.h"
#include "Light.h"
#include "TextureLib.h"
#include "Cube.h"
#include "Player.h"
#include "Boss.h"
#include "Enemy.h"

#include "Bullet.h"
#include "EnergyBolt.h"

#include "Launcher.h"
#include "BossLauncher.h"

#include "Particle.h"

#include "Surface.h"


// 클라이언트 윈도우 크기 설정
#define CLIENT_WIDTH 1200
#define CLIENT_HEIGHT 768

// 윈도우 캡션 타이틀 설정
#define TITLE_MX_LENGTH 64
#define TITLESTRING	TEXT("C.A.D")

// 캡션 FPS 출력 여부 -------------------
// 항상 캡션에 FPS를 출력		(0 : 비활성 | 1 : 활성)
#define USE_CAPTIONFPS_ALWAYS	 1

#if USE_CAPTIONFPS_ALWAYS
#define SHOW_CAPTIONFPS 
#elif _DEBUG	// Debug에서는 항상 실행
#define SHOW_CAPTIONFPS 
#endif

#if defined(SHOW_CAPTIONFPS)
#define MAX_UPDATE_FPS 1.0 / 3.0
#endif

// 최대 FPS
#if _DEBUG
#define MAX_FPS 0.0
#else
#define MAX_FPS 1.0 / 60.0
#endif

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#define DIR_FORWARD					0x01
#define DIR_BACKWARD				0x02
#define DIR_LEFT					0x04
#define DIR_RIGHT					0x08
#define DIR_UP						0x10
#define DIR_DOWN					0x20

// MapSize
#define MapSize 0x1000

#define PolySize 80
#define LineWidth 100
#ifndef PI
#define PI 3.14159265f
#endif
#define ForceOfShear 40
#define degree_per_one_radius 57.29577951471995f
#define radius_per_one_degree 0.0174532925f;

#define HitTime 3.0f
#define BarrierRepair 1.0f