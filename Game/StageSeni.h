#pragma once

class Player;
class Fade;
class Title;
class StageSeni:public IGameObject
{
public:
	StageSeni();
	~StageSeni();
	int GetSNo() 
	{
		return StageNo;
	}
	void SetSNo()
	{
		if (StageNo <= 1) {
			StageNo += 1;
		}
		else {
			StageNo = 0;
		}
	}
	void SetGameOver() 
	{
		StageNo = 0;
	}
private:
	//ステージ遷移の番号
	int StageNo = 0;
};
	

