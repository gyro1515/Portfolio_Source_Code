#pragma once
class SpiderLegMirror :public CompoObject
{
private:
	static vector<ObImage*>* GetAnim();
	vector<ObImage*>* _hitEffectAnim;
	Animation* _animation;

public:
	SpiderLegMirror();
	~SpiderLegMirror();
	float _playRate;

	CompoObject* player;

	void Play();

	void Update() override;
	void Render() override;
};
