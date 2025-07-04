#pragma once
class SpiderLeg :public CompoObject
{
private:
	static vector<ObImage*>* GetAnim();
	vector<ObImage*>* _hitEffectAnim;
	Animation* _animation;

public:
	SpiderLeg();
	~SpiderLeg();
	float _playRate;

	CompoObject* player;

	void Play();

	void Update() override;
	void Render() override;
};
