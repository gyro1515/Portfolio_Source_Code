// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Genji/GenjiSkill/C_Skill.h"
#include "C_GenjiSkill_RightClick.generated.h"

UCLASS()
class AC_GenjiSkill_RightClick : public AC_Skill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GenjiSkill_RightClick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp ,
		int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult);
public:
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UAnimMontage* AttackMotion;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class USoundBase* SkillSound;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UParticleSystem* SkillEffect;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	FVector SkillEffectOffset;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UParticleSystem* HitEffect;


public:
	virtual void UseSkill() override;
};
