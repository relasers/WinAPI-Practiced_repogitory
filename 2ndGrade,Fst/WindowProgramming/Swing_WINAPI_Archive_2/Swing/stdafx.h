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

#define THICK_OF_GROUND 16 // 땅의 두께
#define NUM_PLATFORM 7 // 플랫폼 수
#define PLAT_WIDTH 80 // 플랫폼 너비
#define PLAT_HEIGHT 16 // 플랫폼 높이
#define MX_DIST 80



#define PLAYERSPEED 2.5 // 플레이어 속도
#define GRAVITY 0.7 // 중력
#define GRAVITY_ACCEL 0.1 //중력가속도
//<플레이어 관련 정의값들>/////////////////////
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 42
#define PLAYER_JP_POWER 10

#define MX_LINE_LENGTH 150
//////////////////////////////////////////////////



///////////<플랫폼 위치들>///////////////////
#define PLAT_1 {360,150} // 홀딩 (시작점)
#define PLAT_2 {120,60} // 좌우
#define PLAT_3 {700,100} // 상하
#define PLAT_4 {500,200} // 좌우
#define PLAT_5 {200,200} // 상하
#define PLAT_6 {180,300} // 좌우
#define PLAT_7 {600,250} // 상하
#define PLAT_8 {70,470} // 바구니
#define PLAT_9 {400,470} // 바구니
/////////////////////////////////////////////////
#define BASK_LENGTH 150 // 바구니 길이
typedef enum {
	ITM_NULL,
	ITM_COIN,
	ITM_TREASURE,
	ITM_AMMO, 
}ITEM_ID;

typedef enum {
	left,right
}Direction;

typedef enum {
	SD_Back,
	SD_GETITEM,
	SD_PORTAL,
	SD_SCR1,
	SD_SCR2,
	SD_END
}SOUND;

typedef enum {
	holder, upsider, slider // 고정, 위아래, 좌우
}PL_Status;

typedef enum {
	plus, minus
}PL_AC; // 증감산

#include "SoundManager.h"

extern CSoundManager soundM;
extern CImage brick;
#include "SpriteImage.h"


#include "player.h"
#include "Portal.h"
#include "Platform.h"
#include "Basket.h"
#include "Item.h"

#include "ObjectManager.h"
#include "framework.h"


