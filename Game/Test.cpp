#include "stdafx.h"
#include "Test.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Title.h"
#include "GameClear.h"


Test::Test()
{
}


Test::~Test()
{
}
bool Test::Start()
{
	//ƒJƒƒ‰‚ğİ’èB
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();

	m_gameClear = NewGO<GameClear>(0,"GameClear");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	return true;
}
void Test::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, "Title");
			DeleteGO(m_gameClear);
			DeleteGO(this);
		}
	}
	else {
		if (Pad(0).IsPress(enButtonB)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}