#pragma once
class Attack4
{
public:
	vector<ObImage*> attack4Img;
	vector<ObImage*> attack4Hit;

public:
	Attack4();
	~Attack4();
	void Update();
	void LateUpdate();
	void Render();
};
