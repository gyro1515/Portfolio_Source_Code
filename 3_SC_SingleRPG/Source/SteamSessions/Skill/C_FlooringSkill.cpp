// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_FlooringSkill.h"

#include "C_TopDownCharacter.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "C_TopDownController.h"


// Sets default values
AC_FlooringSkill::AC_FlooringSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f; // 기본 피해량 설정
	Duration = 1.0f; // 공격 지속 시간 설정
	CoolTime = Duration;
	skilltype = FlooringSkillType::ONE_SHOT;
	DotDealInterval = 0.25f;
	tmpDotDealInterval = 0.0f;
	onDotDeal = false;
	isFirst = true;
}

// Called when the game starts or when spawned
void AC_FlooringSkill::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_FlooringSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canClik)
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		
		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}

		FTransform transform;;
		if (bHitSuccessful)
		{
			transform.SetLocation(Hit.Location);
		}
		SetActorTransform(transform);
	}
	else if (isCoolTime)
	{
		tmpCoolTime += DeltaTime;
		if (tmpCoolTime >= CoolTime)
		{
			isCoolTime = false;
			tmpCoolTime = 0.0f;
			//SetActorTickEnabled(false);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("CoolTIme: %f"), tmpCoolTime));
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("CoolTIme: %f"), CoolTime - tmpCoolTime));
		}
	}

	if (skilltype == FlooringSkillType::DOT_DEAL && onDotDeal)
	{
		tmpDotDealInterval += DeltaTime;
		if (tmpDotDealInterval >= DotDealInterval)
		{
			tmpDotDealInterval = 0.0f;
			SetActorEnableCollision(false);
			SetActorEnableCollision(true);

		}
	}

	
}

void AC_FlooringSkill::FireSkill()
{
	if (isCoolTime) return;
	
	switch (skillStep)
	{
	case AC_FlooringSkill::SkillStep::DECAL:
	{
		player->canInput = true;
		canClik = true;
		SetActorHiddenInGame(false);
		SetActorTickEnabled(true);
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), TEXT("FlooringSkillDecal!"));
	}
		break;
	case AC_FlooringSkill::SkillStep::FIRE:
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		}
		
		FTransform transform;
		if (bHitSuccessful)
		{
			transform.SetLocation(Hit.Location);
		}

		FVector WorldDirection = (transform.GetLocation() - player->GetActorLocation()).GetSafeNormal();
		FRotator tmpRot;
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		player->SetActorRotation(tmpRot);
		SetActorTransform(transform);
		//SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		//SetActorTickEnabled(true);

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_FlooringSkill::InactiveSkill, Duration, false);
		player->PlayAnimMontage(SkillMotion);
		skillStep = SkillStep::DECAL;
		player->canInput = false;
		isCoolTime = true;
		if (skilltype == FlooringSkillType::DOT_DEAL)
		{
			onDotDeal = true;
		}
	}
		break;
	default:
		break;
	}
	
}

void AC_FlooringSkill::Fire()
{
	if (!canClik) return;

	canClik = false;
	skillStep = SkillStep::FIRE;
	FireSkill();
}

void AC_FlooringSkill::SetPlayer(AC_TopDownCharacter* _player)
{
	Super::SetPlayer(_player);
	// 키 설정해주기, 플레이어 캐스트는 플레이어 캐릭터에서?
	//APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());


	APlayerController* PlayerController = Cast<APlayerController>(player->GetController());
	
	if (PlayerController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Controller0")));
	
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FlooringSkillMappingContext, 1);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Controller1")));
		}
	
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FlooringSkillFireAction, ETriggerEvent::Started, this, &AC_FlooringSkill::Fire);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Controller2")));
		}
	
	}
}

void AC_FlooringSkill::InactiveSkill()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	if (!isCoolTime)
	{
		SetActorTickEnabled(false);
		//Super::Destroy();
	}
	else
	{
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("OffSkill")));
	skillStep = SkillStep::DECAL;
	player->canInput = false;
	onDotDeal = false;



}


