#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Test.h"
#include "Player.h"


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
	m_player = FindGO<Player>("Player");
	std::list<MapChip*>::iterator a= m_game->m_level.itr;
	int h = 1;
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		MapChip* f = *a;
		m_position[i] = f->m_position;
		m_position[i].y += 30.0;
		m_position[i].x += h;
		m_skinModelRender[i] = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender[i]->Init(L"modelData/unityChan.cmo");
		//キャラクターコントローラーを初期化。
		m_charaCon[i].Init(
			4.0,			//半径。 
			6.0f,			//高さ。
			m_position[i] 	//初期位置。
		);
		m_skinModelRender[i]->SetPosition(m_position[i]);
		m_skinModelRender[i]->SetScale({ 0.1f, 0.1f, 0.1f });
		h += 1;
		a++;
	}
	return true;
}

void NPC::Update()
{
	CVector3 plp[30];
	CQuaternion qRot[30];
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		m_moveSpeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();
		plp[i] = m_player->m_position - m_position[i];
		if (plp[i].Length() < 100.0f) {
			plp[i].Normalize();
			m_moveSpeed[i].x = plp[i].x * 50;
			m_moveSpeed[i].z = plp[i].z * 50;
			//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
			//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
			//atan2を使用して、角度を求めている。
			//これが回転角度になる。
			angle[i] = atan2(m_moveSpeed[i].x, m_moveSpeed[i].z);
			//atanが返してくる角度はラジアン単位なので
			//SetRotationDegではなくSetRotationを使用する。
			m_rotation[i].SetRotation(CVector3::AxisY, angle[i]);
		}
		m_position[i] = m_charaCon[i].Execute(
			GameTime().GetFrameDeltaTime(),
			m_moveSpeed[i]
		);
		//座標を設定。
		//ワールド行列を更新。
		qRot[i].SetRotationDeg(CVector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる。
		qRot[i].Multiply(m_rotation[i], qRot[i]);
		m_skinModelRender[i]->SetPosition(m_position[i]);
		m_skinModelRender[i]->SetRotation(qRot[i]);
	}
}

void NPC::Render(CRenderContext& rc)
{
}