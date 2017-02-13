#include "stdafx.h"

#include "Framework.h"
#include "M_Sky.h"
#include "MainScene.h"
#include "RanderProp.h"
using namespace std;

CMainScene::CMainScene()
{
}
CMainScene::~CMainScene()
{
	delete m_Sky;
	delete m_Player;
	delete m_Boss;
	delete m_Bottom;
	m_Immune = 0.0f;
	m_ObstarcleList.clear();
	m_bullets.clear();
	m_ally_bullets.clear();
	m_energybolts.clear();
	m_particles.clear();
	m_EnemyList.clear();
	m_pCamera->Reset();
	m_bGameClear = false;
	m_bGameOver = false;
}

void CMainScene::DrawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void CMainScene::SettingLight()
{
	m_pLight->LightOn(CLight::LightTag::Light0);
	m_pLight->SetLightAmbient(CLight::LightTag::Light0, 0.35f, 0.35f, 0.35f);
	m_pLight->SetLightDiffuse(CLight::LightTag::Light0, 1.0f, 1.0f, 1.0f);
	m_pLight->SetLightSpecular(CLight::LightTag::Light0, 1.0f, 1.0f, 1.0f);
	m_pLight->SetLightPosition(CLight::LightTag::Light0, 1.0f, 1024.0f, 1.0f);
}

void CMainScene::SettingObjects()
{
	// 하늘 생성
	m_Sky = new CM_Sky(m_TextureLib,*m_pCamera);
	// 바닥 생성
	m_Bottom = new CSurface(m_TextureLib);
	m_Bottom->SetScale(MapSize, 10, MapSize);
	// 플레이어 기체 생성
	m_Player = new CPlayer(m_ally_bullets);
	m_pCamera->SetTarget(m_Player);
	// 적기체 생성
	for (int i =0; i < InitEnemyNum; i++)
		m_EnemyList.push_back(new CEnemy(Vec3f{0.0f, 0.0f, 0.0f}, m_Player,m_bullets));
	// 보스 생성
	m_Boss = new CBoss(m_Player,m_bullets,m_energybolts, m_EnemyList);
	// 장애물 생성
	for (int i = 0; i < ObstarcleNum; i++)
		m_ObstarcleList.push_back(new CCube(m_TextureLib));
	m_ObstarcleList.remove_if([](CCube* p)->bool {return Length(p->GetCenter()) >(MapSize * 0.5f); });
	m_ObstarcleList.remove_if([&](CCube* p)->bool {return CollideCheck(m_Boss->Get_BindCube(), *p); });
}

bool CMainScene::CollideCheck(CCube& a, CCube& b)
{
	SFormularf* a_f = a.Get_SFormular();
	Vec3f* b_bb = b.Get_BB();

	for (int i = 0; i < 8; i++)
	{
		int inside = 0;
		for (int j = 0; j < 6; j++)
		{
			if (a_f[j].isCollide(b_bb[i]))
			{
				inside++;
			}
		}
		if (inside == 6)
			return true;
	}
	return false;
}

void CMainScene::Reset()
{
	m_Immune = 0.0f;
	delete m_Sky;
	delete m_Player;
	delete m_Boss;
	delete m_Bottom;
	m_ObstarcleList.clear();
	m_bullets.clear();
	m_ally_bullets.clear();
	m_energybolts.clear();
	m_particles.clear();
	m_EnemyList.clear();
	m_pCamera->Reset();
	m_bGameClear = false;
	m_bGameOver = false;
	SettingObjects();
}

