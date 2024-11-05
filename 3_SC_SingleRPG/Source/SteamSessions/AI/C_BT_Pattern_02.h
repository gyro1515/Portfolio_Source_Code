// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Engine/DecalActor.h"
#include "C_BT_Pattern_02.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_BT_Pattern_02 : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BT_Pattern_02();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float time = 0.0f;

	float delay = 0.0f;

	ADecalActor* Wipe;

};
