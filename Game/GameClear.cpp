#include "stdafx.h"
#include "GameClear.h"
#include "Test.h"

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
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();

	//スキンモデルレンダラーを作成。
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");

	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f });

	return true;
}
void GameClear::Update()
{
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 90.0f);
	if (Pad(0).IsTrigger(enButtonX)) {
		//エフェクトを作成。
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		//エフェクトを再生。
		effect->Play(L"effect/hanabi.efk");
		CVector3 emitPos = m_pos;
		emitPos.y += 10.0f;
		effect->SetPosition(emitPos);
		effect->SetRotation(qRot);
	}
	m_pos.z += Pad(0).GetLStickXF();
	m_pos.y += Pad(0).GetLStickYF();
	
	m_skinModelRender->SetPosition(m_pos);
	m_skinModelRender->SetRotation(qRot);
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
}