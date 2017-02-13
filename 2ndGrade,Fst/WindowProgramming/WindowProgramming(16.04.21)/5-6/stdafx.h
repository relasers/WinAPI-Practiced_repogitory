// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<time.h>
#include "resource.h"


#define CLIENT_WIDTH 600
#define CLIENT_HEIGHT 600
#define IMAGE_SIZE 600

#define SHUFFLE_TIME 50 // ���� Ƚ��

#define WT_MOVINGPIECE 1
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

typedef enum {
	gameset,gameon,moving
}Game_Stat;

typedef enum {
	left,right,up,down
}Direction;