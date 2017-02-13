#include "stdafx.h"
#include "ObjectManager.h"


void CObjectManager::init(RECT m_rect)
{
	srand((unsigned)time(NULL));

	RECT groundinit = {0,m_rect.bottom-THICK_OF_GROUND,m_rect.right,m_rect.bottom}; // µû¾Ó ÃÊ±âÈ­
	POINT settingpt = {m_rect.right/2,120};
	ground.setpos(groundinit);
	player.setpos(settingpt);

	for (int i = 0; i < NUM_PLATFORM+2; ++i) {
		POINT x;
		switch (i) {
		case 0:
			x = PLAT_1;
			break;
		case 1:
			x = PLAT_2;
			break;
		case 2:
			x = PLAT_3;
			break;
		case 3:
			x = PLAT_4;
			break;
		case 4:
			x = PLAT_5;
			break;
		case 5:
			x = PLAT_6;
			break;
		case 6:
			x = PLAT_7;
			break;
		case 7:
			x = PLAT_8;
			break;
		case 8:
			x = PLAT_9;
			break;
		}
		platform[i].placpos(x);
		if (i != 0) {
			platform[i].initdir(i,0);
		}
	}
	settingpt = { 70,groundinit.top - 64 };
	basket[0].init(settingpt);
	settingpt = { 400,groundinit.top - 64 };
	basket[1].init(settingpt);

	settingpt = { m_rect.right/2,groundinit.top - 80 };
	portal.init(settingpt); // Æ÷Å» ÃÊ±âÈ­

	settingpt = {0,0};
	item_head = new CItem();
	score =0;
	
	auto p = item_head;
	for(int i = 0; i < 8; ++i) {
		settingpt = {PLAT_WIDTH/2,-PLAT_HEIGHT};
		if (i < 6) {
			int x = rand() % 2;
			if(x==0)
				p->next = new CItem (settingpt,ITEM_ID::ITM_COIN,i+1);
			else
				p->next = new CItem (settingpt, ITEM_ID::ITM_AMMO, i + 1);
		}
		else {
			settingpt = { BASK_LENGTH / 2,-PLAT_HEIGHT };
		p->next = new CItem(settingpt, ITEM_ID::ITM_TREASURE, i + 1);
		}
		p = p->next;
	}

}

void CObjectManager::Play_Obj_Sprite()
{
	player.play_spr();
	portal.play_spr();

	auto p = item_head->next;
	while(p!=nullptr) {
		p->play_spr();
		p = p->next;
	}
}

void CObjectManager::Obj_Updater(RECT m_rect)
{
	player.Updater();
	player.setcollisioned(false);

	
	RECT COLLISION_CHECK;

	if (!player.getisspin())
	if (IntersectRect(&COLLISION_CHECK, &player.getpos(), &ground.getpos())) {
		soundM.PlaySnd(SD_SCR2);
		init(m_rect);
	}
	

	if(!player.getisspin())
	player.portalcheck(portal,m_rect);
	for (int i = 0; i < 2; ++i) {
		basket[i].updater();
		for (int j = 0; j < 3; ++j) {
			if (!player.getisspin())
			player.collisioncheck(basket[i].getplat(j), m_rect);
		}
	}


	for (int i = 0; i < NUM_PLATFORM+2; ++i) {
		platform[i].moving();
		if (6 >= i)
			if (!player.getisspin())
				player.collisioncheck(platform[i], m_rect);
	}

	auto p = item_head->next;
	while (p != nullptr) {
		if (!player.getisspin())
		score += p->collisioncheck(player, m_rect, platform[p->getPlatid()].getpos());
		p = p->next;
	}

	p = item_head;
	bool isdeleted = false;
	while (p->next != nullptr) {
		if (p->next->gethp() == 0) {
			auto tempNode = new CItem();
			tempNode->next = p->next->next;
			p->next = tempNode->next;
			free(tempNode);
			p = item_head;
			isdeleted = true;
		}
		p = p->next;

		if (isdeleted == true) {
			p = item_head;
			isdeleted = false;
		}
	}



	if (player.getcollisioned() == false) {
		player.setflying(true);
	}


}

void CObjectManager::Obj_RT_Key_Input(bool iskeydown) {
	player.ActonKey(iskeydown);
}

void CObjectManager::Obj_NORM_Key_Input(WPARAM)
{

}

bool CObjectManager::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam, bool iskeydown)
{
	switch (iMessage) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_SPACE:
			player.spincont();
			break;
		case VK_LEFT:
		case VK_RIGHT:
			if (iskeydown == false)
				player.reset_spr();
			break;
		}
	

		return true;
		break;
	case WM_KEYUP:
		iskeydown = false;
		switch (wParam) {
		case VK_LEFT:
		case VK_RIGHT:
			player.reset_spr();
			player.setstance(PStance::stand);
		}
		break;
	}
}

void CObjectManager::Draw(HDC hdc,RECT m_rect) {
	player.draw(hdc,m_rect);
	ground.draw(hdc, m_rect);
	portal.draw(hdc,m_rect);
	for (int i = 0; i < NUM_PLATFORM; ++i) {
		platform[i].draw(hdc, m_rect);
	}
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			basket[i].getplat(j).draw(hdc, m_rect);
		}
	}
	
	auto p = item_head->next;
	while (p != nullptr) {
		p->draw(hdc,m_rect,platform[p->getPlatid()].getpos());
		p = p->next;
	}
	SetBkMode(hdc,TRANSPARENT);
	SetTextColor(hdc,RGB(0,255,50));
	wsprintf(temp,TEXT("Score : %d"),score);
	DrawText(hdc,temp,-1,&m_rect,DT_CENTER);

}

CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}
