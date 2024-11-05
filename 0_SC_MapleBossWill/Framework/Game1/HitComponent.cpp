#include "stdafx.h"

HitComponent::HitComponent()
{
	this->maxHp = 100.f;
	this->currentHp = this->maxHp;
	this->invincibilityTime = 0.f;
	this->_lastHitTime = TIMER->GetWorldTime();
}

HitComponent::~HitComponent()
{
}

bool HitComponent::IsInvincibility()
{
	return (Timer::GetInstance()->GetWorldTime() - _lastHitTime < invincibilityTime);
}

void HitComponent::Hit(float _damage)
{
	if (TIMER->GetWorldTime() - _lastHitTime < invincibilityTime)
	{
		return;
	}

	currentHp -= _damage;

	if (currentHp < 0.f)
	{
		currentHp = 0.f;
	}

	_lastHitTime = TIMER->GetWorldTime();
}