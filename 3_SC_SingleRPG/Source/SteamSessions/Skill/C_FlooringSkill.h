// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Skill.h"

#include "C_FlooringSkill.generated.h"

UENUM(BlueprintType)
enum class FlooringSkillType : uint8
{
	ONE_SHOT,
	DOT_DEAL
};

UCLASS()
class STEAMSESSIONS_API AC_FlooringSkill : public AC_Skill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_FlooringSkill();

	enum class SkillStep
	{
		DECAL,
		FIRE
	};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FlooringSkillMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlooringSkillFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	FlooringSkillType skilltype;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float DotDealInterval;

public:
	virtual void FireSkill() override;
	UFUNCTION()
	void Fire();

	virtual void SetPlayer(AC_TopDownCharacter* _player) override;
	virtual void InactiveSkill() override;

private:
	SkillStep skillStep = SkillStep::DECAL;

	bool canClik = false;
	float tmpDotDealInterval;
	bool onDotDeal;
	bool isFirst;

	FTransform tmpTransform;

};
