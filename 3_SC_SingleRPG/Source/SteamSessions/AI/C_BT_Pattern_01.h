// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Engine/DecalActor.h"
#include "C_TopDownCharacter.h"
#include "C_BT_Pattern_01.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_BT_Pattern_01 : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BT_Pattern_01();

	AC_TopDownCharacter* target;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float time = 0.0f;

	float delay = 0.0f;

	FVector V = { 0.0f,0.0f,-50.0f };
	ADecalActor* In;
	ADecalActor* Out;

	FVector Location;

};
