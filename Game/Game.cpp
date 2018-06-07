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
#include "StageSeni.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/Sound/tkSoundEngine.h"


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
	m_ss = FindGO<StageSeni>("ss");
	m_soundSource = NewGO<prefab::CSoundSource>(0);
	m_soundSource->Init("Assets/sprite/1ststageBGMmT.wav", true);
	m_soundSource->Play(true);
	//レベルを構築する。
	m_level.Build(L"level/map2.tks");

	CLocData locData;
	locData.Load(L"modelData/NPCloc.tks");
	for (int i = 0; i < locData.GetNumObject(); i++) {
		NPC* npc = NewGO<NPC>(0);
		if (counter % 4 == 0)
		{
			npc->npckanjou = angry;
			npc->npcState = npc->osou;
		}
		npc->m_position = locData.GetObjectPosition(i);
		m_npcList.push_back(npc);
		counter++;
	}
	return true;
}
void Game::OnDestroy()
{
	DeleteGO(m_player);
	DeleteGO(m_background);
	DeleteGO(m_gameCamera);
	for (auto& npc : m_npcList) {
		DeleteGO(npc);
	}
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
		if (m_player->Getef_flag() == 2) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	SoundEngine().SetListenerPosition(MainCamera().GetPosition());
}
void Game::Render(CRenderContext& rc)
{
}