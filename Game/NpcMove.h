#pragma once

//class NPC;
class NpcMove

{
public:
	NpcMove();
	~NpcMove();
	//ˆÚ“®ˆ—B
	float MoveRoundTrip();
	float RandomMove();
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
	int time = 0;
	int fugou = 1;
};