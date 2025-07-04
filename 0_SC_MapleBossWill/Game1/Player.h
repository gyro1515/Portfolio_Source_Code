#pragma once
class Player :public CompoObject
{
public:
	AnimState animState;
	Animation* animation;

	vector<ObImage*> standImg;
	vector<ObImage*> wlakImg;
	vector<ObImage*> jumpImg;
	vector<ObImage*> swingImg;
	vector<ObImage*> downImg;
	vector<ObImage*> fightImg;

	vector<ObImage*> jumpjumpImg1;
	vector<ObImage*> jumpjumpImg2;
	vector<ObImage*> highJumpImg1;
	vector<ObImage*> highJumpImg2;

	vector<ObImage*> snail;
	vector<ObImage*> snailHit;

	CompoObject* enemy;

	PlayerJump playerJump;

	Snail snailObject;

	CompoObject jumpEffect;
	Animation* jumpEffectAnimation;

public:
	Player();
	~Player();

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Show();

	void SetState(AnimState _animState);
};
