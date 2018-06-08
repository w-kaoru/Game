#include "stdafx.h"
#include "NpcMove.h"
#include <time.h>
//#include "NPC.h"

NpcMove::NpcMove()
{
	//m_position = m_npc->m_position;
}

NpcMove::~NpcMove()
{
}
	

//往復移動
float NpcMove::RoundTripMove()
{
	timer++;
	m_moveSpeed = m_position;
	m_moveSpeed.y = 0.0f;
		m_moveSpeed.Normalize();
		if (timer > 0 && timer <= 20) {
			//移動の方向を求める。
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 20) {
				//移動方向変換
				fugou *= -1;
				//簡易タイマーリセット
				timer = 0;
			}
		}
		//移動の計算を返す。
		return m_moveSpeed.x * 100.0f * fugou;
}

//ランダム移動X軸
float NpcMove::RandomMoveX()
{
	timer++;
	m_moveSpeed = m_position;
	m_moveSpeed.Normalize();
	if (randomX == 1 || randomX == 5 || randomX == 9) {
		if (timer > 0 && timer <= 7) {
			//移動の向き
			fugou = 1;
			//移動の方向を求める。
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 7) {
				//簡易タイマーリセット
				timer = 0;
				//1～9の乱数取得
				randomX = rand() % 9 + 1;
			}
		}
	}
	if (randomX == 2 || randomX == 4 || randomX == 7) {
		if (timer > 0 && timer <= 7) {
			//移動の向き
			fugou = -1;
			//移動の方向を求める。
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 7) {
				//簡易タイマーリセット
				timer = 0;
				//1～9の乱数取得
				randomX = rand() % 9 + 1;
			}
		}
	}
	if (randomX == 3 || randomX == 6 || randomX == 8) {

		if (timer > 0 && timer <= 7) {
			//移動の向き
			fugou = 0;
			//移動の方向を求める。
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 7) {
				//簡易タイマーリセット
				timer = 0;
				//1～9の乱数取得
				randomX = rand() % 9 + 1;
			}
		}
	}
	//移動の計算を返す。
	return m_moveSpeed.x * 100.0 * fugou;
}

//ランダム移動Z軸
float NpcMove::RandomMoveZ()
{
	timer2++;
	m_moveSpeed = m_position;
	m_moveSpeed.Normalize();
	if (randomZ == 1 || randomZ == 5 || randomZ == 9) {
		if (timer2 > 0 && timer2 <= 7) {
			//移動の向き
			fugou = 1;
			//移動の方向を求める。
			m_position.z += m_moveSpeed.z * fugou;
			if (timer2 == 7) {
				//簡易タイマーリセット
				timer2 = 0;
				//1～9の乱数取得
				randomZ = rand() % 9 + 1;
			}
		}
	}
	if (randomZ == 2 || randomZ == 6 || randomZ == 7) {
		if (timer2 > 0 && timer2 <= 7) {
			//移動の向き
			fugou = -1;
			//移動の方向を求める。
			m_position.z += m_moveSpeed.z * fugou;
			if (timer2 == 7) {
				//簡易タイマーリセット
				timer2 = 0;
				//1～9の乱数取得
				randomZ = rand() % 9 + 1;
			}
		}
	}
	if (randomZ == 3 || randomZ == 4 || randomZ == 8) {

		if (timer2 > 0 && timer2 <= 7) {
			//移動の向き
			fugou = 0;
			//移動の方向を求める。
			m_position.z += m_moveSpeed.z * fugou;
			if (timer2 == 7) {
				//簡易タイマーリセット
				timer2 = 0;
				//1～9の乱数取得
				randomZ = rand() % 9 + 1;
			}
		}
	}
	//移動の計算を返す。
	return m_moveSpeed.z * 100.0 * fugou;
}

