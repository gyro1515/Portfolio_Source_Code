// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/C_BaseBullet.h"
#include "C_TracerBomb.generated.h"

/**
 * 
 */
UCLASS()
class SERFPS_API AC_TracerBomb : public AC_BaseBullet
{
	GENERATED_BODY()
public:
	AC_TracerBomb();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AC_TracerExplosion> tracerbombclass;

	class AC_TracerExplosion* realbomb;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
public:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp ,
	int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult);

};
