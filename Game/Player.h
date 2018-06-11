#pragma once
//キャラクターコントローラーを使用する場合は、下記のヘッダーファイルのインクルードが必要。
#include "tkEngine/character/tkCharacterController.h"
class GameClear;
class Player :public IGameObject
{
public:
	Player();
	~Player();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;

	//移動処理。
	void Move();
	void Turn();
	//ゲッター、セッター
	int GetfollowerNum()
	{
		return followerNum;
	}
	int Getef_flag()
	{
		return ef_flag;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	void Setef_flag()
	{
		ef_flag++;
	}
	void SetfollowerNump() 
	{
		followerNum++;
	}
	void SetfollowerNumm()
	{
		followerNum--;
	}
	////////////////////////////////////
	// メンバ変数とか
	////////////////////////////////////
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero;	//座標。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	CCharacterController m_charaCon;		//キャラクターコントローラー。
	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
			//付いて来ている人間の数。
	GameClear* m_gc = nullptr;

	int ef_flag = 0;						//エフェクトのフラグ。
	int followerNum = 0;			
};
