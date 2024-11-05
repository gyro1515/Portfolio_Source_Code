#pragma once
class Effect :public Singleton<Effect>
{
private:
	vector<Animation> _effectAnimPool;

public:
	Effect();

	void PlayEffect(Vector2 _playPosition, vector<ObImage*>* _effectImages);

	void Update();
	void Render();
};

#define EFFECT Effect::GetInstance()