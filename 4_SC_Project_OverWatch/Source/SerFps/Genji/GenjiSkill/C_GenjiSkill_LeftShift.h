// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Genji/GenjiSkill/C_Skill.h"
#include "C_GenjiSkill_LeftShift.generated.h"

UCLASS()
class AC_GenjiSkill_LeftShift : public AC_Skill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GenjiSkill_LeftShift();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* AttackMotion;
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* QAttackMotion;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class USoundBase* SkillSound;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UParticleSystem* SkillEffect;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	FVector SkillEffectOffset;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UParticleSystem* HitEffectP;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UNiagaraSystem* HitEffectN;
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	float dashSpeed = 100.0f;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	float distance = 1200.0f;

	// 몽타주에서 설정
	UPROPERTY()
	bool skillOn = false;
	UPROPERTY()
	bool gravityOn = false;

private:
	//UPROPERTY(Replicated)
	FVector skillDirection;
	FVector startLocation;
	float lerpAlpha = 0.0f;

	float graviTime = 0.08f;
	float tmpGraviTime = 0.0f;

public:
	virtual void UseSkill() override;
	UFUNCTION(NetMulticast , Reliable)
	void MulSetUseSkill(const FVector& _skillDirection , const FVector& _startLocation, const float& _Pitch);
	UFUNCTION(Client, Reliable)
	void ClientSetDirection(FVector _skillDirection, FVector _startLocation);
	UFUNCTION(NetMulticast , Reliable)
	void MulSetActorLocation(FVector _NewLocation, bool _bSweep);
	UFUNCTION(Server , Reliable)
	void SerSetActorLocation(FVector _NewLocation , bool _bSweep);
	UFUNCTION(Server , Reliable)
	void SerMulSetActorLocation(FVector _NewLocation , bool _bSweep);
	UFUNCTION(NetMulticast, Reliable)
	void MulStopSkillLeftShift();
	UFUNCTION(Client , Reliable)
	void ClientSetWidgetLSIcon(bool _isCoolTime);
	UFUNCTION(Client , Reliable)
	void ClientSetWidgetLSCoolTime(float _tmpCoolTime);
};
