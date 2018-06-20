#pragma once
//キャラクターコントローラーを使用する場合は、下記のヘッダーファイルのインクルードが必要。
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class GameClear;
class StageSeni;
class NPC;

class Player :public IGameObject
{
public:
	Player();
	~Player();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	//感情に合わせたエフェクト再生。
	void Effect(CVector3 npcpos, CQuaternion npcrot);
	//ステージに合わせた感情の移り変わり
	void UpdatekanjouSt1();

	//移動処理。
	void Move();
	void Turn();
	//ゲッター、セッター
	int GetfollowerNum()
	{
		return followerNum;
	}
	int Getef_flag()
	{
		return ef_flag;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	CVector3 GetPlforward()
	{
		return m_plforward;
	}
	void Setef_flag()
	{
		ef_flag++;
	}
	void SetfollowerNump() 
	{
		followerNum++;
	}
	void SetfollowerNumm()
	{
		followerNum--;
	}
	void Setplkan(bool k)
	{
		plkan = k;
	}
	////////////////////////////////////
	// メンバ変数とか
	////////////////////////////////////
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero;	//座標。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	CCharacterController m_charaCon;		//キャラクターコントローラー。
	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	//付いて来ている人間の数。
	GameClear* m_gc = nullptr;
	CVector3 m_plforward = CVector3::Zero;
	NPC* m_npc = nullptr;
	//エフェクトを作成。
	prefab::CEffect* effect = nullptr;
	StageSeni* m_ss = nullptr;
	enum kanjou plkanjou;
	bool plkan = false;
	int ef_flag = 0;						//エフェクトのフラグ。
	int followerNum = 0;			
};