void CMainScene::Update(float fTimeElapsed)
{
	ProcessInput(); 
	m_SoundManager->Update(fTimeElapsed);
	m_EnemyList.remove_if([](CEnemy* p)->bool {return p->IsDie(); });
	m_ally_bullets.remove_if([](Cbullet* p)->bool {return p->IsDie(); });
	m_energybolts.remove_if([](CEnergyBolt* p)->bool {return p->IsDie(); });
	m_bullets.remove_if([](Cbullet* p)->bool {return  p->IsDie(); });
	m_particles.remove_if([](CParticle* p)->bool {return  p->IsDie(); });

	std::thread th1{ [&]() {
		m_pCamera->Update(fTimeElapsed);
		float speed = m_Player->GetSpeed();
		if (m_bFront) m_pCamera->TranslatePos(0.0f, 0.0f, speed*fTimeElapsed);
		if (m_bBack) m_pCamera->TranslatePos(0.0f, 0.0f, -speed*fTimeElapsed);
		if (m_bLeft) m_pCamera->TranslatePos(speed*fTimeElapsed, 0.0f, 0.0f);
		if (m_bRight) m_pCamera->TranslatePos(-speed*fTimeElapsed, 0.0f, 0.0f);
		m_Sky->Update(fTimeElapsed);
		m_Player->Update(fTimeElapsed);
		m_Boss->Update(fTimeElapsed);
		if (CollideCheck(m_Boss->Get_BindCube(), m_Player->Get_BindCube()))
		{
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Die_P);
			m_Player->CollideEnv();
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
		}
		if (CollideCheck(m_Boss->Get_CoreBindCube(), m_Player->Get_BindCube()))
		{
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Die_P);
			m_Player->CollideEnv();
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
		}
		if (CollideCheck(m_Boss->Get_RoofBindCube(), m_Player->Get_BindCube()))
		{
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Die_P);
			m_Player->CollideEnv();
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
		}
		if (Length(m_Player->GetCenter()) > MapSize / 2 || m_Player->GetCenter().y < 20.0f)
		{
			m_Player->CollideEnv();
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Die_P);
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
		}
		for (auto &p : m_EnemyList) {
			p->Update(fTimeElapsed);
			if (Length(p->GetCenter()) > MapSize / 2 || p->GetCenter().y < 20.0f)
			{
				m_SoundManager->PlaySnd_Enemy(CSoundManager::ENEMY_SOUND::Enemy_Die);
				p->CollideEnv();
				m_particles.push_back(new CParticle(p->GetCenter()));
				m_particles.push_back(new CParticle(p->GetCenter()));
				m_particles.push_back(new CParticle(p->GetCenter()));
			}
			if (CollideCheck(p->Get_BindCube(), m_Player->Get_BindCube())) {
				p->CollideEnv();
				m_SoundManager->PlaySnd_Enemy(CSoundManager::ENEMY_SOUND::Enemy_Die);
				m_Player->Hit(100);
				m_particles.push_back(new CParticle(p->GetCenter()));
				m_particles.push_back(new CParticle(p->GetCenter()));
				m_particles.push_back(new CParticle(p->GetCenter()));
			}
		}
		for (auto &p : m_energybolts) {
			p->Update(fTimeElapsed);
			if (Length(p->GetCenter()) > MapSize / 2 || p->GetCenter().y < 20.0f)
			{
				p->Collide();
				m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
				m_particles.push_back(new CParticle(p->GetCenter()));
			}
			if (CollideCheck(m_Player->Get_BindCube(), p->Get_BindCube())) {
				m_particles.push_back(new CParticle(p->GetCenter()));
				m_SoundManager->PlaySnd_Enemy(CSoundManager::ENEMY_SOUND::Enemy_Die);
				p->Collide();
				m_Player->Hit(10);
				m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Hit_P);
			}
		}
	} };
	std::thread th2{ [&]() {
	for (auto p : m_ObstarcleList)
	{
		if (CollideCheck(*p, m_Player->Get_BindCube()))
		{
			m_Player->CollideEnv();
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Die_P);
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
		}
		for (auto &q : m_bullets) {
			if (CollideCheck(*p, q->Get_BindCube()))
			{
				q->Collide();
				m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
				m_particles.push_back(new CParticle(q->GetCenter()));
			}
		}
		for (auto &q : m_energybolts) {
			if (CollideCheck(*p, q->Get_BindCube()))
			{
				q->Collide();
				m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
				m_particles.push_back(new CParticle(q->GetCenter()));
			}
		}
		for (auto &q : m_ally_bullets) {
			if (CollideCheck(*p, q->Get_BindCube()))
			{
				q->Collide();
				m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
				m_particles.push_back(new CParticle(q->GetCenter()));
			}
		}
		for (auto &q : m_EnemyList) {
			if (CollideCheck(*p, q->Get_BindCube()))
			{
				q->CollideEnv();
				m_SoundManager->PlaySnd_Enemy(CSoundManager::ENEMY_SOUND::Enemy_Die);
				m_particles.push_back(new CParticle(q->GetCenter()));
				m_particles.push_back(new CParticle(q->GetCenter()));
				m_particles.push_back(new CParticle(q->GetCenter()));
			}
		}
	}
	} };
	std::thread th3{ [&]() {
	for (auto &p : m_ally_bullets) {
		p->Update(fTimeElapsed);
		if (Length(p->GetCenter()) > MapSize / 2 || p->GetCenter().y < 20.0f)
		{
			p->Collide();
			m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
			m_particles.push_back(new CParticle(p->GetCenter()));
		}
		for (auto &q : m_EnemyList) {
			if (CollideCheck(q->Get_BindCube(), p->Get_BindCube())) {
				q->Hit(1);
				p->Collide();
				m_particles.push_back(new CParticle(p->GetCenter()));
				m_SoundManager->PlaySnd_Enemy(CSoundManager::ENEMY_SOUND::Enemy_Hit);
			}
		}
		if (CollideCheck(m_Boss->Get_CoreBindCube(), p->Get_BindCube())) { // TODO : BOSSCORE
			p->Collide();
			m_Boss->Hit(1);
			m_particles.push_back(new CParticle(p->GetCenter()));
			m_SoundManager->PlaySnd_Enemy(CSoundManager::ENEMY_SOUND::Enemy_Hit);
		}
		if (CollideCheck(m_Boss->Get_BindCube(), p->Get_BindCube())) {
			m_particles.push_back(new CParticle(p->GetCenter()));
			m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
			p->Collide();
		}
		if (CollideCheck(m_Boss->Get_RoofBindCube(), p->Get_BindCube())) {
			m_particles.push_back(new CParticle(p->GetCenter()));
			m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
			p->Collide();
		}
	}
	} };
	for (auto &p : m_bullets) {
		p->Update(fTimeElapsed);
		if (Length(p->GetCenter()) > MapSize / 2 || p->GetCenter().y < 20.0f)
		{
			p->Collide();
			m_particles.push_back(new CParticle(p->GetCenter()));
			m_SoundManager->PlaySnd_UI(CSoundManager::UI_SOUND::CollideBullet_UI);
		}
		if (CollideCheck(p->Get_BindCube(), m_Player->Get_BindCube())) {
			p->Collide();
			m_Player->Hit(5);
			m_particles.push_back(new CParticle(p->GetCenter()));
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Hit_P);
		}
	}
	for (auto &p : m_particles)
		p->Update(fTimeElapsed);
	
	th1.join();
	th2.join();
	th3.join();
	
	m_Immune += fTimeElapsed;
	if (m_Player->IsDie()) 
	{
		if (m_Immune < ImmuneTime)
			m_Player->Reset();
		else if (!m_bGameOver)
		{
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_particles.push_back(new CParticle(m_Player->GetCenter()));
			m_bGameOver = true;
			m_SoundManager->PlaySnd_Player(CSoundManager::PLAYER_SOUND::Die_P);
			m_SoundManager->PlaySnd_BGM(CSoundManager::BGM_SOUND::Stop_BGM);
			m_SoundManager->PlaySnd_BGM(CSoundManager::BGM_SOUND::GameOver_BGM);
			m_pFramework->ChangeScene(CScene::CurrentScene::GameOver);
			Reset();
		}
	}
	if (m_Boss->IsDie())
	{
		if (!m_bGameClear)
		{
			m_bGameClear = true;
			for (int i = 0; i < 100; i++)
				m_particles.push_back(new CParticle(m_Boss->GetCenter()));
			m_SoundManager->PlaySnd_Boss(CSoundManager::BOSS_SOUND::Boss_Die);
			m_SoundManager->PlaySnd_BGM(CSoundManager::BGM_SOUND::Stop_BGM);
			m_SoundManager->PlaySnd_BGM(CSoundManager::BGM_SOUND::GameClear_BGM);
			m_pFramework->ChangeScene(CScene::CurrentScene::GameClear);
			Reset();
		}
	}
}

