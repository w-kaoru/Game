#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Background.h"
#include "Title.h"
#include"GameOver.h"
#include "Player.h"
#include "GameCamera.h"
#include "Level.h"
#include "NPC.h"
#include "StageSeni.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/Sound/tkSoundEngine.h"
#include "tkEngine/timer/tkGameTime.h"

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
	m_soundSource = NewGO<prefab::CSoundSource>(0);
	m_soundSource->Init("Assets/sprite/1ststageBGMmT.wav");
	m_soundSource->Play(true);
	m_ss = FindGO<StageSeni>("ss");
	//レベルを構築する。
	m_level.Build(L"level/map2.tks");

	locData.Load(L"modelData/NPCloc.tks");
	for (int i = 0; i < locData.GetNumObject(); i++) {
		NPC* npc = NewGO<NPC>(0);
		if (counter % 4 == 0)
		{
			npc->npckanjou = angry;
			npc->npcState = npc->osou;

		}
		else
		{
			npc->npckanjou = flat;
			npc->npcState = npc->haikai;
		}
		npc->m_position = locData.GetObjectPosition(i);
		m_npcList.push_back(npc);
		counter++;
	}
	//ライティング、影を落とす。
	m_sunLig = NewGO<prefab::CDirectionLight>(0);
	CVector3 lightDir = { 0.20f, -0.3f, 0.0f };
	lightDir.Normalize();
	m_sunLig->SetDirection(lightDir);
	m_sunLig->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	LightManager().SetAmbientLight({ 0.4f, 0.4f, 0.4f });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);
	//タイマー用のフォントを初期化。
	m_timerFont = std::make_unique<DirectX::SpriteFont>(
		GraphicsEngine().GetD3DDevice(),
		L"font/hato_pop.spritefont"
		);
	m_fontTest.SetFont(m_timerFont.get());
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
	//タイマーの減算
	//残り時間
	if (m_timer > 0.0f)
	{
		m_timer -= GameTime().GetFrameDeltaTime();
	}
	if (m_timer < 0.0f) {
		m_gameover=NewGO<GameOver>(0, "GameOver");

		m_gameover->SetGameOver(true);
		m_timer = 0.0f;
	}
	////フェードアウト
	//if (m_isWaitFadeout) {
	//	if (!m_fade->IsFade()) {
	//		if (m_gameover.GetGameOver() == true) {
	//			m_ss->SetGameOver();
	//		}
	//		NewGO<Title>(0, "Title");
	//		DeleteGO(this);
	//	}
	//}
	//else {
	//	if (m_player->Getef_flag() == 2 || m_gameover.GetGameOver() == true) {
	//		m_isWaitFadeout = true;

	//		m_fade->StartFadeOut();
	//	}
	//}
	SoundEngine().SetListenerPosition(MainCamera().GetPosition());
}
void Game::Render(CRenderContext& rc)
{
	
}
void Game::PostRender(CRenderContext& rc)
{
	//タイマーの表示。
	wchar_t text[256];
	int minute = (int)m_timer / 60;
	int sec = (int)m_timer % 60;
	swprintf_s(text, L"%02d:%02d", minute, sec);
	m_fontTest.Begin(rc);

	//文字を描画。
	m_fontTest.Draw(
		L"TIME ",
		{ -620.0f, 340.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		0.8f,
		{ 0.0f, 1.0f }
	);
	m_fontTest.Draw(
		text,
		{ -465.0f, 340.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		0.8f,
		{ 0.0f, 1.0f }
	);
	m_fontTest.End(rc);

}