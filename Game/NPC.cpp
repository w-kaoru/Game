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
	DeleteGO(m_skinModelRender);
}

bool NPC::Start()
{
	//int npcCflag = 1;
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
		if (plpo.Length() < 4.0) {
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		break;
	case delighted:
		if (plpo.Length() > 50.0f) //仮
		{
			npcState = haikai;
			npckanjou = flat;
		}
	case angry:
		if (plpo.Length() < 4.0&&m_player->GetfollowerNum()==7
			/*　プレイヤーが連れている人数が一定値以上になったら、感情を喜び状態にする。*/
			) {
			npckanjou = delighted;
			npcState = tuibi;
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
	plpo = m_player->m_position - m_position;
	switch (npcState) {
	case haikai:
		//徘徊状態の処理。
		//@todo 渡辺 ここのプログラムをNPCの徘徊の仕方によって、処理をわけて　実装するように
		break;
	case tuibi:
		//追尾状態。
		//ここにプレイヤーに追尾するプログラムを書く。
		plpo.Normalize();
		m_moveSpeed.x = plpo.x *50 ;
		m_moveSpeed.z = plpo.z *50 ;
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
	/*if (stageNo == 0) {

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