#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Player.h"


NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::OnDestroy()
{
}

bool NPC::Start()
{
	int npcCflag = 1;
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");

	//Level *NpcBasyo;
	//NpcBasyo->m_mapChipList[0]->m_position;
	m_position.y += 25.0;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_charaCon.Init(
		4.0,			//半径。 
		6.0f,			//高さ。
		m_position, 	//初期位置。
		1
	);
	
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });

	return true;
}

void NPC::Update()
{
	CVector3  plpo;
	CQuaternion  nprt;
	
	plpo = m_player->m_position - m_position;


	switch (npckanjou)
	{
	case flat:
		if (plpo.Length() > 50.0f&&flag == 0) {
			m_moveSpeed.x = 0;
			m_moveSpeed.z = 0;
		}
		else if (plpo.Length() > 50.0f&&flag == 1) {

			flag = 0;
		}
		else if (plpo.Length() < 50.0f) {
			npckanjou = delighted;
		}
		break;
	case delighted:
		if (plpo.Length() < 50.0f) {
			plpo.Normalize();
			m_moveSpeed.x = plpo.x * 50;
			m_moveSpeed.z = plpo.z * 50;
		}
		m_moveSpeed.y -= 980.0f*GameTime().GetFrameDeltaTime();
		m_position = m_charaCon.Execute(
			GameTime().GetFrameDeltaTime(),
			m_moveSpeed
		);
		break;
	}
	//座標を設定。
	//ワールド行列を更新。
	nprt.SetRotationDeg(CVector3::AxisX, 0.0f);//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる。
	nprt.Multiply(m_rotation, nprt);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(nprt);
}
void NPC::Render(CRenderContext& rc)
{
}