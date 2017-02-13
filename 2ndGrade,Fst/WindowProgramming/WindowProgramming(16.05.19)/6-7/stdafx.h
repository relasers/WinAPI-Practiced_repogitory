// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "msimg32.lib" )

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h> // �޸� -> iostream �� ����ִ�
#include <memory.h> // �޸� -> iostream �� ����ִ�
#include <tchar.h> // �����ڵ� �Լ� �ټ� ����
#include <time.h>

#define CLIENT_WIDTH 1000
#define CLIENT_HEIGHT 800
#define TEMP_ARR_SIZE 40
///// â ũ�� /////
#define WT_COUNTING 1

typedef enum {
	Tiling,Objecting
}Mode;


#include "Resource.h"
#include "Tiles.h"
#include "OBJ.h"
#include "BackGround.h"
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
extern class CFrameWork framework;