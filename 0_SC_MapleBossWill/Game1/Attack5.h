#pragma once
class Attack5
{
public:
	vector<ObImage*> attack5Img;
	vector<ObImage*> attack5Hit;

public:
	Attack5();
	~Attack5();
	void Update();
	void LateUpdate();
	void Render();
};
