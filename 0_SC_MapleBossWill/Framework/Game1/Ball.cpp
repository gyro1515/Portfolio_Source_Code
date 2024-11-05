#include "stdafx.h"

vector<ObImage*>* Ball::GetLoopAnim()
{
	static vector<ObImage*> attack7BallImg;
	if (attack7BallImg.size() == 0)
	{
		attack7BallImg = *new vector<ObImage*>(8);
		attack7BallImg[0] = new ObImage(L"attack7_ball (1).png");
		attack7BallImg[1] = new ObImage(L"attack7_ball (2).png");
		attack7BallImg[2] = new ObImage(L"attack7_ball (3).png");
		attack7BallImg[3] = new ObImage(L"attack7_ball (4).png");
		attack7BallImg[4] = new ObImage(L"attack7_ball (5).png");
		attack7BallImg[5] = new ObImage(L"attack7_ball (6).png");
		attack7BallImg[6] = new ObImage(L"attack7_ball (7).png");
		attack7BallImg[7] = new ObImage(L"attack7_ball (8).png");
		for (auto& _image : attack7BallImg)
		{
			_image->animInterval = 0.09f;
			_image->SetWorldPos(Vector2(0.0f, -130.0f));
		}
	}

	return &attack7BallImg;
}

Ball::Ball()
{
	this->direction = Vector2(0.f, 0.f);
	this->speed = 200.f;

	this->_collider = AddComponent<Collider>();
	this->_collider->SetCollider(this, Vector2(200.f, 100.f));

	this->player = nullptr;

	this->animation = AddComponent<Animation>();

	this->animState = AnimState::Loop;

	hitAnim = new vector<ObImage*>(7);
	(*hitAnim)[0] = new ObImage(L"attack7_hit (1).png");
	(*hitAnim)[1] = new ObImage(L"attack7_hit (2).png");
	(*hitAnim)[2] = new ObImage(L"attack7_hit (3).png");
	(*hitAnim)[3] = new ObImage(L"attack7_hit (4).png");
	(*hitAnim)[4] = new ObImage(L"attack7_hit (5).png");
	(*hitAnim)[5] = new ObImage(L"attack7_hit (6).png");
	(*hitAnim)[6] = new ObImage(L"attack7_hit (7).png");

	for (auto& _image : (*hitAnim))
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos(Vector2(-6.f, 9.f));
		//_image->SetWorldPos();
	}

	this->isVisible = false;
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (!this->isVisible)
	{
		return;
	}

	GameObject::Update();

	this->MoveWorldPos(this->direction * this->speed * DELTA);

	if (this->GetWorldPivot().x > app.GetHalfWidth() || this->GetWorldPivot().x < -app.GetHalfWidth() ||
		this->GetWorldPivot().y > app.GetHalfHeight() || this->GetWorldPivot().y < -app.GetHalfHeight())
	{
		this->isVisible = false;
	}
	GameObject::Update();

	if (this->player != nullptr)
	{
		if (this->_collider->Intersect(this->player))
		{
			HitComponent* hitComponent = player->GetComponent<HitComponent>();
			if (!hitComponent->IsInvincibility())
			{
				EFFECT->PlayEffect(player->GetWorldPos(), hitAnim);
			}

			hitComponent->Hit(1.f);

			//this->isVisible = false;
		}
	}
	CompoObject::Update();
}

void Ball::Render()
{
	if (!this->isVisible)
	{
		return;
	}

	CompoObject::Render();
}

void Ball::SetState(AnimState _animState)
{
	this->animState = _animState;

	switch (this->animState)
	{
	case AnimState::Loop:
		this->animation->SetAnimation(GetLoopAnim());
		this->animation->isLoop = true;
		break;
	default:
		break;
	}
}

void Ball::Shoot(Vector2 _direction, Vector2 _shootPos)
{
	this->isVisible = true;
	this->direction = _direction;
	this->speed = 200.f;
	this->SetWorldPos(_shootPos);
	this->SetState(AnimState::Loop);
}