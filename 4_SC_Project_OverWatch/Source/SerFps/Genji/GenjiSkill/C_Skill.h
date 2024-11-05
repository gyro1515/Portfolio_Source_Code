// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Skill.generated.h"

UCLASS()
class AC_Skill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Skill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//UPROPERTY(EditAnywhere, Category = SkillSetting)
	//class UAnimMontage* AttackMotion;
	//
	//UPROPERTY(EditAnywhere, Category = SkillSetting)
	//class USoundBase* HitSound;
	//
	//UPROPERTY(EditAnywhere, Category = SkillSetting)
	//class UParticleSystem* Effect;
	//
	//UPROPERTY(EditAnywhere, Category = SkillSetting)
	//FVector EffectOffset;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = SkillSetting)
	TObjectPtr<USoundAttenuation> Attenuation;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	float coolTime = 0.f;
	float tmpCoolTime = 0.f;
	bool isCoolTime = false;
	bool useSkill = false; // 위젯 세팅용

	class AC_CharacterGenji* player;
public:
	virtual void UseSkill();
	UFUNCTION(NetMulticast, Reliable)
	void MulPlayMontage(UAnimMontage* MontageToPlay, float InPlayRate = 1.0f);
	UFUNCTION(NetMulticast , Reliable)
	void MulSpawnEffect(class UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale);
	UFUNCTION(NetMulticast , Reliable)
	void MulPlaySound(class USoundBase* Sound , FVector Location);
};
