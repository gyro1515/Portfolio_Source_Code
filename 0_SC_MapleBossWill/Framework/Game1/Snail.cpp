#include "stdafx.h"

Snail::Snail()
{
	snail = *new vector<ObImage*>(3);
	snail[0] = new ObImage(L"´ÞÆØÀÌ (1).png");
	snail[1] = new ObImage(L"´ÞÆØÀÌ (2).png");
	snail[2] = new ObImage(L"´ÞÆØÀÌ (3).png");
	for (auto& _image : snail)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	snailHit = *new vector<ObImage*>(6);
	snailHit[0] = new ObImage(L"´ÞÆØÀÌÈ÷Æ® (1).png");
	snailHit[1] = new ObImage(L"´ÞÆØÀÌÈ÷Æ® (2).png");
	snailHit[2] = new ObImage(L"´ÞÆØÀÌÈ÷Æ® (3).png");
	snailHit[3] = new ObImage(L"´ÞÆØÀÌÈ÷Æ® (4).png");
	snailHit[4] = new ObImage(L"´ÞÆØÀÌÈ÷Æ® (5).png");
	snailHit[5] = new ObImage(L"´ÞÆØÀÌÈ÷Æ® (6).png");
	for (auto& _image : snailHit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	this->_duration = 0.5f;
	this->enemy = nullptr;

	animation = AddComponent<Animation>();
	animation->SetAnimation(&snail);
	animation->isLoop = true;

	this->_collider = AddComponent<Collider>();
	this->_collider->SetCollider(this, this->scale);
	this->isVisible = false;

	SOUND->AddSound("Snail.mp3", "snail");
}

Snail::~Snail()
{
}

void Snail::Update()
{
	if (this->isVisible)
	{
		if (_duration > 0.f)
		{
			MoveWorldPos(this->_direction * 500.f * DELTA);
			if (this->enemy != nullptr)
			{
				if (this->_collider->Intersect(this->enemy))
				{
					HitComponent* hitComponent = enemy->GetComponent<HitComponent>();
					hitComponent->Hit(10.f);

					GameObject::Update();
					EFFECT->PlayEffect(GetWorldPos(), &snailHit);
					this->isVisible = false;
				}
			}
		}
		else
		{
			this->isVisible = false;
		}

		CompoObject::Update();
	}

	if (_duration > 0.f)
	{
		_duration -= DELTA;
	}
}

void Snail::Render()
{
	if (this->isVisible)
	{
		CompoObject::Render();
	}
}

void Snail::Throw(Vector2 _position, Vector2 _direction)
{
	if (this->_duration > 0.f)
	{
		return;
	}

	SOUND->Stop("snail");
	SOUND->Play("snail");
	SetWorldPos(_position);
	this->_direction = _direction;
	this->isVisible = true;
	this->_duration = 0.5f;
	CompoObject::Update();
}