#pragma once
class DarkEnforcer :public CompoObject
{
private:
	Collider* _collider;
	static vector<ObImage*>* GetStartAnim();
	static vector<ObImage*>* GetLoopAnim();
	static vector<ObImage*>* GetAttackAnim();
	vector<ObImage*>* _hitEffectAnim;

	float _time;
	float _playRate;

public:
	DarkEnforcer();
	~DarkEnforcer();

	Vector2 direction;

	float speed;
	AnimState animState;
	Animation* animation;
	CompoObject* player;

	void Update() override;
	void Render() override;

	void Play();
	void SetState(AnimState _animState);
};
