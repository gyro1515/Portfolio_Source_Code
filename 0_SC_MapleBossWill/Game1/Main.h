#pragma once

class Main : public Scene
{
private:
	ObImage* img[31];
	float imgCount;
	Attack1* attack1;
	Attack2* attack2;

	Will* will;
	Player* player;
	Phase2* phase2;

	BeholderBody* beholderBodys[2];

	SpiderLeg* spiderLegs[2];
	SpiderLeg* spiderLegs2[2];
	SpiderLeg* spiderLegs3[3];
	SpiderLegMirror* spiderLegMirrors[2];
	SpiderLegMirror* spiderLegMirrors2[2];
	SpiderLegMirror* spiderLegMirrors3[2];

	DarkEnforcer* darkEnforcers[3];

	HpBar* willHpBar;
	HpBar* playerHpBar;

	int phase;
	int soundCount;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
