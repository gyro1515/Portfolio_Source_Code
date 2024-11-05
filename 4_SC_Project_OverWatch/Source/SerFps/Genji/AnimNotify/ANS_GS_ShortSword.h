// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_GS_ShortSword.generated.h"

/**
 * 
 */
UCLASS()
class SERFPS_API UANS_GS_ShortSword : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp ,
		UAnimSequenceBase* Animation , float TotalDuration ,
		const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp ,
		UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference);
};
