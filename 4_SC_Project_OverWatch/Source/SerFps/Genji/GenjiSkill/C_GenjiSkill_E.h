// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Genji/GenjiSkill/C_Skill.h"
#include "C_GenjiSkill_E.generated.h"

UCLASS()
class AC_GenjiSkill_E : public AC_Skill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GenjiSkill_E();

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
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UAnimMontage* ESkillMotion;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class USoundBase* SkillSound;

	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class USoundBase* HitSound0;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class USoundBase* HitSound1;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class USoundBase* HitSound2;
	// 이페트 둘 중 하나만 쓰고 나머지 버리기
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UParticleSystem* SkillEffectP;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UNiagaraSystem* SkillEffectN;
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	FVector SkillEffectOffset;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	FVector skillScale;
	UPROPERTY(EditAnywhere, Category = SkillSetting)
	class UParticleSystem* HitEffect;
	bool bESkillOn = false;
private:
	UPROPERTY(EditAnywhere, Category = SkillSetting, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float duration = 5.0f;
	float tmpDuration = 0.0f;

	int hitCount = 0;

public:
	virtual void UseSkill() override;
	UFUNCTION(Client , Reliable)
	void ClientSetWidgetEIcon(bool _isCoolTime);
	UFUNCTION(Client , Reliable)
	void ClientSetWidgetECoolTime(float _tmpCoolTime);
	UFUNCTION(NetMulticast , Reliable)
	void MulReflectPyo(UClass* _Uclass, const FTransform& _Transform, const FVector& _direction, float _tmpDistance);
	
};
