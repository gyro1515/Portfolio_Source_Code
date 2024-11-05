// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_GenjiSkill_LeftShift.h"
#include "Genji/C_CharacterGenji.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Genji/GenjiSkill/C_GenjiSkill_Q.h"
#include "Camera/CameraComponent.h"
#include "CharacterBase/C_BaseWidget.h"

// 네트워크
#include "Net/UnrealNetwork.h"


// Sets default values
AC_GenjiSkill_LeftShift::AC_GenjiSkill_LeftShift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	coolTime = 8.0f;
	Damage = 50.0f;
	if (HasAuthority())
	{
		SetReplicates(true);
	}
}

// Called when the game starts or when spawned
void AC_GenjiSkill_LeftShift::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_GenjiSkill_LeftShift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (skillOn && HasAuthority())
	if (skillOn)
	//if (skillOn && player && player->Controller->IsLocalPlayerController())
	{
		// 거리가 컴퓨터, 플레이어 인원수에 따라 달라짐 -> set, lerp로 바꾸기
		//player->AddActorWorldOffset(skillDirection * dashSpeed, true);
		lerpAlpha += DeltaTime * 2.86f; // 스킬 시간에 따라 달라짐
		if ( lerpAlpha >= 1.0f )
		{
			lerpAlpha = 1.0f;
			//skillOn = false;
		}

		FVector tmpLocation = FMath::Lerp(startLocation , startLocation + skillDirection * distance , lerpAlpha);
		player->SetActorLocation(tmpLocation, true);
		if ( player && player->Controller && player->Controller->IsLocalPlayerController() && lerpAlpha >= 1.0f )
		{
			//SerSetActorLocation(tmpLocation , true);
			SerMulSetActorLocation(tmpLocation , true);
		}
		//MulSetActorLocation(tmpLocation , true);
		
	}
	//else if (gravityOn)
	else if (gravityOn && HasAuthority() )
	{
		tmpGraviTime += DeltaTime;
		if (tmpGraviTime >= graviTime)
		{
			/*gravityOn = false;
			player->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 100.0f);
			player->GetCharacterMovement()->bApplyGravityWhileJumping = true;
			player->GetCharacterMovement()->GravityScale = 3.0f;
			player->GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
			tmpGraviTime = 0.0f;
			player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);*/
			
			// 아래로 테스트
			MulStopSkillLeftShift();

		}
	}
	if ( useSkill && HasAuthority())
	{
		ClientSetWidgetLSCoolTime(coolTime - tmpCoolTime + 1.0f);
		if ( !isCoolTime )
		{
			ClientSetWidgetLSIcon(false);
			useSkill = false;
		}
		
	}
}

void AC_GenjiSkill_LeftShift::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor == Owner || !skillOn || !HasAuthority() ) return;
	// 태그 테스트
	//if (!OtherComp->ComponentHasTag(FName("MainCol")))
	//{
	//	for (FName tmp : OtherComp->ComponentTags)
	//	{
	//		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: %s"), *player->GetActorNameOrLabel(), *tmp.ToString())
	//			, true, true, FColor::MakeRandomColor(), 10.0f);
	//	}
	//	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: NotMainCol"), *OtherComp->GetFName().ToString())
	//		, true, true, FColor::MakeRandomColor(), 10.0f);
	//	return;
	//}

	// 베이스 캐릭터로 변경
	//AC_CharacterGenji* tmpPlayer = Cast<AC_CharacterGenji>(OtherActor);
	AC_BaseCharacter* tmpPlayer = Cast<AC_BaseCharacter>(OtherActor);

	if (!tmpPlayer) return;
	if (tmpPlayer->GetCapsuleComponent() != OtherComp)
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: NotMainCol"), *OtherComp->GetFName().ToString())
		//	, true, true, FColor::MakeRandomColor(), 10.0f);
		return;
	}
	/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: MainCol") , *OtherComp->GetFName().ToString())
			, true , true , FColor::MakeRandomColor() , 10.0f);*/
	TSubclassOf<UDamageType> DamageType;

	Damage = UGameplayStatics::ApplyDamage(OtherActor, Damage,
		player->GetController(), player, DamageType);
	if (!player->bDrangonSowrd)
	{
		player->skillQ->AddGauge(Damage);
	}
	FRotator tmpRot = player->GetActorRotation();
	if ( player->bDrangonSowrd )
	{
		tmpRot.Roll += FMath::FRandRange(20.0f , 80.0f);
	}
	else
	{
		tmpRot.Roll = 20.0f;
	}
	MulSpawnEffect(HitEffectN , OtherActor->GetActorLocation() , tmpRot , FVector(1.0f , 1.0f , 1.0f));
	MulPlaySound(HitSound, SweepResult.Location);
}

void AC_GenjiSkill_LeftShift::OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == this || OtherActor == Owner || !skillOn || !HasAuthority() ) return;
	player->MulStopMontage();
	MulStopSkillLeftShift();
	//player->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f), true);// 피치 바꿀 것인가

	/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: LeftShiftStop"), *player->GetActorNameOrLabel(), *GetActorNameOrLabel())
		,true, true, FColor::MakeRandomColor(), 10.0f);*/
}

