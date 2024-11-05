#include "stdafx.h"

vector<ObImage*>* BeholderBody::GetStartAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(16);
		wstring _path = L"Beholder/";
		_images[0] = new ObImage(_path + L"說除換_儅撩 (1).png");
		_images[1] = new ObImage(_path + L"說除換_儅撩 (2).png");
		_images[2] = new ObImage(_path + L"說除換_儅撩 (3).png");
		_images[3] = new ObImage(_path + L"說除換_儅撩 (4).png");
		_images[4] = new ObImage(_path + L"說除換_儅撩 (5).png");
		_images[5] = new ObImage(_path + L"說除換_儅撩 (6).png");
		_images[6] = new ObImage(_path + L"說除換_儅撩 (7).png");
		_images[7] = new ObImage(_path + L"說除換_儅撩 (8).png");
		_images[8] = new ObImage(_path + L"說除換_儅撩 (9).png");
		_images[9] = new ObImage(_path + L"說除換_儅撩 (10).png");
		_images[10] = new ObImage(_path + L"說除換_儅撩 (11).png");
		_images[11] = new ObImage(_path + L"說除換_儅撩 (12).png");
		_images[12] = new ObImage(_path + L"說除換_儅撩 (13).png");
		_images[13] = new ObImage(_path + L"說除換_儅撩 (14).png");
		_images[14] = new ObImage(_path + L"說除換_儅撩 (15).png");
		_images[15] = new ObImage(_path + L"說除換_儅撩 (16).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

vector<ObImage*>* BeholderBody::GetLoopAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(16);
		wstring _path = L"Beholder/";
		_images[0] = new ObImage(_path + L"說除換_瑞Щ (1).png");
		_images[1] = new ObImage(_path + L"說除換_瑞Щ (2).png");
		_images[2] = new ObImage(_path + L"說除換_瑞Щ (3).png");
		_images[3] = new ObImage(_path + L"說除換_瑞Щ (4).png");
		_images[4] = new ObImage(_path + L"說除換_瑞Щ (5).png");
		_images[5] = new ObImage(_path + L"說除換_瑞Щ (6).png");
		_images[6] = new ObImage(_path + L"說除換_瑞Щ (7).png");
		_images[7] = new ObImage(_path + L"說除換_瑞Щ (8).png");
		_images[8] = new ObImage(_path + L"說除換_瑞Щ (9).png");
		_images[9] = new ObImage(_path + L"說除換_瑞Щ (10).png");
		_images[10] = new ObImage(_path + L"說除換_瑞Щ (11).png");
		_images[11] = new ObImage(_path + L"說除換_瑞Щ (12).png");
		_images[12] = new ObImage(_path + L"說除換_瑞Щ (13).png");
		_images[13] = new ObImage(_path + L"說除換_瑞Щ (14).png");
		_images[14] = new ObImage(_path + L"說除換_瑞Щ (15).png");
		_images[15] = new ObImage(_path + L"說除換_瑞Щ (16).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			_image->SetWorldPos(Vector2(-2.f, -6.f));
		}
	}

	return &_images;
}

vector<ObImage*>* BeholderBody::GetEndAnim()
{
	static vector<ObImage*> _images;

	if (_images.size() == 0)
	{
		_images = *new vector<ObImage*>(16);
		wstring _path = L"Beholder/";
		_images[0] = new ObImage(_path + L"說除換_模資 (1).png");
		_images[1] = new ObImage(_path + L"說除換_模資 (2).png");
		_images[2] = new ObImage(_path + L"說除換_模資 (3).png");
		_images[3] = new ObImage(_path + L"說除換_模資 (4).png");
		_images[4] = new ObImage(_path + L"說除換_模資 (5).png");
		_images[5] = new ObImage(_path + L"說除換_模資 (6).png");
		_images[6] = new ObImage(_path + L"說除換_模資 (7).png");
		_images[7] = new ObImage(_path + L"說除換_模資 (8).png");
		_images[8] = new ObImage(_path + L"說除換_模資 (9).png");
		_images[9] = new ObImage(_path + L"說除換_模資 (10).png");
		_images[10] = new ObImage(_path + L"說除換_模資 (11).png");
		_images[11] = new ObImage(_path + L"說除換_模資 (12).png");
		_images[12] = new ObImage(_path + L"說除換_模資 (13).png");
		_images[13] = new ObImage(_path + L"說除換_模資 (14).png");
		_images[14] = new ObImage(_path + L"說除換_模資 (15).png");
		_images[15] = new ObImage(_path + L"說除換_模資 (16).png");

		for (auto& _image : _images)
		{
			_image->animInterval = 0.06f;
			_image->SetWorldPos(Vector2(0.f, 7.f));
			//_image->SetWorldPos();
		}
	}

	return &_images;
}

