#pragma once
class Will :public CompoObject
{
public:
	vector<ObImage*> mapImg;

	float imgCount;
	bool right; //윌 돌진시 바라본 방향으로만 쭉 가게 하기

	AnimState animState;
	Animation* animation;

	CompoObject* player;
	Ball ball;
	Random* rand;
public:
	Will();
	~Will();

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Show();

	void SetState(AnimState _animState);
};
