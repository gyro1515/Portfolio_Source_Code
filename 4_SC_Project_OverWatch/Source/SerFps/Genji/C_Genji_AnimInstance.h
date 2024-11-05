// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Genji/C_CharacterGenji.h"

#include "C_Genji_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UC_Genji_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Speed;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	class AC_CharacterGenji* Owner;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Rotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bAirJump;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EActionState actionState = EActionState::PyoChang;

	UPROPERTY(EditAnywhere)
	class USoundBase* LandSound;
	UPROPERTY(EditAnywhere , BlueprintReadWrite )
	TObjectPtr<USoundAttenuation> Attenuation;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool OffCanAirJump(bool _bAirJump);
	UFUNCTION(BlueprintCallable , BlueprintPure , meta = ( BlueprintThreadSafe ))
	bool PlayLandSound(bool _isLanding);
};
