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

#define THICK_OF_GROUND 16 // ���� �β�
#define NUM_PLATFORM 7 // �÷��� ��
#define PLAT_WIDTH 80 // �÷��� �ʺ�
#define PLAT_HEIGHT 16 // �÷��� ����
#define MX_DIST 80



#define PLAYERSPEED 2.5 // �÷��̾� �ӵ�
#define GRAVITY 0.7 // �߷�
#define GRAVITY_ACCEL 0.1 //�߷°��ӵ�
//<�÷��̾� ���� ���ǰ���>/////////////////////
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 42
#define PLAYER_JP_POWER 10

#define MX_LINE_LENGTH 150
//////////////////////////////////////////////////



///////////<�÷��� ��ġ��>///////////////////
#define PLAT_1 {360,150} // Ȧ�� (������)
#define PLAT_2 {120,60} // �¿�
#define PLAT_3 {700,100} // ����
#define PLAT_4 {500,200} // �¿�
#define PLAT_5 {200,200} // ����
#define PLAT_6 {180,300} // �¿�
#define PLAT_7 {600,250} // ����
#define PLAT_8 {70,470} // �ٱ���
#define PLAT_9 {400,470} // �ٱ���
/////////////////////////////////////////////////
#define BASK_LENGTH 150 // �ٱ��� ����
typedef enum {
	ITM_NULL,
	ITM_COIN,
	ITM_TREASURE,
	ITM_AMMO, 
}ITEM_ID;

typedef enum {
	left,right
}Direction;

typedef enum {
	SD_Back,
	SD_GETITEM,
	SD_PORTAL,
	SD_SCR1,
	SD_SCR2,
	SD_END
}SOUND;

typedef enum {
	holder, upsider, slider // ����, ���Ʒ�, �¿�
}PL_Status;

typedef enum {
	plus, minus
}PL_AC; // ������

#include "SoundManager.h"

extern CSoundManager soundM;
extern CImage brick;
#include "SpriteImage.h"


#include "player.h"
#include "Portal.h"
#include "Platform.h"
#include "Basket.h"
#include "Item.h"

#include "ObjectManager.h"
#include "framework.h"


