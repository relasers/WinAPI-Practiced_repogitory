// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "msimg32.lib" )

#include "inc/fmod.hpp"
#pragma comment (lib, "fmod64_vc.lib")

using namespace FMOD;

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h> // 메모리 -> iostream 에 들어있다
#include <memory.h> // 메모리 -> iostream 에 들어있다
#include <tchar.h> // 유니코드 함수 다수 포함
#include <time.h>
#include <mmsystem.h>
#include <atlimage.h>
#include "Resource.h"


#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 600
#define TEMP_ARR_SIZE 40
///// 창 크기 /////
#define WT_PLAYANIMATION 1
#define WT_KEYINPUTER 2
#define WT_UPDATER 3

#define THICK_OF_GROUND 50 // 땅의 두께
#define PLAYERSPEED 2.5 // 플레이어 속도
#define GRAVITY 0.5 // 중력
#define GRAVITY_ACCEL 0.1 //중력가속도
//<플레이어 관련 정의값들>/////////////////////
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 42
//////////////////////////////////////////////////
typedef enum {
	left,right
}Direction;

typedef enum {
	SD_Back,
	SD_SCR1,
	SD_SCR2,
	SD_END
}SOUND;


#include "SoundManager.h"
#include "SpriteImage.h"
#include "player.h"
#include "Platform.h"
#include "ObjectManager.h"
#include "framework.h"