void AC_GenjiSkill_LeftShift::UseSkill()
{
	if (isCoolTime) return;
	isCoolTime = true; // 벽 판단하고 바꾸기, 콜라이더 히트 활성화됨
	float genjiPitch = 0.0f;
	if (player->GetCharacterMovement()->IsFalling() || !(player->GetControlRotation().Pitch < 360.0f && player->GetControlRotation().Pitch >= 270.0f))
	{
		skillDirection = player->Camera->GetForwardVector();
		//player->SetActorRotation(FRotator(player->GetControlRotation().Pitch, 0.0f, 0.0f), ETeleportType::TeleportPhysics); // 피치 바꿀 것인가?
		genjiPitch = player->GetControlRotation().Pitch;
	}
	else
	{
		skillDirection = player->GetActorForwardVector();
	}
	// 벽 체크
	FHitResult tmpHitResult;
	FVector start = player->GetActorLocation();
	FVector end = start + skillDirection * 100.0f;
	GetWorld()->LineTraceSingleByChannel(tmpHitResult, start, end, ECollisionChannel::ECC_Visibility);
	if (tmpHitResult.bBlockingHit)
	{
		isCoolTime = false;
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: ShiftCancle"), *GetActorNameOrLabel())
		//	, true, true, FColor::MakeRandomColor(), 10.0f);
		return;
	}
	////////////////////
	startLocation = player->GetActorLocation();
	//lerpAlpha = 0.0f;
	//ClientSetDirection(skillDirection, startLocation);
	//player->GetCharacterMovement()->bApplyGravityWhileJumping = false;
	//player->GetCharacterMovement()->GravityScale = 0.0f;
	//player->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
	// 테스트
	MulSetUseSkill(skillDirection , startLocation, genjiPitch);
	///////////////////////

	if (player->bDrangonSowrd)
	{
		MulPlayMontage(QAttackMotion);
	}
	else
	{
		MulPlayMontage(AttackMotion);
	}
	//player->GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	//player->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	//player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	ClientSetWidgetLSIcon(true);
	useSkill = true;
}

void AC_GenjiSkill_LeftShift::MulSetUseSkill_Implementation(const FVector& _skillDirection , const FVector& _startLocation , const float& _Pitch)
{
	if ( !IsValid(player) ) return;
	
	player->SetActorRotation(FRotator(_Pitch, 0.0f, 0.0f), ETeleportType::TeleportPhysics);
	skillOn = true;
	skillDirection = _skillDirection;
	player->SetActorLocation(_startLocation);
	startLocation = _startLocation;
	lerpAlpha = 0.0f;
	player->GetCharacterMovement()->bApplyGravityWhileJumping = false;
	player->GetCharacterMovement()->GravityScale = 0.0f;
	player->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
	player->GetCharacterMovement()->Velocity = FVector(0.0f , 0.0f , 0.0f);
	player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn , ECollisionResponse::ECR_Overlap);
}

void AC_GenjiSkill_LeftShift::ClientSetWidgetLSCoolTime_Implementation(float _tmpCoolTime)
{
	if ( !IsValid(player) ) return;
	player->mainWidget->SetIconCoolTimeTmp(SkillState::SKill_LShift , _tmpCoolTime);
}

void AC_GenjiSkill_LeftShift::ClientSetWidgetLSIcon_Implementation(bool _isCoolTime)
{
	if ( !IsValid(player) ) return;
	player->mainWidget->SetIconCoolTime(SkillState::SKill_LShift, _isCoolTime);
}

void AC_GenjiSkill_LeftShift::MulSetActorLocation_Implementation(FVector _NewLocation , bool _bSweep)
{
	if ( !IsValid(player) ) return;
	player->SetActorLocation(_NewLocation , _bSweep);
}

void AC_GenjiSkill_LeftShift::MulStopSkillLeftShift_Implementation()
{
	if ( !IsValid(player) ) return;
	skillOn = false;
	//player->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f), true);
	player->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f), ETeleportType::TeleportPhysics);

	gravityOn = false;
	player->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, -1.0f);
	player->GetCharacterMovement()->bApplyGravityWhileJumping = true;
	player->GetCharacterMovement()->GravityScale = 3.0f;
	player->GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
	player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void AC_GenjiSkill_LeftShift::ClientSetDirection_Implementation(FVector _skillDirection , FVector _startLocation)
{
	skillDirection = _skillDirection;
	startLocation = _startLocation;
	lerpAlpha = 0.0f;
	player->GetCharacterMovement()->bApplyGravityWhileJumping = false;
	player->GetCharacterMovement()->GravityScale = 0.0f;
	player->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
	player->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	player->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AC_GenjiSkill_LeftShift::SerSetActorLocation_Implementation(FVector _NewLocation , bool _bSweep)
{
	player->SetActorLocation(_NewLocation , _bSweep);

}

void AC_GenjiSkill_LeftShift::SerMulSetActorLocation_Implementation(FVector _NewLocation , bool _bSweep)
{
	MulSetActorLocation(_NewLocation, _bSweep);
}
