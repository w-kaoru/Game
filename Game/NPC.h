#pragma once
//キャラクターコントローラーを使用する場合は、下記のヘッダーファイルのインクルードが必要。
#include "tkEngine/character/tkCharacterController.h"
#include "NpcMove.h"

class Game;
class Player;
class NPC : public IGameObject
{
public:
	NPC(); 
	~NPC();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	prefab::CSkinModelRender* m_skinModelRender;	        //スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero;                   //座標。
	CVector3 m_moveSpeed;                                   //移動速度。
	CQuaternion m_rotation = CQuaternion::Identity;         //回転。
	CCharacterController m_charaCon; 
	NpcMove m_npcMove;

	Game *m_game = nullptr;
	Player *m_player = nullptr;
	float angle=0.0f;
	int flag = 0;
	enum kanjou {
		flat,             //平常
		delighted,        //喜ぶ
		angry,            //怒り
		sad,              //哀しい
		pleasant,         //楽しい
		kanjouNum,        //感情の数
	};
	enum kanjou npckanjou =flat;
};

