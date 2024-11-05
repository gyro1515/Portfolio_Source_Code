// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "C_BlueZone.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "C_RealZone.generated.h"

/**
 * 
 */
UCLASS()
class AC_RealZone : public AC_BlueZone
{
	GENERATED_BODY()
public:
	AC_RealZone();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FTransform GenerateSmallTransform(FTransform original);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp ,
		int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex);

	UFUNCTION(NetMulticast, Reliable)
	void MulSetActorTransform(const FTransform& NewTransform , bool bSweep);

	UFUNCTION(BlueprintCallable)
	void SetActive(bool _IsStart);
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SerSetActive(bool _IsStart);
	UFUNCTION(NetMulticast , Reliable)
	void MulSetActive(bool _IsStart);

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AC_BlueZone> IndicatorClass;

	UPROPERTY(EditDefaultsOnly)
	float StartScale = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	float SmallerPercent = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float StableTime = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float ReadyTime = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float UnStableTime = 4.0f;

	UPROPERTY(EditDefaultsOnly)
	float damage = 10.0f;

	TArray<class AC_BaseCharacter*> characters;

	AC_BlueZone* Indicator;
	FTransform OriginalT;
	FTransform SmallT;
	float Timer;
	float Alpha;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsStart;
	bool bRealStart;
	UPROPERTY(EditDefaultsOnly)
	float startTime = 3.0f;
	float tmpStartTime = 0.0f;
	int32 zoneCount;
};
