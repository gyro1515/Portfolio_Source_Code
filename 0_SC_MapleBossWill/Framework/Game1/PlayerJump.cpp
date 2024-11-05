#include "stdafx.h"

PlayerJump::PlayerJump()
{
	this->_force = 0.f;
	this->floorHeight = 0.f;

	this->player = nullptr;

	this->_gravity = 0.f;
	this->_direction = Vector2(0.f, 0.f);

	this->jumpCount = 0;
}

void PlayerJump::Jump(Vector2 _direction, float _force)
{
	this->_force += _force;
	this->_direction = _direction;
	//cout << "JUMP\n";
	//this->_gravity = 0.f;
	player->SetState(AnimState::Jump);
	jumpCount++;
}

void PlayerJump::Update()
{
	if (player == nullptr)
	{
		return;
	}
	if (_force > 0.f)
	{
		player->MoveWorldPos(_direction * _force * DELTA);
		player->GameObject::Update();

		if (player->GetWorldPivot().y > floorHeight)
		{
			_gravity += 9.8f * DELTA;

			player->MoveWorldPos(DOWN * this->_gravity);
		}
		else
		{
			player->SetWorldPosY(floorHeight);
			_force = 0.f;
			_gravity = 0.f;
			jumpCount = 0;
			//cout << "end\n";
			player->SetState(AnimState::Stand);
		}
	}
}