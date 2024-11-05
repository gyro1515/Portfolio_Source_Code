// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill/C_Attack.h"
#include "C_SkillManager.generated.h"

UCLASS()
class STEAMSESSIONS_API AC_SkillManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SkillManager();

	// 여기부터 테스트
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* SkillMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SkillSpawnAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class AC_Attack> BaseSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class AC_LOSPillar> PillarClass;




	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UDecalComponent* Decal;

	UPROPERTY()
	TMap<AttackInput, class AC_Attack*> attacks;

	void StartAttack(AC_TopDownCharacter* Own, FAttackBaseC* attackBase, AttackInput attackInput);
											 
	void SpawnAttack(AC_TopDownCharacter* Own, FAttackBaseC* attackBase, AttackInput attackInput);
	// 240611 추가 ***** 이걸 사용해야 함
	void StartAttackU(AC_TopDownCharacter* Own, FAttackBaseC attackBase, AttackInput attackInput);
	void SpawnAttackU(AC_TopDownCharacter* Own, FAttackBaseC attackBase, AttackInput attackInput);

	void MonsterAttack(AC_BasicMonster* Own, FAttackBaseC attackBase, AttackInput attackInput, AC_TopDownCharacter* target, FVector location = FVector());

	void SpawnAttackDPS(AC_TopDownCharacter* Own, FAttackBaseC attackBase);

	void Click();

	bool CanInput() { return canInput; }

	// 데칼 중 다른 다른 스킬 사용, 이동 등
	void ResetSkillManager();

	AC_TopDownCharacter* tmpOwn;
	FAttackBaseC* tmpAttackBase;
	AttackInput tmpAttackInput;
	UPROPERTY()
	FAttackBaseC tmpAttackBaseU;


private:
	bool canInput = true;
	FVector spawnLocation;
	float chargingTime = 0.0f;
	bool decalClickOn = false;
	bool chargingTriggeredOn = false;
	bool delayAttackOn = false;
	bool isJump = false;

	FVector tmpWorldDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle TimerHandle;


};
