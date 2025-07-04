#pragma once
class Phase3 :public CompoObject
{
public:

	AnimState animState;
	Animation* animation;

public:
	Phase3();
	~Phase3();

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Show();
};

