#pragma once

//class NPC;
class NpcMove

{
public:
	NpcMove();
	~NpcMove();
	//移動処理。
	float RoundTripMove();
	float RandomMoveX();
	float RandomMoveZ();
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 k)
	{
		m_position = k;
	}
	void SetmoveSpeed(CVector3 a)
	{
		m_moveSpeed = a;
	}
	CVector3 GetmoveSpeed()
	{
		return m_moveSpeed;
	}
	int h;
private:
	CVector3 m_position = CVector3::Zero;	//座標
	CVector3 m_moveSpeed = CVector3::Zero;	//移動
	int timer2 = 0;		//簡易タイマー
	int timer = 0;		//簡易タイマー２
	int fugou = 1;		//移動方向
	int randomX = 1;	//乱数取得X軸
	int randomZ = 1;	//乱数取得Z軸
};