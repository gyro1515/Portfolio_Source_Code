#include "stdafx.h"

HpBar::HpBar(CompoObject* gameObject)
{
	HitComponent* _hitComponent = gameObject->GetComponent<HitComponent>();

	if (_hitComponent == nullptr)
	{
		_hitComponent = gameObject->AddComponent<HitComponent>();
	}

	this->currentHp = &_hitComponent->currentHp;
	this->maxHp = &_hitComponent->maxHp;

	for (auto& _obRect : hpBar)
	{
		_obRect.pivot = OFFSET_L;
		_obRect.SetParentT(*this);
	}

	hpBar[0].color = Color(1.f, 1.f, 1.f, 1.f);
	hpBar[1].color = Color(1.f, 0.f, 0.f, 1.f);
}

void HpBar::Update()
{
	hpBar[1].scale.x = hpBar[0].scale.x * (*currentHp / *maxHp);

	CompoObject::Update();

	for (auto& _obRect : hpBar)
	{
		_obRect.Update();
	}
}

void HpBar::Render()
{
	CompoObject::Render();

	for (auto& _obRect : hpBar)
	{
		_obRect.Render();
	}
}

void HpBar::SetBarScale(Vector2 _scale)
{
	for (auto& _obRect : hpBar)
	{
		_obRect.scale = _scale;
	}
}