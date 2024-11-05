// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SkillQ_SpawnN2.generated.h"

/**
 * 
 */
UCLASS()
class SERFPS_API UAN_SkillQ_SpawnN2 : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation ,
		const FAnimNotifyEventReference& EventReference) override;
};
