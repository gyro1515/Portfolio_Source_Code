#include "stdafx.h"

vector<ObImage*>* BeholderBullet::GetLoopAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(8);
		wstring _path = L"Beholder/bullet/";
		_images[0] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (1).png");
		_images[1] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (2).png");
		_images[2] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (3).png");
		_images[3] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (4).png");
		_images[4] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (5).png");
		_images[5] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (6).png");
		_images[6] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (7).png");
		_images[7] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_·çÇÁ (8).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.08f;
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

vector<ObImage*>* BeholderBullet::GetHitAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(10);
		wstring _path = L"Beholder/bullet/";
		_images[0] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (1).png");
		_images[1] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (2).png");
		_images[2] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (3).png");
		_images[3] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (4).png");
		_images[4] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (5).png");
		_images[5] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (6).png");
		_images[6] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (7).png");
		_images[7] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (8).png");
		_images[8] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (9).png");
		_images[9] = new ObImage(_path + L"»¡°£´«_ÃÑ¾Ë_È÷Æ® (10).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			_image->SetWorldPos(Vector2(-6.f, 9.f));
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

BeholderBullet::BeholderBullet()
{
	this->direction = Vector2(0.f, 0.f);
	this->speed = 200.f;

	this->_collider = AddComponent<Collider>();
	this->_collider->SetCollider(this, Vector2(20.f, 20.f));

	this->player = nullptr;

	this->animation = AddComponent<Animation>();

	this->animState = AnimState::Loop;

	this->isVisible = false;
}

BeholderBullet::~BeholderBullet()
{
}

void BeholderBullet::Update()
{
	if (!this->isVisible)
	{
		return;
	}

	CompoObject::Update();

	this->MoveWorldPos(this->direction * this->speed * DELTA);

	if (this->GetWorldPivot().x > app.GetHalfWidth() || this->GetWorldPivot().x < -app.GetHalfWidth() ||
		this->GetWorldPivot().y > app.GetHalfHeight() || this->GetWorldPivot().y < -app.GetHalfHeight())
	{
		this->isVisible = false;
	}

	if (this->animation->IsOver())
	{
		switch (this->animState)
		{
		case AnimState::Loop:
			this->SetState(AnimState::Hit1);
			break;
		case AnimState::Hit1:
			this->isVisible = false;
			break;
		default:
			break;
		}
	}

	if (this->player != nullptr && this->animation->isLoop)
	{
		if (this->_collider->Intersect(this->player))
		{
			this->player->GetComponent<HitComponent>()->Hit(10.f);
			this->animation->isLoop = false;
		}
	}
}

void BeholderBullet::Render()
{
	if (!this->isVisible)
	{
		return;
	}

	CompoObject::Render();
}

void BeholderBullet::SetState(AnimState _animState)
{
	this->animState = _animState;

	switch (this->animState)
	{
	case AnimState::Loop:
		this->animation->SetAnimation(GetLoopAnim());
		this->animation->isLoop = true;
		break;
	case AnimState::Hit1:
		this->speed = 0.f;
		this->animation->SetAnimation(GetHitAnim());
		this->animation->isLoop = false;
		break;
	default:
		break;
	}
}

void BeholderBullet::Shoot(Vector2 _direction, Vector2 _shootPos)
{
	this->isVisible = true;
	this->direction = _direction;
	this->speed = 200.f;
	this->SetWorldPos(_shootPos);
	this->SetState(AnimState::Loop);
}