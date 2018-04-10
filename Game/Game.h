#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "Level.h"


class Fade;
class Background;
class Player;
class GameCamera;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void OnDestroy();
	void Render(CRenderContext& rc);
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
	Background* m_background = nullptr;
	GameCamera*m_gameCamera = nullptr;
	Level m_level;							//レベル。
};

