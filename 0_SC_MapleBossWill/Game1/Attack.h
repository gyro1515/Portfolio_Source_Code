#pragma once
class DelayAttack
{
private:
	Collider* _collider;
	CompoObject* _defender;
	float _damage;
	float _delay;
	vector<ObImage*>* _hitAnim;

public:
	DelayAttack() = default;
	DelayAttack(Collider* _collider, CompoObject* _defender, float _damage, float _delay, vector<ObImage*>* _hitAnim);

	bool Attackfrom();
};

class Attack :public Singleton<Attack>
{
private:
	Collider* GetColliderRef();

	vector<Collider*>* _colliderPool;

	vector<DelayAttack*>* _delayAttacks;

public:
	void Init();

	void Attackform(Vector2 _position, Vector2 _scale, CompoObject* _defender, float _damage, float _delay = 0.f, vector<ObImage*>* _hitAnim = nullptr);

	void Attackform(Collider* _collider, CompoObject* _defender, float _damage, vector<ObImage*>* _hitAnim);

	void Update();

	void Render();
};

#define ATTACK Attack::GetInstance()