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
	if (m_ss->GetSNo() == 0) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/zimen2.cmo");
	}
	if (m_ss->GetSNo() == 1) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/karisute2.cmo");
	}
	if (m_ss->GetSNo() > 1) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/karisute3.cmo");
	}
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity);
	return true;
}
