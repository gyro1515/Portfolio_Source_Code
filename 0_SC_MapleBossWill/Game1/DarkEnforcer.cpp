#include "stdafx.h"

vector<ObImage*>* DarkEnforcer::GetStartAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(10);
		wstring _path = L"DarkEnforcer/";
		_images[0] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (1).png");
		_images[1] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (2).png");
		_images[2] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (3).png");
		_images[3] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (4).png");
		_images[4] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (5).png");
		_images[5] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (6).png");
		_images[6] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (7).png");
		_images[7] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (8).png");
		_images[8] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (9).png");
		_images[9] = new ObImage(_path + L"ÆÄ¶õ´«_»ý¼º (10).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.12f;
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

vector<ObImage*>* DarkEnforcer::GetLoopAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(8);
		wstring _path = L"DarkEnforcer/";
		_images[0] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (1).png");
		_images[1] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (2).png");
		_images[2] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (3).png");
		_images[3] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (4).png");
		_images[4] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (5).png");
		_images[5] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (6).png");
		_images[6] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (7).png");
		_images[7] = new ObImage(_path + L"ÆÄ¶õ´«_ÇÃ¶óÀÌ (8).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.09f;
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

vector<ObImage*>* DarkEnforcer::GetAttackAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(9);
		wstring _path = L"DarkEnforcer/";
		_images[0] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (1).png");
		_images[1] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (2).png");
		_images[2] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (3).png");
		_images[3] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (4).png");
		_images[4] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (5).png");
		_images[5] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (6).png");
		_images[6] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (7).png");
		_images[7] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (8).png");
		_images[8] = new ObImage(_path + L"ÆÄ¶õ´«_Æø¹ß (9).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

DarkEnforcer::DarkEnforcer()
{
	this->_collider = AddComponent<Collider>();
	this->_collider->SetCollider(this, Vector2(40.f, 40.f));
	this->animation = AddComponent<Animation>();
	this->player = nullptr;
	this->speed = 100.f;
	this->animState = AnimState::Start;

	this->_time = 0.f;
	this->_playRate = 10.f;
	this->isVisible = false;

	this->_hitEffectAnim = new vector<ObImage*>(5);
	wstring _path = L"DarkEnforcer/";
	(*_hitEffectAnim)[0] = new ObImage(_path + L"ÆÄ¶õ´« È÷Æ® (1).png");
	(*_hitEffectAnim)[1] = new ObImage(_path + L"ÆÄ¶õ´« È÷Æ® (2).png");
	(*_hitEffectAnim)[2] = new ObImage(_path + L"ÆÄ¶õ´« È÷Æ® (3).png");
	(*_hitEffectAnim)[3] = new ObImage(_path + L"ÆÄ¶õ´« È÷Æ® (4).png");
	(*_hitEffectAnim)[4] = new ObImage(_path + L"ÆÄ¶õ´« È÷Æ® (5).png");

	for (auto& _image : *_hitEffectAnim)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	SOUND->AddSound("blyeEye Regen.mp3", "darkEnforcerRegen");
	SOUND->AddSound("blueEye Attack1.mp3", "darkEnforcerAttack");
}

DarkEnforcer::~DarkEnforcer()
{
}

void DarkEnforcer::Update()
{
	if (INPUT->KeyDown('L'))
	{
		this->Play();
	}

	if (this->isVisible)
	{
		if (animation->IsOver())
		{
			switch (this->animState)
			{
			case AnimState::Start:
				SetState(AnimState::Loop);
				break;
			case AnimState::Loop:
				break;
			case AnimState::End:
				this->isVisible = false;
				this->_playRate = 10.f;
				break;
			default:
				break;
			}
		}

		if (this->animState == AnimState::Loop)
		{
			this->_time += DELTA;
			Vector2 targetPos = player->GetWorldPivot();
			targetPos.y += 50.f * sinf(this->_time * 4.f);
			this->direction = targetPos - this->GetWorldPivot();
			this->direction.Normalize();
			this->MoveWorldPos(this->direction * this->speed * DELTA);
			GameObject::Update();
			if (_collider->Intersect(player))
			{
				Vector2 attackPos = this->GetWorldPos();
				attackPos.y -= 40.f;
				ATTACK->Attackform(attackPos, this->_collider->_collider->scale * 2.f, player, 10.f, 0.24f, _hitEffectAnim);
				SetState(AnimState::End);
			}
		}
		CompoObject::Update();
	}
	else
	{
		if (this->_playRate > 0.f)
		{
			this->_playRate -= DELTA;
		}
		else
		{
			this->Play();
		}
	}
}

void DarkEnforcer::Render()
{
	if (isVisible)
	{
		CompoObject::Render();
	}
}

void DarkEnforcer::Play()
{
	this->isVisible = true;
	SetState(AnimState::Start);
	SOUND->Stop("darkEnforcerRegen");
	SOUND->Play("darkEnforcerRegen");
}

void DarkEnforcer::SetState(AnimState _animState)
{
	this->animState = _animState;

	switch (this->animState)
	{
	case AnimState::Start:
		this->animation->SetAnimation(GetStartAnim());
		this->animation->isLoop = false;
		break;
	case AnimState::Loop:
		this->animation->SetAnimation(GetLoopAnim());
		this->animation->isLoop = true;
		break;
	case AnimState::End:
		this->animation->SetAnimation(GetAttackAnim());
		this->animation->isLoop = false;
		SOUND->Stop("darkEnforcerAttack");
		SOUND->Play("darkEnforcerAttack");
		break;
	default:
		break;
	}
}