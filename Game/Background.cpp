#include "stdafx.h"
#include "Background.h"
#include "StageSeni.h"


void Background::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Background::Start()
{
	//ピクセルシェーダーをロード。
	
	m_psShader.Load("shader/model.fx", "PSSkyMain", CShader::EnType::PS);
	StageSeni* m_ss = FindGO<StageSeni>("ss");
	//１ステージ
	if (m_ss->GetSNo() == 0) {
		//モデルをロード。
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/saisyo.cmo");
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
	m_skinModelRender->FindMaterial([&](auto mat) {
		if (mat->EqualMaterialName( L"sky" ) == true ) {
			mat->SetRender3DModelPSShader(m_psShader);
		}
	});
	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity);
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
