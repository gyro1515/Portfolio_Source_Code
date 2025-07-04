#include "stdafx.h"

Will::Will()
{
	//컴포넌트 추가
	//히트
	//공격
	//이동?

	imgCount = 0.0f;
	right = false;

	//애니메이션
	this->animation = AddComponent<Animation>();

	//윌 콜라이더
	Collider* _collider = AddComponent<Collider>();
	_collider->SetCollider(this, Vector2(120.f, 160.f));
	_collider->_collider->SetLocalPosY(30.f);

	//윌 체력
	AddComponent<HitComponent>();

	SetState(AnimState::Stand);

	//좌표체크용 맵
	mapImg = *new vector<ObImage*>(3);
	mapImg[0] = new ObImage(L"map (1).png");
	mapImg[1] = new ObImage(L"map (2).png");
	mapImg[2] = new ObImage(L"map (3).png");
	mapImg[0]->scale = Vector2(1400.0f, 800.0f);
	mapImg[1]->scale = Vector2(1400.0f, 800.0f);
	mapImg[2]->scale = Vector2(1400.0f, 800.0f);
	rand = new Random();

	ball.player = player;

	SOUND->AddSound("skill3.mp3", "Hit", true);
	SOUND->AddSound("Attack1.mp3", "Attack1");
	SOUND->AddSound("Attack2 and Attack3.mp3", "Attack2_3");
	SOUND->AddSound("Attack4.mp3", "Attack4");
	SOUND->AddSound("Attack5~6.mp3", "Attack5_6");
	SOUND->AddSound("Die.mp3", "Die");
	SOUND->AddSound("Skill1_Attack7.mp3", "Skill1_Attack7");
}

Will::~Will()
{
}

void Will::Update()
{
	if (animState == AnimState::Move || animState == AnimState::Stand)
	{
		if (player->GetWorldPos().x - GetWorldPos().x >= 0.0f)//플레이어 오른
		{
			animation->flipX = true;
		}
		else if (player->GetWorldPos().x - GetWorldPos().x < 0.0f)//플레이어 왼
		{
			animation->flipX = false;
		}

		if (player->GetWorldPos().x - GetWorldPos().x >= 300.0f)
		{
			SetState(AnimState::Move);
			MoveWorldPos(GetRight() * 60 * DELTA);
		}
		else if (player->GetWorldPos().x - GetWorldPos().x <= -300.0f)
		{
			SetState(AnimState::Move);
			MoveWorldPos(-GetRight() * 60 * DELTA);
		}
		else
		{
			if (animState == AnimState::Move)
			{
				SetState(AnimState::Stand);
				animation->SetAnimCount(16); // 사거리에 오자마자 스킬을 쓸 수 있게끔 바로 스탠드 모션 이즈오버하게 했습니다.
			}
		}
	}

	//애니메이션 끝나면 스탠드로.
	if (animation->IsOver())
	{
		int random = rand->Int(0, 6);
		//cout << random << endl;
		switch (animState)
		{
		case AnimState::Stand:
			//행동
			switch (random)
			{
			case 0:
				SetState(AnimState::Attack1);
				break;
			case 1:
				SetState(AnimState::Attack2);
				break;
			case 2:
				SetState(AnimState::Attack4);
				break;
			case 3:
				SetState(AnimState::Attack5);
				break;
			case 4:
				SetState(AnimState::Attack7);
				break;
			case 5:
				SetState(AnimState::Attack3);
				break;
			case 6:
				SetState(AnimState::Attack6);
				break;
			}
			break;
		case AnimState::Move:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack1:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack2:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack3:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack4:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack5:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack6:
			SetState(AnimState::Stand);
			break;
		case AnimState::Attack7:
			SetState(AnimState::Stand);
			if (animation->flipX)
			{
				ball.Shoot(RIGHT, GetWorldPos());
			}
			else
			{
				ball.Shoot(LEFT, GetWorldPos());
			}
			ball.animation->flipX = animation->flipX;
			break;
			//case AnimState::Ball:
			//	if (animation->GetAnimWorldPivot().x > 850.0f || animation->GetAnimWorldPivot().x > -850.0f)
			//	{
			//		SetState(AnimState::Stand);
			//	}
			//	break;
		case AnimState::Die1:
			SetState(AnimState::Die1);
			break;
		case AnimState::Hit1:
			SOUND->Stop("HIt");
			SetState(AnimState::Stand);
			break;
		case AnimState::Skill1:
			SetState(AnimState::Stand);
			break;
		default:
			break;
		}
	}
	else if (animState == AnimState::Attack4 && animation->GetAnimCount() >= 17 && animation->GetAnimCount() <= 21)
	{
		if (right)
		{
			MoveWorldPos(GetRight() * 1020.4f * DELTA);
		}
		else
		{
			MoveWorldPos(-GetRight() * 1020.4f * DELTA);
		}
	}

	//다단히트?
	switch (animState)
	{
	case AnimState::Attack4:
		if (animation->GetAnimCount() > 12 && animation->GetAnimCount() < 22)
			//ATTACK->Attackform();
			break;
	}

	if (INPUT->KeyDown('1'))
	{
		SetState(AnimState::Attack1);
	}
	if (INPUT->KeyDown('2'))
	{
		SetState(AnimState::Attack2);
	}
	if (INPUT->KeyDown('3'))
	{
		SetState(AnimState::Attack3);
	}
	if (INPUT->KeyDown('4'))
	{
		SetState(AnimState::Attack4);
	}
	if (INPUT->KeyDown('5'))
	{
		SetState(AnimState::Attack5);
	}
	if (INPUT->KeyDown('6'))
	{
		SetState(AnimState::Attack6);
	}
	if (INPUT->KeyDown('7'))
	{
		SetState(AnimState::Attack7);
	}
	if (INPUT->KeyDown('8'))
	{
		SetState(AnimState::Die1);
	}
	if (INPUT->KeyDown('9'))
	{
		SetState(AnimState::Hit1);
	}
	if (INPUT->KeyDown('0'))
	{
		SetState(AnimState::Skill1);
	}
	if (INPUT->KeyDown('Q'))
	{
		SetState(AnimState::Move);
	}
	if (INPUT->KeyDown('W'))
	{
		SetState(AnimState::Stand);
	}

	GameObject::Update();
	SetWorldPosX(Utility::Saturate(GetWorldPos().x, -650.f, 650.f));

	CompoObject::Update();
	ball.Update();
	mapImg[1]->Update();
}

