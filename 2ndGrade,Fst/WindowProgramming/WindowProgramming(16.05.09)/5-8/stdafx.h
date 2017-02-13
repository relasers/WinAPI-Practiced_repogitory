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
#include "Resource.h"



#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 400
#define TEMP_ARR_SIZE 40
///// 창 크기 /////
#define WT_UPDATER 1
#define WT_YTORCUNTR 2 

#define TRAFFICORBSIZE 50

#define Color_RED 0
#define Color_YELLOW 1
#define Color_GREEN 2

typedef enum {
to_left,to_right
}Direction;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
