// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTT_BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_BTT_BossMonster : public UBTService
{
	GENERATED_BODY()
	
public:
	UC_BTT_BossMonster();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float Skill1time = 0.0f;
	float Skill2time = 0.0f;

};
