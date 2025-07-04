#include "stdafx.h"

vector<ObImage*>* SpiderLeg::GetAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(30);
		wstring _path = L"SpiderLeg/";
		_images[0] = new ObImage(_path + L"거미다리 (1).png");
		_images[1] = new ObImage(_path + L"거미다리 (2).png");
		_images[2] = new ObImage(_path + L"거미다리 (3).png");
		_images[3] = new ObImage(_path + L"거미다리 (4).png");
		_images[4] = new ObImage(_path + L"거미다리 (5).png");
		_images[5] = new ObImage(_path + L"거미다리 (6).png");
		_images[6] = new ObImage(_path + L"거미다리 (7).png");
		_images[7] = new ObImage(_path + L"거미다리 (8).png");
		_images[8] = new ObImage(_path + L"거미다리 (9).png");
		_images[9] = new ObImage(_path + L"거미다리 (10).png");
		_images[10] = new ObImage(_path + L"거미다리 (11).png");
		_images[11] = new ObImage(_path + L"거미다리 (12).png");
		_images[12] = new ObImage(_path + L"거미다리 (13).png");
		_images[13] = new ObImage(_path + L"거미다리 (14).png");
		_images[14] = new ObImage(_path + L"거미다리 (15).png");
		_images[15] = new ObImage(_path + L"거미다리 (16).png");
		_images[16] = new ObImage(_path + L"거미다리 (17).png");
		_images[17] = new ObImage(_path + L"거미다리 (18).png");
		_images[18] = new ObImage(_path + L"거미다리 (19).png");
		_images[19] = new ObImage(_path + L"거미다리 (20).png");
		_images[20] = new ObImage(_path + L"거미다리 (21).png");
		_images[21] = new ObImage(_path + L"거미다리 (22).png");
		_images[22] = new ObImage(_path + L"거미다리 (23).png");
		_images[23] = new ObImage(_path + L"거미다리 (24).png");
		_images[24] = new ObImage(_path + L"거미다리 (25).png");
		_images[25] = new ObImage(_path + L"거미다리 (26).png");
		_images[26] = new ObImage(_path + L"거미다리 (27).png");
		_images[27] = new ObImage(_path + L"거미다리 (28).png");
		_images[28] = new ObImage(_path + L"거미다리 (29).png");
		_images[29] = new ObImage(_path + L"거미다리 (30).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			_image->pivot = OFFSET_B;
			_image->SetWorldPos(Vector2(60.f, 0.f));
		}
	}

	return &_images;
}

SpiderLeg::SpiderLeg()
{
	this->_animation = AddComponent<Animation>();
	this->player = nullptr;
	this->_animation->SetAnimation(GetAnim());

	_hitEffectAnim = new vector<ObImage*>(7);
	wstring _path = L"SpiderLeg/Hit/";
	(*_hitEffectAnim)[0] = new ObImage(_path + L"거미다리 히트 (1).png");
	(*_hitEffectAnim)[1] = new ObImage(_path + L"거미다리 히트 (2).png");
	(*_hitEffectAnim)[2] = new ObImage(_path + L"거미다리 히트 (3).png");
	(*_hitEffectAnim)[3] = new ObImage(_path + L"거미다리 히트 (4).png");
	(*_hitEffectAnim)[4] = new ObImage(_path + L"거미다리 히트 (5).png");
	(*_hitEffectAnim)[5] = new ObImage(_path + L"거미다리 히트 (6).png");
	(*_hitEffectAnim)[6] = new ObImage(_path + L"거미다리 히트 (7).png");

	for (auto& _image : *_hitEffectAnim)
	{
		_image->animInterval = 0.08f;
		//_image->SetWorldPos();
	}

	this->isVisible = false;

	this->_playRate = 5.f;

	SOUND->AddSound("spiderLeg.mp3", "spiderLeg");
}

SpiderLeg::~SpiderLeg()
{
}

void SpiderLeg::Play()
{
	this->isVisible = true;
	CompoObject::Update();
	this->_animation->SetAnimCount(0);
	Vector2 _attackPos = this->_animation->GetAnimWorldPivot() - Vector2(60.f, this->_animation->GetAnimScale().y * 0.5f);
	Vector2 _attackScale = this->_animation->GetAnimScale() - Vector2(this->_animation->GetAnimScale().x * 0.9f, 0.f);
	ATTACK->Attackform(_attackPos, _attackScale, this->player, 10.f, 1.32f, _hitEffectAnim);
	SOUND->Stop("spiderLeg");
	SOUND->Play("spiderLeg");
}

void SpiderLeg::Update()
{
	if (INPUT->KeyDown('N'))
	{
		this->Play();
	}

	if (this->isVisible)
	{
		if (this->_animation->IsOver())
		{
			this->isVisible = false;
			this->_playRate = 10.f;
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

void SpiderLeg::Render()
{
	if (this->isVisible)
	{
		CompoObject::Render();
	}
}