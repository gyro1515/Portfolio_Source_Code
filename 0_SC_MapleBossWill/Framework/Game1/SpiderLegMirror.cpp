#include "stdafx.h"

vector<ObImage*>* SpiderLegMirror::GetAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(30);
		wstring _path = L"SpiderLeg/";
		_images[0] = new ObImage(_path + L"거미다리2 (1).png");
		_images[1] = new ObImage(_path + L"거미다리2 (2).png");
		_images[2] = new ObImage(_path + L"거미다리2 (3).png");
		_images[3] = new ObImage(_path + L"거미다리2 (4).png");
		_images[4] = new ObImage(_path + L"거미다리2 (5).png");
		_images[5] = new ObImage(_path + L"거미다리2 (6).png");
		_images[6] = new ObImage(_path + L"거미다리2 (7).png");
		_images[7] = new ObImage(_path + L"거미다리2 (8).png");
		_images[8] = new ObImage(_path + L"거미다리2 (9).png");
		_images[9] = new ObImage(_path + L"거미다리2 (10).png");
		_images[10] = new ObImage(_path + L"거미다리2 (11).png");
		_images[11] = new ObImage(_path + L"거미다리2 (12).png");
		_images[12] = new ObImage(_path + L"거미다리2 (13).png");
		_images[13] = new ObImage(_path + L"거미다리2 (14).png");
		_images[14] = new ObImage(_path + L"거미다리2 (15).png");
		_images[15] = new ObImage(_path + L"거미다리2 (16).png");
		_images[16] = new ObImage(_path + L"거미다리2 (17).png");
		_images[17] = new ObImage(_path + L"거미다리2 (18).png");
		_images[18] = new ObImage(_path + L"거미다리2 (19).png");
		_images[19] = new ObImage(_path + L"거미다리2 (20).png");
		_images[20] = new ObImage(_path + L"거미다리2 (21).png");
		_images[21] = new ObImage(_path + L"거미다리2 (22).png");
		_images[22] = new ObImage(_path + L"거미다리2 (23).png");
		_images[23] = new ObImage(_path + L"거미다리2 (24).png");
		_images[24] = new ObImage(_path + L"거미다리2 (25).png");
		_images[25] = new ObImage(_path + L"거미다리2 (26).png");
		_images[26] = new ObImage(_path + L"거미다리2 (27).png");
		_images[27] = new ObImage(_path + L"거미다리2 (28).png");
		_images[28] = new ObImage(_path + L"거미다리2 (29).png");
		_images[29] = new ObImage(_path + L"거미다리2 (30).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			_image->pivot = OFFSET_T;
			_image->SetWorldPos(Vector2(60.f, 30.f));
		}
	}

	return &_images;
}

SpiderLegMirror::SpiderLegMirror()
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

SpiderLegMirror::~SpiderLegMirror()
{
}

void SpiderLegMirror::Play()
{
	this->isVisible = true;
	CompoObject::Update();
	this->_animation->SetAnimCount(0);
	Vector2 _attackPos = this->_animation->GetAnimWorldPivot() - Vector2(60.f, -this->_animation->GetAnimScale().y * 0.5f + 30.f);
	Vector2 _attackScale = this->_animation->GetAnimScale() - Vector2(this->_animation->GetAnimScale().x * 0.89f, 0.f);
	ATTACK->Attackform(_attackPos, _attackScale, this->player, 10.f, 1.32f, _hitEffectAnim);
	SOUND->Stop("spiderLeg");
	SOUND->Play("spiderLeg");
}

void SpiderLegMirror::Update()
{
	if (INPUT->KeyDown('M'))
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

void SpiderLegMirror::Render()
{
	if (this->isVisible)
	{
		CompoObject::Render();
	}
}