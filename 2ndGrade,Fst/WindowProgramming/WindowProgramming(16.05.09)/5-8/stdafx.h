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
#include <malloc.h> // �޸� -> iostream �� ����ִ�
#include <memory.h> // �޸� -> iostream �� ����ִ�
#include <tchar.h> // �����ڵ� �Լ� �ټ� ����
#include <time.h>
#include "Resource.h"



#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 400
#define TEMP_ARR_SIZE 40
///// â ũ�� /////
#define WT_UPDATER 1
#define WT_YTORCUNTR 2 

#define TRAFFICORBSIZE 50

#define Color_RED 0
#define Color_YELLOW 1
#define Color_GREEN 2

typedef enum {
to_left,to_right
}Direction;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
