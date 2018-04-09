#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Fade;
class NPC;
class Test : public IGameObject
{
public:
	Test();
	~Test();
	bool Start();
	void Update();
private:
	enum EnState {
		enState_FadeIn,	//!<フェードイン中。
		enState_InGame,	//!<インゲーム中。
	};
	bool m_isWaitFadeout = false;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	//CAnimationClip m_animClip[1];							//アニメーションクリップ。
	//CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	NPC * m_npc = nullptr;
};


