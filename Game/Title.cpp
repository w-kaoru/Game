#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
Title::Title()
{
}


Title::~Title()
{
}
void Title::OnDestroy()
{
}
bool Title::Start()
{
	m_texture.CreateFromDDSTextureFromFile(L"sprite/title.dds");
	m_sprite.Init(m_texture, 1280,720/*GraphicsEngine().Get2DSpaceScreenWidth(), GraphicsEngine().Get2DSpaceScreenHeight()*/);
	m_fade = FindGO<Fade>("Fade");

	m_font.SetShadowParam(true, 1.0f, { 26.0f / 255.0f, 49 / 255.0f, 103 / 255.0f, 1.0f });
	m_fade->StartFadeIn();
	return true;
}
void Title::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsPressAnyKey()) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}
void Title::PostRender(CRenderContext& rc)
{
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	//press any keyÇï\é¶ÅB
	m_font.Begin(rc);
	m_font.Draw(L"PRESS ANY KEY", { 0.0f, -270.0f }, { 234.0f / 255.0f, 69.0f / 255.0f, 21.0f / 255.0f, 1.0f }, 0.0f, 1.0f);
	m_font.End(rc);
}
