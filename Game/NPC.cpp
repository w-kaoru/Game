#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Player.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/Sound/tkSoundEngine.h"

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
	
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");

	
	
	m_position.y = 0;
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

	//@todo ステージによって、生成する感情コントロールのインスタンスを切り替えるように.

	return true;
}
//Stage1の感情更新関数。
void NPC::UpdateKanjouStage1()
{
	plpo = m_player->m_position - m_position;
	switch (npckanjou)
	{
	case flat:
		if (plpo.Length() < 5.0f) {
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		break;
	case delighted:
		//喜んでいる
		if (plpo.Length() < 5.0f && npcState != tuibi)
		{
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		break;
	case angry:
		if (plpo.Length() <= 5.0f&&m_player->GetfollowerNum() >= 2 )
			//プレイヤーが連れている人数が一定値以上になったら、感情を喜び状態にする。
		{
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		else if (plpo.Length() <= 5.0f) {
			//怒っている人間とプレイヤーがぶつかった。
			//ついてきているNPCすべての感情を変更する。
			for (int i = 0; i < m_game->m_npcList.size(); i++) {
				if(m_game->m_npcList[i]->npcState == tuibi){
					m_game->m_npcList[i]->npckanjou = flat;
					m_game->m_npcList[i]->npcState = haikai;
					m_player->SetfollowerNumm();
				}	
			}
		}
		break;
	}
}
//Stage2の感情更新関数。
void NPC::UpdateKanjouStage2()
{
}
//Stage3の感情更新関数。
void NPC::UpdateKanjouStage3()
{
}
void NPC::UpdateState()
{
	
	switch (npcState) {
	case haikai:
		//徘徊状態の処理。
		//@todo 渡辺 ここのプログラムをNPCの徘徊の仕方によって、処理をわけて　実装するように
		m_moveSpeed.x = 0;
		m_moveSpeed.z = 0;
		break;
	case tuibi:
		//追尾状態。
		//ここにプレイヤーに追尾するプログラムを書く。
		plpo.Normalize();
		m_moveSpeed.x = plpo.x *50 ;
		m_moveSpeed.z = plpo.z *50 ;
		angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3::AxisY, angle);
		break;
	case osou:
		if (plpo.Length() < 60.0) {
			plpo.Normalize();
			m_moveSpeed.x = plpo.x * 40;
			m_moveSpeed.z = plpo.z * 40;
			//angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
			//m_rotation.SetRotation(CVector3::AxisY, angle);
			if (m_soundSource == nullptr) {
				m_soundSource = NewGO<prefab::CSoundSource>(0);
				m_soundSource->Init("Assets/sprite/Mic3_52.wav",true);
				m_soundSource->SetPosition(m_position);
				m_soundSource->SetVolume(1.0f);
				m_soundSource->Play(true);
			}
			else {
				m_soundSource->SetPosition(m_position);
			}
		}
		break;
	}
	m_position = m_charaCon.Execute(
		GameTime().GetFrameDeltaTime(),
		m_moveSpeed);
}
void NPC::Update()
{
	//感情の更新。
	//こんな感じでいいのでは。
	/*if (GetSNo->stageNo == 0) {

		UpdateKanjouStage1();
	}*/

	UpdateKanjouStage1();

	//状態を更新。
	UpdateState();

	//UpdateKanjou();

	CQuaternion  nprt;
	
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