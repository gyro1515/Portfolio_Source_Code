#include "stdafx.h"

Player::Player()
{
	Collider* _collider = AddComponent<Collider>();
	_collider->SetCollider(this, Vector2(40.f, 60.f));
	this->animation = AddComponent<Animation>();

	HitComponent* _hitComponent = AddComponent<HitComponent>();
	_hitComponent->invincibilityTime = 1.f;

	playerJump.player = this;
	playerJump.floorHeight = -20.f;

	standImg = *new vector<ObImage*>(4);
	standImg[0] = new ObImage(L"아바타_스탠드 (1).png");
	standImg[1] = new ObImage(L"아바타_스탠드 (2).png");
	standImg[2] = new ObImage(L"아바타_스탠드 (3).png");
	standImg[3] = new ObImage(L"아바타_스탠드 (2).png");
	for (auto& _image : standImg)
	{
		_image->animInterval = 0.2f;
		//_image->SetWorldPos();
	}
	wlakImg = *new vector<ObImage*>(4);
	wlakImg[0] = new ObImage(L"아바타_워크 (1).png");
	wlakImg[1] = new ObImage(L"아바타_워크 (2).png");
	wlakImg[2] = new ObImage(L"아바타_워크 (3).png");
	wlakImg[3] = new ObImage(L"아바타_워크 (4).png");
	for (auto& _image : wlakImg)
	{
		_image->animInterval = 0.2f;
		//_image->SetWorldPos();
	}

	jumpImg = *new vector<ObImage*>(1);
	jumpImg[0] = new ObImage(L"아바타_점프.png");
	for (auto& _image : jumpImg)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	swingImg = *new vector<ObImage*>(3);
	swingImg[0] = new ObImage(L"아바타_스윙 (1).png");
	swingImg[1] = new ObImage(L"아바타_스윙 (2).png");
	swingImg[2] = new ObImage(L"아바타_스윙 (3).png");
	for (auto& _image : swingImg)
	{
		_image->animInterval = 0.2f;
		//_image->SetWorldPos();
	}

	downImg = *new vector<ObImage*>(1);
	downImg[0] = new ObImage(L"아바타_숙이기.png");
	for (auto& _image : downImg)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	fightImg = *new vector<ObImage*>(3);
	fightImg[0] = new ObImage(L"아바타_전투대기 (1).png");
	fightImg[1] = new ObImage(L"아바타_전투대기 (2).png");
	fightImg[2] = new ObImage(L"아바타_전투대기 (3).png");
	for (auto& _image : fightImg)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	jumpjumpImg1 = *new vector<ObImage*>(10);
	jumpjumpImg1[0] = new ObImage(L"더블점프 (1).png");
	jumpjumpImg1[1] = new ObImage(L"더블점프 (2).png");
	jumpjumpImg1[2] = new ObImage(L"더블점프 (3).png");
	jumpjumpImg1[3] = new ObImage(L"더블점프 (4).png");
	jumpjumpImg1[4] = new ObImage(L"더블점프 (5).png");
	jumpjumpImg1[5] = new ObImage(L"더블점프 (6).png");
	jumpjumpImg1[6] = new ObImage(L"더블점프 (7).png");
	jumpjumpImg1[7] = new ObImage(L"더블점프 (8).png");
	jumpjumpImg1[8] = new ObImage(L"더블점프 (9).png");
	jumpjumpImg1[9] = new ObImage(L"더블점프 (10).png");
	for (auto& _image : jumpjumpImg1)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPosX(96.5f);
	}

	jumpjumpImg2 = *new vector<ObImage*>(8);
	jumpjumpImg2[0] = new ObImage(L"더블점프2- (1).png");
	jumpjumpImg2[1] = new ObImage(L"더블점프2- (2).png");
	jumpjumpImg2[2] = new ObImage(L"더블점프2- (3).png");
	jumpjumpImg2[3] = new ObImage(L"더블점프2- (4).png");
	jumpjumpImg2[4] = new ObImage(L"더블점프2- (5).png");
	jumpjumpImg2[5] = new ObImage(L"더블점프2- (6).png");
	jumpjumpImg2[6] = new ObImage(L"더블점프2- (7).png");
	jumpjumpImg2[7] = new ObImage(L"더블점프2- (8).png");
	for (auto& _image : jumpjumpImg2)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	highJumpImg1 = *new vector<ObImage*>(10);
	highJumpImg1[0] = new ObImage(L"윗점 (1).png");
	highJumpImg1[1] = new ObImage(L"윗점 (2).png");
	highJumpImg1[2] = new ObImage(L"윗점 (3).png");
	highJumpImg1[3] = new ObImage(L"윗점 (4).png");
	highJumpImg1[4] = new ObImage(L"윗점 (5).png");
	highJumpImg1[5] = new ObImage(L"윗점 (6).png");
	highJumpImg1[6] = new ObImage(L"윗점 (7).png");
	highJumpImg1[7] = new ObImage(L"윗점 (8).png");
	highJumpImg1[8] = new ObImage(L"윗점 (9).png");
	highJumpImg1[9] = new ObImage(L"윗점 (10).png");
	for (auto& _image : highJumpImg1)
	{
		_image->animInterval = 0.09f;
		_image->SetWorldPosY(-96.5f);
		//_image->SetWorldPos();
	}

	highJumpImg2 = *new vector<ObImage*>(8);
	highJumpImg2[0] = new ObImage(L"윗점2- (1).png");
	highJumpImg2[1] = new ObImage(L"윗점2- (2).png");
	highJumpImg2[2] = new ObImage(L"윗점2- (3).png");
	highJumpImg2[3] = new ObImage(L"윗점2- (4).png");
	highJumpImg2[4] = new ObImage(L"윗점2- (5).png");
	highJumpImg2[5] = new ObImage(L"윗점2- (6).png");
	highJumpImg2[6] = new ObImage(L"윗점2- (7).png");
	highJumpImg2[7] = new ObImage(L"윗점2- (8).png");
	for (auto& _image : highJumpImg2)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	snail = *new vector<ObImage*>(3);
	snail[0] = new ObImage(L"달팽이 (1).png");
	snail[1] = new ObImage(L"달팽이 (2).png");
	snail[2] = new ObImage(L"달팽이 (3).png");
	for (auto& _image : snail)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	snailHit = *new vector<ObImage*>(6);
	snailHit[0] = new ObImage(L"달팽이히트 (1).png");
	snailHit[1] = new ObImage(L"달팽이히트 (2).png");
	snailHit[2] = new ObImage(L"달팽이히트 (3).png");
	snailHit[3] = new ObImage(L"달팽이히트 (4).png");
	snailHit[4] = new ObImage(L"달팽이히트 (5).png");
	snailHit[5] = new ObImage(L"달팽이히트 (6).png");
	for (auto& _image : snailHit)
	{
		_image->animInterval = 0.09f;
		//_image->SetWorldPos();
	}

	animation->SetAnimation(&standImg);
	animation->isLoop = true;

	snailObject.enemy = this->enemy;

	jumpEffect.SetParentT(*this);
	jumpEffectAnimation = jumpEffect.AddComponent<Animation>();

	SOUND->AddSound("jumpjump.mp3", "doubleJump");
	SOUND->AddSound("Jump.mp3", "jump");
	SOUND->AddSound("maceAttack.mp3", "playerAttack");
}

