#include "stdafx.h"
#include "Background.h"
#include "StageSeni.h"


void Background::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Background::Start()
{
	StageSeni* m_ss = FindGO<StageSeni>("ss");
	//１ステージ
	if (m_ss->GetSNo() == 0) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/zimen3.cmo");
	}
	//2ステージ
	if (m_ss->GetSNo() == 1) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/karisute2.cmo");
	}
	//3ステージ
	if (m_ss->GetSNo() >= 2) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/karisute3.cmo");
	}
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity);
	return true;
}
