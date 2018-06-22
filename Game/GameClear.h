#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "GameOver.h"
#include "Fade.h"
class Game;
class Player;
class Fade;
class StageSeni;
class Title;

class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();

	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	Player* pl = nullptr;
	Game* game = nullptr;
	CVector3 m_pos = CVector3::Zero;
	StageSeni* m_ss = nullptr;
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	GameOver m_gameover;
	//エフェクトを作成。
	prefab::CEffect* effect = nullptr;
	int Gtime = 0;
};