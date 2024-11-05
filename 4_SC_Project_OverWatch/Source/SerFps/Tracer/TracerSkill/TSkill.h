// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TSkill.generated.h"

UCLASS()
class SERFPS_API ATSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	float coolTime = 0.f;
	float tmpCoolTime = 0.f;
	bool isCoolTime = false;
	bool useSkill = false; // 위젯 세팅용

	class AC_CharacterTracer* player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseSkill();
	UFUNCTION(NetMulticast , Reliable)
	void MulPlayMontage(UAnimMontage* MontageToPlay , float InPlayRate = 1.0f);
	UFUNCTION(NetMulticast , Reliable)
	void MulSpawnEffect(class UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale);
	UFUNCTION(NetMulticast , Reliable)
	void MulPlaySound(class USoundBase* Sound , FVector Location);

};
