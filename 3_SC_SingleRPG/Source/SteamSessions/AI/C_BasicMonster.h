// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skill/C_Attack.h"
#include "CUW_CharacterOverHead.h"
#include "C_BasicMonster.generated.h"

UCLASS()
class STEAMSESSIONS_API AC_BasicMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_BasicMonster();

	//UFUNCTION(Server, Reliable, BlueprintCallable)
	UFUNCTION(BlueprintCallable)
	void ResetSer();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void ResetMul();


	UFUNCTION(NetMulticast, Reliable)
	void SetMonsterName(const FString& name);


	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SerTakeDamage(float damageamount);


	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void UpdateHpPercent(float curHp, float maxHp);

	UFUNCTION(Server, Reliable)
	void SerAttack(UAnimMontage* attack);

	UFUNCTION(NetMulticast, Reliable)
	void MulRPCAttack(UAnimMontage* attack);




	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	//UPROPERTY(VisibleInstanceOnly)
	//class UPatrolComponent* Patrol;


	FORCEINLINE class UBehaviorTree* GetTree() { return BehaviorTree; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Attack0;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Attack1;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Attack2;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Attack3;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Death;


	UPROPERTY(EditAnywhere)
	class UWidgetComponent* OverHeadUI;


public:

	UPROPERTY(EditAnywhere)
	FString MonsterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MonsterMaxHp = 100.0f;


	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MonsterHp = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackSpeed = 0.5f;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HpPercent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MonsterAttackPower;


	//moster skills
	class AC_SkillManager* SkillManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class AC_SkillManager> SkillManagerClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	//TSubclassOf<class AC_LOSPillar> PillarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* dataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName Skill_0_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName Skill_1_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName Skill_2_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName Skill_3_Name;


	FAttackBaseC* Skill_0_Base;
	FAttackBaseC* Skill_1_Base;
	FAttackBaseC* Skill_2_Base;
	FAttackBaseC* Skill_3_Base;
	UPROPERTY()
	FAttackBaseC Skill_0_BaseU;
	UPROPERTY()
	FAttackBaseC Skill_1_BaseU;
	UPROPERTY()
	FAttackBaseC Skill_2_BaseU;
	UPROPERTY()
	FAttackBaseC Skill_3_BaseU;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class ACItemStrut> ItemClass;

	class ACItemStrut* dropItem;


	UFUNCTION()
	void MonsterSkill0(AC_TopDownCharacter* target);

	UFUNCTION()
	void MonsterSkill1(AC_TopDownCharacter* target, FVector location = FVector());

	UFUNCTION()
	void MonsterSkill2(AC_TopDownCharacter* target);

	UFUNCTION()
	void MonsterSkill3(AC_TopDownCharacter* target);

	UFUNCTION()
	void DeathParticle();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class ADecalActor> DecalIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class ADecalActor> DecalOut;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class ADecalActor> DecalWipe;


	UFUNCTION()
	void Die();


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	bool isDead = false;
	bool isAttacking = false;
};
