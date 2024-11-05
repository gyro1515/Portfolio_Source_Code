// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_TracerExplosion.generated.h"

UCLASS()
class SERFPS_API AC_TracerExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_TracerExplosion();

	UPROPERTY(EditAnywhere)
	class USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Components")
	class UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 100.0f;

	UPROPERTY(EditAnywhere)
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere)
	float Delay = 3.0f;

	UPROPERTY(EditAnywhere)
	float Duration = 0.5f;



	UPROPERTY(EditAnywhere)
	float ScaleMax = 5.0f;


	float time = 0.0f;

	bool isActive = false;
	int count = 0;
	FVector AttachedLocation;
	AActor* AttachedActor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp ,
		int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult);

	void AttachBomb(const FVector& location , AActor* Actor);
};
