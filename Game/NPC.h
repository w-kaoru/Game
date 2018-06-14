#pragma once
//キャラクターコントローラーを使用する場合は、下記のヘッダーファイルのインクルードが必要。
#include "tkEngine/character/tkCharacterController.h"
#include "NpcMove.h"
#include "Game.h"
class Game;
class Player;


class NPC : public IGameObject
{
private:
	void UpdateState();
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
	CVector3 plpo;                                          //NPCとPlayerの距離。
	CQuaternion m_rotation = CQuaternion::Identity;         //回転。
	CCharacterController m_charaCon; 
	NpcMove m_npcMove;

	Game *m_game = nullptr;
	Player *m_player = nullptr;
	prefab::CSoundSource* m_soundSource = nullptr;
	prefab::CSoundSource* m_soundSource2 = nullptr;
	NPC*pNpc;
	int soundflag = 0;
	bool HitWall = false;
	int movetime = 0;

	float angle= 0.0f;
	int flag = 0;
	int sevo = 0;
	int osouvo = rand() % 3 + 1;
	
	enum state {
		haikai,			//徘徊
		tuibi,			//追尾。
		osou,           //襲う。
	};
	enum kanjou npckanjou =flat;
	enum state npcState = haikai;
private:
	void UpdateKanjouStage1();
	void UpdateKanjouStage2();
	void UpdateKanjouStage3();

};

