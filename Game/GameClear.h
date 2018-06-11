#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Game;
class Player;
class StageSeni;

class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();

	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	Player* pl = nullptr;
	CVector3 m_pos = CVector3::Zero;
	StageSeni* m_ss = nullptr;
	//エフェクトを作成。
	prefab::CEffect* effect = nullptr;
	int Gtime = 0;
};