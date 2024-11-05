// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTT_BasicMonster.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_BTT_BasicMonster : public UBTService
{
	GENERATED_BODY()

public:
	UC_BTT_BasicMonster();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
