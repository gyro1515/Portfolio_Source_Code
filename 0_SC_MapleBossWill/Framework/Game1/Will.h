#pragma once
class Will :public CompoObject
{
public:
	vector<ObImage*> mapImg;

	float imgCount;
	bool right; //�� ������ �ٶ� �������θ� �� ���� �ϱ�

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
