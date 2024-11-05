// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_BTAttackTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BTAttackTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float time = 0.0f;
};
