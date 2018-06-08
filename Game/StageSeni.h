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
private:
	int StageNo = 0;
};
	

