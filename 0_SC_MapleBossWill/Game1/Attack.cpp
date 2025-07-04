#include "stdafx.h"

DelayAttack::DelayAttack(Collider* _collider, CompoObject* _defender, float _damage, float _delay, vector<ObImage*>* _hitAnim)
{
	this->_collider = _collider;
	this->_defender = _defender;
	this->_damage = _damage;
	this->_delay = _delay;
	this->_hitAnim = _hitAnim;
}

bool DelayAttack::Attackfrom()
{
	if (_delay > DELTA)
	{
		_delay -= DELTA;
		return false;
	}
	else
	{
		ATTACK->Attackform(_collider, _defender, _damage, _hitAnim);
		return true;
	}
}

Collider* Attack::GetColliderRef()
{
	Collider* _collider = new Collider();
	_collider->isTrigger = true;
	_collider->enable = false;
	_collider->_collider->pivot = OFFSET_B;
	return _collider;
}

void Attack::Init()
{
	_colliderPool = new vector<Collider*>(10);
	_delayAttacks = new vector<DelayAttack*>(10);
}

void Attack::Attackform(Vector2 _position, Vector2 _scale, CompoObject* _defender, float _damage, float _delay, vector<ObImage*>* _hitAnim)
{
	Collider* _attackCollider = nullptr;

	if (!_colliderPool->empty())
	{
		for (auto& _collider : *_colliderPool)
		{
			if (_collider == nullptr)
			{
				_collider = GetColliderRef();
			}

			if (_collider->enable == false)
			{
				_attackCollider = _collider;
				break;
			}
		}
	}

	if (_attackCollider == nullptr)
	{
		_colliderPool->push_back(GetColliderRef());
		_attackCollider = _colliderPool->back();
	}

	_attackCollider->SetCollider(_position, _scale);
	_attackCollider->enable = true;
	_attackCollider->Update();

	if (!_delayAttacks->empty())
	{
		for (auto& _delayAttack : *_delayAttacks)
		{
			if (_delayAttack == nullptr)
			{
				_delayAttack = new DelayAttack(_attackCollider, _defender, _damage, _delay, _hitAnim);
				return;
			}
		}
	}

	_delayAttacks->push_back(new DelayAttack(_attackCollider, _defender, _damage, _delay, _hitAnim));
}

void Attack::Attackform(Collider* _collider, CompoObject* _defender, float _damage, vector<ObImage*>* _hitAnim)
{
	_collider->Update();

	if (_defender != nullptr)
	{
		if (_collider->Intersect(_defender) == true)
		{
			HitComponent* _hitComponent = _defender->GetComponent<HitComponent>();
			if (_hitComponent != nullptr)
			{
				if (_hitAnim != nullptr && !_hitComponent->IsInvincibility())
				{
					EFFECT->PlayEffect(_defender->GetWorldPivot(), _hitAnim);
				}
				_hitComponent->Hit(_damage);
			}
		}
	}

	_collider->enable = false;
}

void Attack::Update()
{
	if (!_delayAttacks->empty())
	{
		for (auto& _delayAttack : *_delayAttacks)
		{
			if (_delayAttack == nullptr)
			{
				continue;
			}

			if (_delayAttack->Attackfrom() == true)
			{
				SafeDelete(_delayAttack)
			}
		}
	}
}

void Attack::Render()
{
	if (!_colliderPool->empty())
	{
		for (auto& _collider : *_colliderPool)
		{
			if (_collider == nullptr)
			{
				continue;
			}

			if (_collider->enable == true)
			{
				_collider->Render();
			}
		}
	}
}