void BeholderBody::SetState(AnimState _animState)
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
		this->animation->isLoop = false;
		break;
	case AnimState::End:
		this->animation->SetAnimation(GetEndAnim());
		this->animation->isLoop = false;
		break;
	default:
		break;
	}
}

BeholderBody::BeholderBody()
{
	this->_spawnCount = 0;
	this->_playRate = 20.f;

	this->animation = AddComponent<Animation>();

	isVisible = false;
	this->SetState(AnimState::Start);

	shootEffectAnim = new vector<ObImage*>(8);
	wstring _path = L"Beholder/";
	(*shootEffectAnim)[0] = new ObImage(_path + L"說除換_嫦餌 (1).png");
	(*shootEffectAnim)[1] = new ObImage(_path + L"說除換_嫦餌 (2).png");
	(*shootEffectAnim)[2] = new ObImage(_path + L"說除換_嫦餌 (3).png");
	(*shootEffectAnim)[3] = new ObImage(_path + L"說除換_嫦餌 (4).png");
	(*shootEffectAnim)[4] = new ObImage(_path + L"說除換_嫦餌 (5).png");
	(*shootEffectAnim)[5] = new ObImage(_path + L"說除換_嫦餌 (6).png");
	(*shootEffectAnim)[6] = new ObImage(_path + L"說除換_嫦餌 (7).png");
	(*shootEffectAnim)[7] = new ObImage(_path + L"說除換_嫦餌 (8).png");

	for (auto& _image : *shootEffectAnim)
	{
		_image->animInterval = 0.08f;
		//_image->SetWorldPos();
	}

	SOUND->AddSound("willEyeBall.mp3", "beholderShoot");
}

BeholderBody::~BeholderBody()
{
	SafeDelete(animation);
}

void BeholderBody::Play()
{
	this->isVisible = true;
	this->_spawnCount = 0;

	for (auto& _bullet : _bulletPool)
	{
		_bullet.player = player;
	}

	SetState(AnimState::Start);
}

void BeholderBody::Update()
{
	if (INPUT->KeyDown('B'))
	{
		this->Play();
	}

	if (this->isVisible)
	{
		CompoObject::Update();

		if (animation->IsOver())
		{
			switch (this->animState)
			{
			case AnimState::Start:
				SetState(AnimState::Loop);
				break;
			case AnimState::Loop:
				if (this->_spawnCount < 4)
				{
					switch (_spawnCount)
					{
					case 0:
						for (int i = 0; i < 5; i++)
						{
							_bulletPool[i].Shoot(Vector2(cosf((72 * i + 270) * ToRadian), sinf((72 * i + 270) * ToRadian)), GetWorldPivot());
						}
						EFFECT->PlayEffect(this->GetWorldPivot(), this->shootEffectAnim);
						SOUND->Stop("beholderShoot");
						SOUND->Play("beholderShoot");
						break;
					case 2:
						for (int i = 5; i < 10; i++)
						{
							_bulletPool[i].Shoot(Vector2(cosf((72 * i + 90) * ToRadian), sinf((72 * i + 90) * ToRadian)), GetWorldPivot());
						}
						EFFECT->PlayEffect(this->GetWorldPivot(), this->shootEffectAnim);
						SOUND->Stop("beholderShoot");
						SOUND->Play("beholderShoot");
						break;

					default:
						break;
					}
					this->_spawnCount++;
					SetState(AnimState::Loop);
				}
				else
				{
					SetState(AnimState::End);
				}
				break;
			case AnimState::End:
				this->isVisible = false;
				this->_playRate = 20.f;
				break;
			default:
				break;
			}
		}
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

	for (auto& _bullet : this->_bulletPool)
	{
		_bullet.Update();
	}
}

void BeholderBody::Render()
{
	if (isVisible)
	{
		CompoObject::Render();
	}

	for (auto& _bullet : this->_bulletPool)
	{
		_bullet.Render();
	}
}