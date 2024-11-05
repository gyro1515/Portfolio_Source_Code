// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Genji/GenjiSkill/C_Skill.h"
#include "C_GenjiSkill_Q.generated.h"

/**
 * 
 */
UCLASS()
class AC_GenjiSkill_Q : public AC_Skill
{
	GENERATED_BODY()
public:
	AC_GenjiSkill_Q();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	float gauge = 0;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* QStartMotion;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* QEndMotion;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* QSlash1Motion;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* QSlash2Motion;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class USoundBase* QStartSound;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class USoundBase* HitSound1;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class USoundBase* HitSound2;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UParticleSystem* QStartEffect;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	FVector SkillEffectOffset;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UParticleSystem* HitEffectP;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UNiagaraSystem* HitEffectN;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UNiagaraSystem* Slash1N;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UNiagaraSystem* Slash2N;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	float skillDuration = 30.0f;
private:
	float tmpSkillDuration;
	bool bDrangonSowrd = false;
	int32 skilMotionNum = 0;
public:
	virtual void UseSkill() override;
	void DragonSlash();
	void AddGauge(float addGauge);
	void SpawnSlash1N();
	void SpawnSlash2N();
	UFUNCTION(Client, Reliable)
	void ClientSetWidgetGauge(float _gauge);
	UFUNCTION(Client , Reliable)
	void ClientSetWidgetGaugeIcon(bool iconOnOff);
};
