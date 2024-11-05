// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_AIBehaviorComponent.generated.h"


UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait,
	Patrol,
	Trace,
	Attack,
	Hit,
	Death
};

UENUM(BlueprintType)
enum class EBossPatternType : uint8
{
	Phase_0,
	Phase_1,
	Phase_2,
	Phase_3
};


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STEAMSESSIONS_API UC_AIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
	FName BossKey = "BossPattern";

	UPROPERTY(EditAnywhere)
	FName PlayerKey = "Target";

	UPROPERTY(EditAnywhere)
	FName subPlayer1 = "SubTarget_1";

	UPROPERTY(EditAnywhere)
	FName subPlayer2 = "SubTarget_2";

public:
	UFUNCTION(BlueprintPure)
	bool IsType(EBehaviorType InType);

	void ChangeType(EBehaviorType InType);

	UFUNCTION(BlueprintPure)
	bool IsBossType(EBossPatternType InType);

	void ChangeType(EBossPatternType InType);


	class AC_TopDownCharacter* GetPlayer();

	class AC_TopDownCharacter* GetSub1Player();

	class AC_TopDownCharacter* GetSub2Player();


	void SetBolackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }
public:
	UC_AIBehaviorComponent();

protected:
	virtual void BeginPlay() override;

	EBehaviorType GetType();

	EBossPatternType GetBossType();

private:
	class UBlackboardComponent* Blackboard;

};
