#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Background.h"
#include "Title.h"
#include "Player.h"
#include "GameCamera.h"
#include "Level.h"
#include "NPC.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();

	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	m_player = NewGO<Player>(0,"Player");
	m_background = NewGO<Background>(0);
	m_gameCamera = NewGO<GameCamera>(0);
	//レベルを構築する。
	m_level.Build(L"level/map2.tks");
	for (int i = 0; i < m_level.m_mapChipList.size(); i++) {
		NPC* npc = NewGO<NPC>(0);
		npc->m_position= m_level.m_mapChipList[i]->m_position;
		
	}
	return true;
}
void Game::OnDestroy()
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	DeleteGO(m_gameCamera);
	DeleteGO(m_npc);
}
void Game::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
				NewGO<Title>(0, "Title");
				DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsPress(enButtonA)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}
void Game::Render(CRenderContext& rc)
{
}