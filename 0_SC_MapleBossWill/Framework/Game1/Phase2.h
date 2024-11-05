#pragma once
class Phase2 :public CompoObject
{
public:
	AnimState animState;
	Animation* animation;

	vector<ObImage*> phase2;
	vector<ObImage*> phase3;

public:
	Phase2();
	~Phase2();

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Show();
	void SetState(AnimState _animState);

};

