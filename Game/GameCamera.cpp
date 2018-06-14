#include "stdafx.h"
#include "GameCamera.h"


//カメラデータ。
struct SCameraData {
	float targetToPosition;		//注視点から視点までの距離。
	int humanLimit;				//このカメラデータを使用できる人間の数の上限。
};
//カメラデータのテーブル。
SCameraData cameraDataTbl[] = {
	{ 15.0f, 5 },			//人間の数が５人以下の時のカメラデータ。
	{ 20.0f, 10 },			//人間の数が10人以下の時のカメラデータ。
	{ 30.0f, 20 },			//人間の数が20人以下の時のカメラデータ。
	{ 40.0f, 100},
	{ 100.0f, 10000},		//人間の数が10000人以下の時のカメラデータ。
};

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 15.0f, 30.0f);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("Player");

	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);

	//ばねカメラの初期化。
	m_springCamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		1000.0f,			//カメラの移動速度の最大値。
		false,					//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	return true;
}
void GameCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	CVector3 target = m_player->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 10.0f;

	CVector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 6.0f * x);
	qRot.Multiply(m_toCameraPos);
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 6.0f * y);
	qRot.Multiply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}/*
	if (m_player->GetfollowerNum() > 2) {
		float angle = 0.0f;
		angle += 3.0f;
		qRot.SetRotationDeg(CVector3::AxisY, angle);
		qRot.Multiply(m_player->GetPlforward());
	}*/
	//ついて来ている人間の数で、使用するカメラデータを決める。
	SCameraData* cameraData = nullptr;
	int arraySize = ARRAYSIZE(cameraDataTbl);
	for (int i = 0; i < arraySize; i++) {
		if (m_player->GetfollowerNum() < cameraDataTbl[i].humanLimit) {
			//使用するカメラデータが見つかった。
			cameraData = &cameraDataTbl[i];
			break;
		}
	}
	//注視点から視点へのベクトルを正規化して、大きさ１にする。
	m_toCameraPos.Normalize();
	m_toCameraPos *= cameraData->targetToPosition;
	////新しい注視点から視点までのベクトルが求まったので、新しい視点を計算する。
	CVector3 pos = target + m_toCameraPos;
	//バネカメラに注視点と視点を設定する。
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);

	//バネカメラの更新。
	m_springCamera.Update();
}