// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "msimg32.lib" )

#include "inc/fmod.hpp"
#pragma comment (lib, "fmod64_vc.lib")

using namespace FMOD;

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
#include <mmsystem.h>
#include <atlimage.h>
#include "Resource.h"


#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 600
#define TEMP_ARR_SIZE 40
///// â ũ�� /////
#define WT_PLAYANIMATION 1
#define WT_KEYINPUTER 2
#define WT_UPDATER 3

#define THICK_OF_GROUND 50 // ���� �β�
#define PLAYERSPEED 2.5 // �÷��̾� �ӵ�
#define GRAVITY 0.5 // �߷�
#define GRAVITY_ACCEL 0.1 //�߷°��ӵ�
//<�÷��̾� ���� ���ǰ���>/////////////////////
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 42
//////////////////////////////////////////////////
typedef enum {
	left,right
}Direction;

typedef enum {
	SD_Back,
	SD_SCR1,
	SD_SCR2,
	SD_END
}SOUND;


#include "SoundManager.h"
#include "SpriteImage.h"
#include "player.h"
#include "Platform.h"
#include "ObjectManager.h"
#include "framework.h"