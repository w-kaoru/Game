#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"
#include "Player.h"
GameClear::GameClear()
{
}


GameClear::~GameClear()
{
}
void GameClear::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool GameClear::Start()
{
	pl = FindGO<Player>("Player");
	return true;
}
void GameClear::Update()
{
	Gtime += 1;
	CQuaternion qRot;
	qRot = pl->m_rotation;
	m_pos = pl->m_position;
	//エフェクトを作成。
	prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
	if (pl->ef_flag == 0) {
		pl->ef_flag = 1;
		
		//エフェクトを再生。
		effect->Play(L"effect/hanabi.efk");
		CVector3 emitPos = m_pos;
		emitPos.y += 10.0f;
		effect->SetPosition(emitPos);
		effect->SetRotation(qRot);
		
	}
	else if (pl->ef_flag == 1&&Gtime==90) {
		pl->ef_flag = 2;
		DeleteGO(this);
	}

}