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
#include <math.h>
#include "Resource.h"

#define CLIENT_WIDTH 500
#define CLIENT_HEIGHT 400
#define TEMP_ARR_SIZE 40
///// â ũ�� /////
#define WT_COUNTING 1

#define MX_UD 100
#define MN_UD -100
typedef enum {
	sa,co,ta
}TriFun;
typedef enum {
	Re,Gr,Bl,END
}Col;

typedef enum{
	Inc,Dec
}CTSTAT;
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
extern class CFrameWork framework;