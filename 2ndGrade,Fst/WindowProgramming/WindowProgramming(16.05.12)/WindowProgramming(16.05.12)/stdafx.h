// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

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
#include <math.h>

#include "Resource.h"

#define CLIENT_WIDTH 1000
#define CLIENT_HEIGHT 800
#define TEMP_ARR_SIZE 40
///// 창 크기 /////
#define WT_COUNTING 1

#define GRIDNUM 20

#define BAR_SIZE 100 // 바 폭
#define BAR_H_SIZE 8 // 바 높이
#define BALL_SIZE 25 // 공 크기
#define MX_SPEED 15
#define MN_SPEED 1
#define COLLISION_REFLECT 10 // 충돌시 반사시킨다
#define N_BRICK_X 10 // 한 행 벽돌 수
#define N_BRICK_Y 2 // 한 열 벽돌 수
#define BRICK_H_SIZE 30 //벽돌 높이

#define BAR_Y_POS 10 // 막대가 윈도우 아래에서 얼마 떨어져 있는지?


typedef enum {
	Side, Updown, Point // 좌우, 위아래, 모서리
}Collision_Check;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

typedef enum {
	red,blue,green
}Color;