#include "stdafx.h"
#include "Player.h"
#include "GameClear.h"
#include "NPC.h"
#include "StageSeni.h"

Player::Player()
{
}


Player::~Player()
{
}
void Player::OnDestroy()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_gc);
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
	m_position.y = 40;
	m_position.x = 200.0f;
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		4.0,			//半径。 
		100.0f,			//高さ。
		m_position, 	//初期位置。
		0			//0がプレイヤーのフラグ。
	);
	//エフェクトを作成。
	effect = NewGO<prefab::CEffect>(0);
	m_npc = FindGO<NPC>("npc");
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	plkanjou = delighted;

	//アニメーションクリップのロード。
	//m_animClips[enAnimationClip_idle].Load(L"animData/idle.tka");
	//m_animClips[enAnimationClip_run].Load(L"animData/run.tka");
	//m_animClips[enAnimationClip_walk].Load(L"animData/walk.tka");
	////ループフラグを設定する。<-走りアニメーションはループフラグを設定していないので
	////ワンショット再生で停止する。
	//m_animClips[enAnimationClip_run].SetLoopFlag(true);
	//m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	//m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	return true;
}

//void Player::Effect(CVector3 npcpos, CQuaternion npcrot)
//{
//	switch (plkanjou)
//	{
//	case delighted:
//		//エフェクトを再生。
//		if (effect->IsPlay() == false) {
//			effect = NewGO<prefab::CEffect>(0);
//			effect->Play(L"effect/tanosii.efk");
//		}
//		effect->SetPosition(npcpos);
//		effect->SetRotation(npcrot);
//		break;
//	case angry:
//		if (effect->IsPlay() == false) {
//			//エフェクトを再生。
//			effect = NewGO<prefab::CEffect>(0);
//			effect->Play(L"effect/okoru.efk");
//		}
//		effect->SetPosition(npcpos);
//		effect->SetRotation(npcrot);
//		break;
//	}
//}
void Player::UpdatekanjouSt1()
{
	switch (plkanjou)
	{
	case flat:
		go = true;
		break;
	case delighted:
		if (plkan == true) {
			plkanjou = flat;
		}
		break;
	}
}

void Player::Move()
{
	//左スティックの入力量を受け取る。
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	m_moveSpeed += cameraForward * lStick_y * 60.0f;	//奥方向への移動速度を代入。
	m_moveSpeed += cameraRight * lStick_x * 60.0f;		//右方向への移動速度を加算。
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	//プレイヤーの前方向。
	m_plforward = m_moveSpeed;
	/*if (m_moveSpeed.x > 0.01f || m_moveSpeed.y > 0.01f) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 2.0f);
	}
	else {
		m_skinModelRender->PlayAnimation(enAnimationClip_idle, 2.0f);
	}*/

}

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void Player::Update()
{
	//移動処理。
	Move();
	//旋回処理。
	Turn();

	//Effect(m_position, m_rotation);

	UpdatekanjouSt1();

	if (followerNum > clearNum && ef_flag == 0) {
		m_gc = NewGO<GameClear>(0);
	}
	//ワールド行列を更新。
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる。
	qRot.Multiply(m_rotation, qRot);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qRot);
}