#include "stdafx.h"

Collider::Collider()
{
	this->_collider = new ObRect();
	_collider->collider = COLLIDER::RECT;
	this->isTrigger = false;
	this->_collider->color = Color(0.f, 1.f, 0.f);
	this->_collider->isFilled = false;
	//this->_collider->isVisible = false;
}

Collider::~Collider()
{
	SafeDelete(this->_collider);
}

void Collider::Update()
{
	this->_collider->Update();
}

void Collider::Render()
{
	this->_collider->Render();
}

void Collider::SetCollider(CompoObject* _parents, Vector2 _scale)
{
	this->_collider->SetParentT(*_parents);
	this->_collider->scale = _scale;
}

void Collider::SetCollider(Vector2 _position, Vector2 _scale)
{
	this->_collider->SetWorldPos(_position);
	this->_collider->scale = _scale;
}

bool Collider::Intersect(CompoObject* _collisionObject)
{
	Collider* _targetCollider = _collisionObject->GetComponent<Collider>();
	if (_targetCollider != nullptr)
	{
		return this->_collider->Intersect(_targetCollider->_collider);
	}

	return false;
}