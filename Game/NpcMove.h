#pragma once

//class NPC;
class NpcMove

{
public:
	NpcMove();
	~NpcMove();
	//ˆÚ“®ˆ—B
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
	CVector3 m_position = CVector3::Zero;	//À•W
	CVector3 m_moveSpeed = CVector3::Zero;	//ˆÚ“®
	//NPC* m_npc = nullptr;
	int MoveNo = 0;
	int hanten = 0;
	int timer2 = 0;
	int timer = 0;
	int fugou = 1;
	int randomX = 1;
	int randomZ = 1;
};