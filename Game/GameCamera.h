#pragma once

#include "Player.h"
//ばねカメラを使用したい場合はtkSpringCamera.hをインクルードする必要がある。
#include "tkEngine/camera/tkSpringCamera.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	Player* m_player;	//プレイヤー。
	CVector3 m_toCameraPos = CVector3::Zero;	//
	CVector3 pos = CVector3::Zero;
	CSpringCamera m_springCamera; //ばねカメラ。
	int Pullcamera = 0;
};

