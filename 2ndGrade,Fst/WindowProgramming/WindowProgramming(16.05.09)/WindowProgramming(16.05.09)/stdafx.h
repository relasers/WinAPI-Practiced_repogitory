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

#define CLIENT_WIDTH 400
#define CLIENT_HEIGHT 400
#define TEMP_ARR_SIZE 40
///// â ũ�� /////
#define WT_COUNTING 1

#define MAX_OBSTACLE 8
#define MAX_OBSTACLE_SIZE 80

typedef enum {
	left, right, up, down
}Direction;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