Player::~Player()
{
}

void Player::Update()
{
	if (INPUT->KeyPress(VK_DOWN))
	{
	}

	if (animState != AnimState::Attack1)
	{
		if (INPUT->KeyPress('A'))
		{
			SetState(AnimState::Attack1);
			Vector2 dir;
			if (animation->flipX)
			{
				dir = RIGHT;
			}
			else
			{
				dir = LEFT;
			}
			snailObject.Throw(this->GetWorldPos(), dir);
		}
	}
	else
	{
		if (!animation->IsOver())
		{
			this->SetWorldPosX(Utility::Saturate(this->GetWorldPos().x, -app.GetHalfWidth() + 25.f, app.GetHalfWidth() - 25.f));
			playerJump.Update();
			CompoObject::Update();
			jumpEffect.Update();
			snailObject.Update();
			return;
		}
		else
		{
			if (playerJump.jumpCount == 0)
			{
				SetState(AnimState::Stand);
			}
			else
			{
				SetState(AnimState::Jump);
			}
		}
	}

	if (INPUT->KeyPress(VK_LEFT))
	{
		animation->flipX = false;

		if (playerJump.jumpCount == 0)
		{
			MoveWorldPos(-GetRight() * 170 * DELTA);
			SetState(AnimState::Walk);
		}
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		animation->flipX = true;

		if (playerJump.jumpCount == 0)
		{
			MoveWorldPos(GetRight() * 170 * DELTA);
			SetState(AnimState::Walk);
		}
	}

	if ((INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp(VK_RIGHT)) && playerJump.jumpCount == 0)
	{
		SetState(AnimState::Stand);
	}

	if (INPUT->KeyDown('C'))
	{
		//MoveWorldPos(GetRight() * 170 * DELTA);
		if (playerJump.jumpCount == 0)
		{
			if (INPUT->KeyPress(VK_LEFT))
			{
				Vector2 dir = Vector2(-1.f, 3.f);
				dir.Normalize();
				playerJump.Jump(dir, 600.f);
			}
			else if (INPUT->KeyPress(VK_RIGHT))
			{
				Vector2 dir = Vector2(1.f, 3.f);
				dir.Normalize();
				playerJump.Jump(dir, 600.f);
			}
			else
			{
				playerJump.Jump(UP, 600.f);
			}
			SOUND->Stop("jump");
			SOUND->Play("jump");
		}
		else if (playerJump.jumpCount == 1)
		{
			SOUND->Stop("doubleJump");
			SOUND->Play("doubleJump");
			if (INPUT->KeyPress(VK_UP))
			{
				jumpEffectAnimation->SetAnimation(&highJumpImg1);
				jumpEffectAnimation->flipX = animation->flipX;
				if (INPUT->KeyPress(VK_LEFT))
				{
					Vector2 dir = Vector2(-0.5f, 5.f);
					dir.Normalize();
					playerJump.Jump(dir, 1000.f);
				}
				else if (INPUT->KeyPress(VK_RIGHT))
				{
					Vector2 dir = Vector2(0.5f, 5.f);
					dir.Normalize();
					playerJump.Jump(dir, 1000.f);
				}
				else
				{
					playerJump.Jump(UP, 1000.f);
				}
			}
			else
			{
				jumpEffectAnimation->SetAnimation(&jumpjumpImg1);
				jumpEffectAnimation->flipX = animation->flipX;
				if (animation->flipX)
				{
					Vector2 dir = Vector2(1.f, 1.5f);
					dir.Normalize();
					playerJump.Jump(dir, 600.f);
				}
				else
				{
					Vector2 dir = Vector2(-1.f, 1.5f);
					dir.Normalize();
					playerJump.Jump(dir, 600.f);
				}
			}
		}
	}

	GameObject::Update();
	this->SetWorldPosX(Utility::Saturate(this->GetWorldPos().x, -700.0f + 25.f, 700.f - 25.f));
	this->SetWorldPosY(Utility::Saturate(this->GetWorldPos().y, -400.0f + 25.f, 400.f - 25.f));

	playerJump.Update();

	CompoObject::Update();

	snailObject.Update();

	jumpEffect.Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	if (playerJump.jumpCount == 2)
	{
		if (!jumpEffectAnimation->IsOver())
		{
			jumpEffect.Render();
		}
	}
	CompoObject::Render();
	snailObject.Render();
}

void Player::Show()
{
}

void Player::SetState(AnimState _animState)
{
	if (this->animState == _animState)
	{
		return;
	}

	this->animState = _animState;

	switch (this->animState)
	{
	case AnimState::Walk:
		animation->SetAnimation(&this->wlakImg);
		animation->isLoop = true;
		break;
	case AnimState::Stand:
		animation->SetAnimation(&this->standImg);
		animation->isLoop = true;
		break;
	case AnimState::Jump:
		animation->SetAnimation(&this->jumpImg);
		animation->isLoop = true;
		break;
	case AnimState::Attack1:
		animation->SetAnimation(&this->swingImg);
		animation->isLoop = false;
		SOUND->Stop("playerAttack");
		SOUND->Play("playerAttack");
		break;
	default:
		break;
	}
}