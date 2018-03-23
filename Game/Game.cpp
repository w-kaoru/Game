#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Background.h"
#include "Title.h"


Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	//ƒJƒƒ‰‚ğİ’èB
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	m_background = NewGO<Background>(0);
	return true;
}
void Game::OnDestroy()
{
	DeleteGO(m_background);
	DeleteGO(m_skinModelRender);
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