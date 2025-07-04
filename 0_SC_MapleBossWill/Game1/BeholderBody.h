#pragma once
class BeholderBody :public CompoObject
{
private:
	static vector<ObImage*>* GetStartAnim();
	static vector<ObImage*>* GetLoopAnim();
	static vector<ObImage*>* GetEndAnim();
	vector<ObImage*>* shootEffectAnim;

private:
	int _spawnCount;

	float _playRate;

	Animation* animation;

	AnimState animState;
	void SetState(AnimState _animState);

public:
	BeholderBody();
	~BeholderBody();

	BeholderBullet _bulletPool[10];
	CompoObject* player;

	void Play();

	void Update() override;
	void Render() override;
};
