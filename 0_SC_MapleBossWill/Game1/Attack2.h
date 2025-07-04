#pragma once
class Attack2
{
public:
	ObImage* attack2[20];
	vector<ObImage*> attack2Img;
	vector<ObImage*> attack2Hit;

public:
	Attack2();
	~Attack2();
	void Update();
	void LateUpdate();
	void Render();
};
