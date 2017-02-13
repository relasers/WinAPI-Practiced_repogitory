// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#include "targetver.h"
#include "Resource.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h> // �޸� -> iostream �� ����ִ�
#include <memory.h> // �޸� -> iostream �� ����ִ�
#include <tchar.h> // �����ڵ� �Լ� �ټ� ����
#include <iostream>
#include <math.h>
#include <time.h>
#include <mmsystem.h>

#define CLIENT_WIDTH 600
#define CLIENT_HEIGHT 660
#define GAME_BOARD_DEVIDE 14
#define BRICK_DEVIDE 8 // �� �� �� ��
#define TEMP_ARR_SIZE 40
#define CLEAR_GAME 400 // Ŭ���� ����
///// â ũ�� /////

#define WT_INSHOOINGBALL 1 // ���� ����
#define WT_MOV_BALL 2 // ���� �����δ�

#define BALL_SIZE 16 // �� ũ��
#define ITEM_SIZE 16 // ������ ������
#define BALL_SPEED 5.0 // �� �ӵ�

#define COLLISION_REFLECT 10 // �浹�� �ݻ��Ų��
#define BAR_Y_POS 10 // ���밡 ������ �Ʒ����� �� ������ �ִ���?

/////<������ ���̵�>////////////////////////
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
	Side, Updown, Point_LT, Point_LB, Point_RT, Point_RB , No // �¿�, ���Ʒ�, �𼭸�(�»�,����,���,����)
}Collision_Check;

typedef enum {
	More_X,More_Y,Same
}Point_Check;

typedef enum {
	NONE,SHOOTING,MOV_BALL,UPDATER,ANIMATION
}TIMER_MENU; // Ÿ�̸Ӹ޴�

typedef enum {
NO_MENU,GAME_MENU,Aiming_Phase,Shoot_Phase, Create_Brick_Phase,Calculating_Phase,GAME_END
}Phase;




// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
