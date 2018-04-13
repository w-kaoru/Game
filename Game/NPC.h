#pragma once
class Game;
class NPC : public IGameObject
{
public:
	NPC(); 
	~NPC();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	////////////////////////////////////
	// メンバ変数とか
	////////////////////////////////////
	//enum EnAnimationClip {
	//	enAnimationClip_idle,	//待機アニメーション。
	//	enAnimationClip_run,	//走りアニメーション。
	//	enAnimationClip_walk,	//歩きアニメーション。
	//	enAnimationClip_num,	//アニメーションクリップの総数。
	//};
	//CAnimationClip m_animationClip[enAnimationClip_num];	//アニメーションクリップ。
	prefab::CSkinModelRender* m_skinModelRender[30];	//スキンモデルレンダラー。
	CVector3 m_position[30];	//座標。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	//CCharacterController m_charaCon;		//キャラクターコントローラー。
	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	Game *m_game = nullptr;
	int i = 0;
};

