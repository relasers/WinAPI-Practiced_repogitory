// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#include "targetver.h"
#include "Resource.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h> // 메모리 -> iostream 에 들어있다
#include <memory.h> // 메모리 -> iostream 에 들어있다
#include <tchar.h> // 유니코드 함수 다수 포함
#include <iostream>
#include <math.h>
#include <time.h>
#include <mmsystem.h>

#define CLIENT_WIDTH 600
#define CLIENT_HEIGHT 660
#define GAME_BOARD_DEVIDE 14
#define BRICK_DEVIDE 8 // 한 행 셀 수
#define TEMP_ARR_SIZE 40
#define CLEAR_GAME 400 // 클리어 조건
///// 창 크기 /////

#define WT_INSHOOINGBALL 1 // 공을 쏘자
#define WT_MOV_BALL 2 // 공이 움직인다

#define BALL_SIZE 16 // 공 크기
#define ITEM_SIZE 16 // 아이템 사이즈
#define BALL_SPEED 5.0 // 공 속도

#define COLLISION_REFLECT 10 // 충돌시 반사시킨다
#define BAR_Y_POS 10 // 막대가 윈도우 아래에서 얼마 떨어져 있는지?

/////<아이템 아이디>////////////////////////
#define ITEM_NOTHING 0
#define ITEM_PLUS_BALL 1
#define ITEM_CHANGE_BALL_DIR 2
#define ITEM_DEBUFF 3
////////////////////////////////////
#define COLOR_RED (255,0,0)
#define COLOR_GREEN (0,255,0)
#define COLOR_BLUE (0,0,255)

///////////////////////////////
typedef enum {
	Side, Updown, Point_LT, Point_LB, Point_RT, Point_RB , No // 좌우, 위아래, 모서리(좌상,좌하,우상,우하)
}Collision_Check;

typedef enum {
	More_X,More_Y,Same
}Point_Check;

typedef enum {
	NONE,SHOOTING,MOV_BALL,UPDATER,ANIMATION
}TIMER_MENU; // 타이머메뉴

typedef enum {
NO_MENU,GAME_MENU,Aiming_Phase,Shoot_Phase, Create_Brick_Phase,Calculating_Phase,GAME_END
}Phase;




// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
