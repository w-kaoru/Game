#pragma once

class Player;
class Fade;
class Title;
class StageSeni:public IGameObject
{
public:
	StageSeni();
	~StageSeni();
	bool Start();
	void Update();
	void OnDestroy();
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
private:
	Title * m_tl = nullptr;
	Player* m_pl = nullptr;
	int StageNo = 0;
};
	

