#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void PostRender(CRenderContext& rc) override;
private:
	//フェイドアウト　ゲーム
	bool m_isWaitFadeout = false;
	//フェイドアウト　テスト
	bool m_isWaitFadeout2 = false;
	CShaderResourceView m_texture;
	CSprite m_sprite;
	Fade* m_fade = nullptr;
	CFont m_font;
	float m_intiBgmVolume = 0.0f;
};


