#include "stdafx.h"
#include "NpcMove.h"
#include <random>
//#include "NPC.h"

NpcMove::NpcMove()
{
	//m_position = m_npc->m_position;
}

NpcMove::~NpcMove()
{
}
	


float NpcMove::MoveRoundTrip()
{
	time++;
	m_moveSpeed = m_position;
	m_moveSpeed.y = 0.0f;
		m_moveSpeed.Normalize();
		if (time>0&&time <= 10) {
			if (hanten == 0) {
				//m_position.x += m_moveSpeed.x * 10.0*fugou;
				if (time == 10) {
					fugou *= -1;
					time = 0;
				}
			}
		}
		return m_moveSpeed.x * 100.0*fugou;
}
float NpcMove::RandomMove()
{

}