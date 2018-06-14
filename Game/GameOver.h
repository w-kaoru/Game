#pragma once
class GameOver
{
public:
	GameOver();
	~GameOver();
	void SetGameOver(bool k) 
	{
		GOflag = k;
	}
	bool GetGameOver() 
	{
		return GOflag;
	}
private:
	bool GOflag = false;
};

