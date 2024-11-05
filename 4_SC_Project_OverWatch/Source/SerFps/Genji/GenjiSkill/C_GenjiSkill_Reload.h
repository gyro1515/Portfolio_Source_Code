// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Genji/GenjiSkill/C_Skill.h"
#include "C_GenjiSkill_Reload.generated.h"

UCLASS()
class AC_GenjiSkill_Reload : public AC_Skill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_GenjiSkill_Reload();
public:
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UAnimMontage* ReloadMotion;

	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class USoundBase* SkillSound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UseSkill() override;
	void Reload();

	UFUNCTION(Server, Reliable)
	void SerTestUseSkill();
};
