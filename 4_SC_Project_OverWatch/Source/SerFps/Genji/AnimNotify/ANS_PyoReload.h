// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_PyoReload.generated.h"

/**
 * 
 */
UCLASS()
class SERFPS_API UANS_PyoReload : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp ,
		UAnimSequenceBase* Animation , float TotalDuration ,
		const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp ,
		UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference);
};
