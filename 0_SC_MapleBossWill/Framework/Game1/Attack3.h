#pragma once
class Attack3
{
public:
	vector<ObImage*> attack3Img;
	vector<ObImage*> attack3Hit;

public:
	Attack3();
	~Attack3();
	void Update();
	void LateUpdate();
	void Render();
};
