// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_LOSPillar.generated.h"

UCLASS()
class STEAMSESSIONS_API AC_LOSPillar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_LOSPillar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector curLocation;
	FVector startLocation;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float curHeight = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyPillar();
};
