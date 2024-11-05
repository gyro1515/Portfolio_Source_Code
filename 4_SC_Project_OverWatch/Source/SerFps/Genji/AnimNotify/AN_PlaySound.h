// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_PlaySound.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;
class USoundBase;
class USoundAttenuation;

UCLASS(const , hidecategories = Object , collapsecategories , Config = Game , meta = ( DisplayName = "Play SoundA" ))
class SERFPS_API UAN_PlaySound : public UAnimNotify
{
	GENERATED_BODY()
public:

	UAN_PlaySound();

	// Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	UE_DEPRECATED(5.0 , "Please use the other Notify function instead")
	virtual void Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation) override;
	virtual void Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference) override;
#if WITH_EDITOR
	virtual void ValidateAssociatedAssets() override;
#endif
	// End UAnimNotify interface

	// Sound to Play
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimNotify" , meta = ( ExposeOnSpawn = true ))
	TObjectPtr<USoundBase> Sound;

	// Volume Multiplier
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimNotify" , meta = ( ExposeOnSpawn = true ))
	float VolumeMultiplier;

	// Pitch Multiplier
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimNotify" , meta = ( ExposeOnSpawn = true ))
	float PitchMultiplier;

	// If this sound should follow its owner
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimNotify")
	uint32 bFollow : 1;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimNotify")
	TObjectPtr<USoundAttenuation> Attenuation;


#if WITH_EDITORONLY_DATA
	UPROPERTY(Config , EditAnywhere , Category = "AnimNotify")
	uint32 bPreviewIgnoreAttenuation : 1;
#endif

	// Socket or bone name to attach sound to
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "AnimNotify" , meta = ( EditCondition = "bFollow" , ExposeOnSpawn = true ))
	FName AttachName;
};