void Will::LateUpdate()
{
}

void Will::Render()
{
	mapImg[1]->Render();
	ball.Render();
	CompoObject::Render();
}

void Will::Show()
{
}

/// <summary>
/// 애니메이션 바꾸기
/// </summary>
/// <param name="_animState"></param>
void Will::SetState(AnimState _animState)
{
	if (this->animState == _animState)
	{
		return;
	}

	this->animState = _animState;

	switch (this->animState)
	{
	case AnimState::Stand:
		this->animation->SetAnimation(&ANIMREF->stand.stand);
		this->animation->isLoop = false;
		break;
	case AnimState::Move:
		this->animation->SetAnimation(&ANIMREF->move.move);
		this->animation->isLoop = false;
		break;
	case AnimState::Attack1:
		this->animation->SetAnimation(&ANIMREF->attack1.attack1Img);
		this->animation->isLoop = false;
		SOUND->Stop("Attack1");
		SOUND->Play("Attack1");

		if (animation->flipX)
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(137.5f, -53.0f), Vector2(275.f, 175.f), player, 10, 1.2f, &ANIMREF->attack1.attack1Hit);
		}
		else
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(-137.5f, -53.0f), Vector2(275.f, 175.f), player, 10, 1.2f, &ANIMREF->attack1.attack1Hit);
		}
		break;
	case AnimState::Attack2:
		this->animation->SetAnimation(&ANIMREF->attack2.attack2Img);
		this->animation->isLoop = false;
		SOUND->Stop("Attack2_3");
		SOUND->Play("Attack2_3");

		if (animation->flipX)
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(195.0f, -53.0f), Vector2(390.f, 180.f), player, 10, 1.2f, &ANIMREF->attack2.attack2Hit);
		}
		else
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(-195.0f, -53.0f), Vector2(390.f, 180.f), player, 10, 1.2f, &ANIMREF->attack2.attack2Hit);
		}

		break;
	case AnimState::Attack3:
		this->animation->SetAnimation(&ANIMREF->attack3.attack3Img);
		this->animation->isLoop = false;
		SOUND->Stop("Attack2_3");
		SOUND->Play("Attack2_3");
		if (animation->flipX)
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(-275.0f, -53.0f), Vector2(550.f, 160.f), player, 10, 1.2f, &ANIMREF->attack3.attack3Hit);
		}
		else
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(275.0f, -53.0f), Vector2(550.f, 160.f), player, 10, 1.2f, &ANIMREF->attack3.attack3Hit);
		}
		break;
	case AnimState::Attack4:
		this->animation->SetAnimation(&ANIMREF->attack4.attack4Img);
		this->animation->isLoop = false;
		SOUND->Stop("Attack4");
		SOUND->Play("Attack4");

		if (animation->flipX)
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 0.99f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.08f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.17f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.26f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.35f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.44f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.53f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.62f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.71f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.80f, &ANIMREF->attack4.attack4Hit);
			right = true;
		}
		else
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 0.99f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.08f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.17f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.26f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.35f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.44f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.53f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.62f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.71f, &ANIMREF->attack4.attack4Hit);
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.80f, &ANIMREF->attack4.attack4Hit);
			right = false;
		}
		break;
	case AnimState::Attack5:
		this->animation->SetAnimation(&ANIMREF->attack5.attack5Img);
		this->animation->isLoop = false;
		SOUND->Stop("Attack5_6");
		SOUND->Play("Attack5_6");
		if (animation->flipX)
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.08f, &ANIMREF->attack5.attack5Hit);
		}
		else
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(-250.0f, -53.0f), Vector2(500.f, 250.f), player, 10, 1.08f, &ANIMREF->attack5.attack5Hit);
		}
		break;
	case AnimState::Attack6:
		this->animation->SetAnimation(&ANIMREF->attack6.attack6Img);
		this->animation->isLoop = false;
		SOUND->Stop("Attack5_6");
		SOUND->Play("Attack5_6");
		if (animation->flipX)
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(-275.0f, -53.0f), Vector2(550.f, 160.f), player, 10, 1.08f, &ANIMREF->attack6.attack6Hit);
		}
		else
		{
			ATTACK->Attackform(GetWorldPos() + Vector2(275.0f, -53.0f), Vector2(550.f, 160.f), player, 10, 1.08f, &ANIMREF->attack6.attack6Hit);
		}
		break;
	case AnimState::Attack7:
		this->animation->SetAnimation(&ANIMREF->attack7.attack7Img);
		this->animation->isLoop = false;
		SOUND->Stop("Skill1_Attack7");
		SOUND->Play("Skill1_Attack7");
		//ATTACK->Attackform(GetWorldPos() + Vector2(275.0f, -53.0f), Vector2(550.f, 160.f), player, 10, 1.2f);
		break;
		//case AnimState::Ball:
		//	this->animation->SetAnimation(&ANIMREF->ball.attack7BallImg);
		//	this->animation->isLoop = false;
		//
		//	//ATTACK->Attackform(GetWorldPos() + Vector2(275.0f, -53.0f), Vector2(550.f, 160.f), player, 10, 1.2f);
		//	break;
	case AnimState::Die1:
		this->animation->SetAnimation(&ANIMREF->die1.die1Img);
		this->animation->isLoop = false;
		SOUND->Stop("Die");
		SOUND->Play("Die");
		break;
	case AnimState::Hit1:
		this->animation->SetAnimation(&ANIMREF->hit1.hit1);
		this->animation->isLoop = false;
		SOUND->Stop("HIt");
		SOUND->Play("HIt");

		break;
	case AnimState::Skill1:
		this->animation->SetAnimation(&ANIMREF->skill1.skill1);
		this->animation->isLoop = false;
		SOUND->Stop("Skill1_Attack7");
		SOUND->Play("Skill1_Attack7");

		break;
	default:
		break;
	}
}