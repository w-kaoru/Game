#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "Level.h"


class Fade;
class StageSeni;
class Background;
class Player;
class GameCamera;
class NPC;

enum kanjou {
	flat,             //平常
	delighted,        //喜ぶ
	angry,            //怒り
	sad,              //哀しい
	pleasant,         //楽しい
	kanjouNum,        //感情の数
};

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void OnDestroy();
	void Render(CRenderContext& rc);
	Level m_level;		//レベル。
	std::vector<NPC*>	m_npcList;	//NPCの可変長配列。

private:
	enum EnState {
		enState_FadeIn,	//!<フェードイン中。
		enState_InGame,	//!<インゲーム中。
	};
	bool m_isWaitFadeout = false;
	CVector3 m_pos = CVector3::Zero;
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	Player*m_player = nullptr;
	prefab::CSoundSource* m_soundSource = nullptr;
	Background* m_background = nullptr;
	GameCamera*m_gameCamera = nullptr;
	prefab::CDirectionLight* m_sunLig = nullptr;
	StageSeni* m_ss = nullptr;
	CLocData locData;
	int counter = 0;
};
