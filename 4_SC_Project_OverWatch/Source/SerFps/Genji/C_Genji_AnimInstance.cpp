// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/C_Genji_AnimInstance.h"
#include "Genji/C_CharacterGenji.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/GameplayStatics.h"

void UC_Genji_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<AC_CharacterGenji>(TryGetPawnOwner());
}

void UC_Genji_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Owner == nullptr) return;

	Speed = Owner->GetVelocity().Size2D();
	Rotation = UKismetAnimationLibrary::CalculateDirection(Owner->GetVelocity() , Owner->GetActorRotation());
	
	bFalling = Owner->GetCharacterMovement()->IsFalling();
	bAirJump = Owner->bCanAirJump;
	actionState = Owner->actionState;
}

bool UC_Genji_AnimInstance::OffCanAirJump(bool _bAirJump)
{
	if (_bAirJump)
	{
		Owner->bCanAirJump = false;
		bAirJump = false;
		return true;
	}
	return false;
}

bool UC_Genji_AnimInstance::PlayLandSound(bool _isLanding)
{
	if (_isLanding)
	{
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), LandSound, Owner->GetActorLocation(), 1.0f, 1.0f, 0.0f, Attenuation);
		return true;
	}
	return false;
}
