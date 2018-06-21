#pragma once
class Player;
class Game;
class StageSeni;
class Fade;
class Title;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void SetGameOver(bool k)
	{
		GOflag = k;
	}
	bool GetGameOver()
	{
		return GOflag;
	}
private:
	Player* pl = nullptr;
	float taim = 0.0f;
	CVector3 position = CVector3::Zero;
	bool GOflag = false;
	Fade* m_fade = nullptr;
	StageSeni* m_ss = nullptr;
	Game* game = nullptr;
	bool m_isWaitFadeout = false;
	int a = 0;
};

