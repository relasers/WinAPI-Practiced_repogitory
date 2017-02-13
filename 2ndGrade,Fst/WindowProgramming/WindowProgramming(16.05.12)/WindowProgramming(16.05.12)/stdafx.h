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

#define CLIENT_WIDTH 1000
#define CLIENT_HEIGHT 800
#define TEMP_ARR_SIZE 40
///// â ũ�� /////
#define WT_COUNTING 1

#define GRIDNUM 20

#define BAR_SIZE 100 // �� ��
#define BAR_H_SIZE 8 // �� ����
#define BALL_SIZE 25 // �� ũ��
#define MX_SPEED 15
#define MN_SPEED 1
#define COLLISION_REFLECT 10 // �浹�� �ݻ��Ų��
#define N_BRICK_X 10 // �� �� ���� ��
#define N_BRICK_Y 2 // �� �� ���� ��
#define BRICK_H_SIZE 30 //���� ����

#define BAR_Y_POS 10 // ���밡 ������ �Ʒ����� �� ������ �ִ���?


typedef enum {
	Side, Updown, Point // �¿�, ���Ʒ�, �𼭸�
}Collision_Check;
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

typedef enum {
	red,blue,green
}Color;