void CMainScene::Rendering()
{
	glPushMatrix();
	m_pCamera->LookAt();
	m_pLight->Light(CLight::LightTag::Light0);
	DrawAxis();
	m_Sky->Rander();
	m_Bottom->Rendering();
	for(auto p: m_ObstarcleList)
		p->Rendering();
	for (auto &p : m_EnemyList)
		p->Rendering();
	for (auto &p : m_bullets)
		p->Rendering();
	for (auto &p : m_ally_bullets)
		p->Rendering();
	for (auto &p : m_energybolts)
		p->Rendering();
	for (auto &p : m_particles)
		p->Rander();
	m_Boss->Rendering();
	m_Player->Rendering();
	glPopMatrix();
}

void CMainScene::RendMiniMap()
{
	glViewport(CLIENT_WIDTH - 300, CLIENT_HEIGHT - 300, 300, 300);
	glPushMatrix();
	m_MiniMapCamera->LookAt();
	m_pLight->Light(CLight::LightTag::Light0);
	DrawAxis();
	for (auto p : m_ObstarcleList)
		p->Rendering();
	glColor3f(1, 0, 1);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (auto p : m_EnemyList)
		glVertex3fv(p->GetCenter().arr);
	glColor3f(1, 0, 0);
	for (auto &p : m_bullets)
		glVertex3fv(p->GetCenter().arr);
	for (auto &p : m_ally_bullets)
		glVertex3fv(p->GetCenter().arr);
	for (auto &p : m_energybolts)
		glVertex3fv(p->GetCenter().arr);
	glEnd();
	m_Player->Rendering();
	CTextureLibraray::UsingTexture2D();
	m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::MiniMap);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 0.3f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(MapSize *0.5f, 0.0f, MapSize *0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(MapSize *0.5f, 0.0f, -MapSize *0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-MapSize *0.5f, 0.0f, -MapSize *0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(-MapSize *0.5f, 0.0f, MapSize *0.5f);
	glEnd();
	glDisable(GL_BLEND);
	CTextureLibraray::StopUsingTexture2D();
	glPopMatrix();
	glViewport(0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);

	{
		////////////////////<RAND PLAYER INFO>/////////////////////////////////////////

		glDisable(GL_DEPTH_TEST);
		//glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, CLIENT_WIDTH, 0, CLIENT_HEIGHT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		CTextureLibraray::UsingTexture2D();
		{
			glColor4f(1.0f, 1.0f, 1.0f, 0.7);
			m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::UIBACK);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(25.0f, 750.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(25.0f, 650.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(600.0f, 650.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(600.0f, 750.0f, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(0.0f, 20.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1200.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1200.0f, 20.0f, 0.0f);
			glEnd();

			glPushMatrix();
			{
				m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::Gear);
				glTranslatef(75, 700, 0);
				glColor4f(1, 1, 1, 1.f);
				glRotatef(m_Player->GetModel().GetAngle(), 0, 0, 1);
				RandQuad({ 0,0,0 }, 125, true);
			}
			glPopMatrix();

		}
		CTextureLibraray::StopUsingTexture2D();

		/////////////<HP>///////////////////////////

		glColor4f(1.0f, 0.0f, 0.0f, 0.7);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(150.0f, 735.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(150.0f, 715.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(150.f + m_Player->GetHP()*80.0f, 715.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(150.f + m_Player->GetHP()*80.0f, 735.0f, 0.0f);
		glEnd();
		//////////<Shield>//////////////////////////
		glColor4f(0.0f, 1.0f, 1.0f, 0.7);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(150.0f, 710.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(150.0f, 690.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(150.f + m_Player->GetBarrier()*4.0f, 690.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(150.f + m_Player->GetBarrier()*4.0f, 710.0f, 0.0f);
		glEnd();

		//////////<Booster>//////////////////////////
		glColor4f(1.0f, 1.0f, 0.0f, 0.7);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(150.0f, 685.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(150.0f, 665.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(150.f + m_Player->GetBoost()*4.0f, 665.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(150.f + m_Player->GetBoost()*4.0f, 685.0f, 0.0f);
		glEnd();
		//////////<BossHP>//////////////////////////
		glColor4f(1.0f, 1.0f, 0.0f, 0.7);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(20.0f, 15.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(20.0f, 5.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(20.0f + m_Boss->GetHP()*1.16f, 5.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(20.0f + m_Boss->GetHP()*1.16f, 15.0f, 0.0f);
		glEnd();
		/////////////////////////////////////////////
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
	
	}
}

bool CMainScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	}
	return false;
}

bool CMainScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		m_Player->SetisShooting(true);
		break;
	case WM_LBUTTONUP:
		m_Player->SetisShooting(false);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		m_pCamera->RotateViewDirection(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	return false;
}

bool CMainScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

void CMainScene::BuildObjects(CFramework * myFramework, HWND hWnd, CurrentScene tag)
{
	CScene::BuildObjects(myFramework, hWnd, tag);
	m_SoundManager = m_pFramework->GetSoundManager();
	m_pCamera = m_pFramework->GetCamera();
	m_MiniMapCamera = m_pFramework->GetMiniMapCamera();
	m_pLight = m_pFramework->GetLight();
	m_TextureLib = m_pFramework->GetTextureLib();
	SettingLight();
	SettingObjects();
}

void CMainScene::ReleaseObjects()
{
}


bool CMainScene::ProcessInput()
{
	bool bProcessedByScene = false;

	if (!bProcessedByScene)
	{
		static UCHAR pKeyBuffer[256];
		DWORD dwLRDirection = 0;
		DWORD dwUDDirection = 0;

		bool bPushShift = false;
		bool bControll = false;

		if (GetKeyboardState(pKeyBuffer))
		{
			if (pKeyBuffer[VK_LSHIFT] & 0xF0)	bPushShift = true;
			if (pKeyBuffer['W'] & 0xF0)			dwUDDirection |= DIR_UP;
			if (pKeyBuffer['S'] & 0xF0)			dwUDDirection |= DIR_DOWN;
			if (pKeyBuffer['A'] & 0xF0)			dwLRDirection |= DIR_LEFT;
			if (pKeyBuffer['D'] & 0xF0)			dwLRDirection |= DIR_RIGHT;

			if (pKeyBuffer['1'] & 0xF0) { bControll = true; m_pCamera->SetViewMode(CCamera_OpenGL::CameraViewMode::TPS); }
			if (pKeyBuffer['2'] & 0xF0) { bControll = true; m_pCamera->SetViewMode(CCamera_OpenGL::CameraViewMode::FPS); }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			if ((pKeyBuffer['A'] & 0xF0) || (pKeyBuffer['D'] & 0xF0))
			{
				if (dwLRDirection & DIR_LEFT) { bControll = true; m_bLeft = true;}
				else m_bLeft = false;
				if (dwLRDirection & DIR_RIGHT) { bControll = true; m_bRight = true;}
				else m_bRight = false;
			}
			else
			{
				m_bLeft = false;
				m_bRight = false;
			}
			if ((pKeyBuffer['W'] & 0xF0) || (pKeyBuffer['S'] & 0xF0))
			{
				if (dwUDDirection & DIR_UP) { bControll = true; m_bFront = true; }
				else m_bFront = false;
				if (dwUDDirection & DIR_DOWN) { bControll = true; m_bBack = true; }
				else m_bBack = false;
			}
			else
			{
				m_bFront = false;
				m_bBack = false;
			}
			m_Player->Boost(bPushShift);
		}

		if (!bControll)
		{
			
		}

		return bControll;
	}
	return false;
}
