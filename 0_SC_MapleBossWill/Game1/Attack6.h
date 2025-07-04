#pragma once
class Attack6
{
public:
	vector<ObImage*> attack6Img;
	vector<ObImage*> attack6Hit;

public:
	Attack6();
	~Attack6();
	void Update();
	void LateUpdate();
	void Render();
};
