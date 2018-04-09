#include "stdafx.h"
#include "NPC.h"


NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}

bool NPC::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
	return true;
}

void NPC::Update()
{
	//上下左右のキー入力による移動処理。
	if (Pad(0).IsPress(enButtonRight)) {
		m_position.x -= 5.0f;
	}
	else if (Pad(0).IsPress(enButtonLeft)) {
		m_position.x += 5.0f;
	}
	else if (Pad(0).IsPress(enButtonUp)) {
		m_position.y += 5.0f;
	}
	else if (Pad(0).IsPress(enButtonDown)) {
		m_position.y -= 5.0f;
	}
	//座標を設定。
	m_skinModelRender->SetPosition(m_position);
}

void NPC::Render(CRenderContext& rc)
{
}