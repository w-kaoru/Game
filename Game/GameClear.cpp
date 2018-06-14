#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"
#include "Player.h"
#include "StageSeni.h"

GameClear::GameClear()
{
}
GameClear::~GameClear()
{
}
void GameClear::OnDestroy()
{
}
bool GameClear::Start()
{
	pl = FindGO<Player>("Player");
	m_ss = FindGO<StageSeni>("ss");
	//エフェクトを作成。
	effect = NewGO<prefab::CEffect>(0);
	return true;
}
void GameClear::Update()
{
	
	Gtime++;
	CQuaternion qRot;
	qRot = pl->GetRotation();
	m_pos = pl->GetPosition();
	if (pl->Getef_flag() == 0) {
		pl->Setef_flag();
		
		//エフェクトを再生。
		effect->Play(L"effect/hanabi.efk");
		CVector3 emitPos = m_pos;
		emitPos.y += 10.0f;
		effect->SetPosition(emitPos);
		effect->SetRotation(qRot);
		
	}
	else if (pl->Getef_flag() == 1 && Gtime > 90) {
		m_ss->SetSNo();
		pl->Setef_flag();
		DeleteGO(this);
	}

}