#pragma once
class Attack1
{
public:
	vector<ObImage*> attack1Img;
	vector<ObImage*> attack1Hit;

public:
	Attack1();
	~Attack1();
	void Update();
	void LateUpdate();
	void Render();
};
