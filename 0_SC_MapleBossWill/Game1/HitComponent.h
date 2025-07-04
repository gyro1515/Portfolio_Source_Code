#pragma once
class HitComponent : public Component
{
private:
	float _lastHitTime;

public:
	HitComponent();
	~HitComponent();

	float maxHp;
	float currentHp;
	float invincibilityTime;

	bool IsInvincibility();

	void Hit(float _damage);
};
