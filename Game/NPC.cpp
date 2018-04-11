#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Test.h"


NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::OnDestroy()
{
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		DeleteGO(m_skinModelRender[i]);
	}
}

bool NPC::Start()
{
	//NPC配置のコード
	m_game = FindGO<Game>("Game");
	std::list<MapChip*>::iterator a= m_game->m_level.itr;
	int h = 1;
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		MapChip* f = *a;
		m_position[i] = f->m_position;
		m_position[i].y += 30.0;
		m_position[i].x += h;
		m_skinModelRender[i] = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender[i]->Init(L"modelData/unityChan.cmo");
		m_skinModelRender[i]->SetPosition(m_position[i]);
		m_skinModelRender[i]->SetScale({ 0.1f, 0.1f, 0.1f });
		h += 1;
		a++;
	}
	return true;
}

void NPC::Update()
{
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		//座標を設定。
		m_skinModelRender[i]->SetPosition(m_position[i]);
	}
}

void NPC::Render(CRenderContext& rc)
{
}