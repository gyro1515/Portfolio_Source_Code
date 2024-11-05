// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseBullet.generated.h"

UCLASS()
class SERFPS_API AC_BaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_BaseBullet();

public:
	UPROPERTY(EditAnywhere)
	class UShapeComponent* Collider;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UProjectileMovementComponent* Projectile;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TObjectPtr<USoundAttenuation> Attenuation;
	UPROPERTY(EditAnywhere)
	float duration = 1.0f;
	float tmpDuration = 0.0f;
	UPROPERTY(EditAnywhere)
	float damage = 10.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp ,
		int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult);

	UFUNCTION(NetMulticast , Reliable)
	void MulSpawnEffect(class UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale);
	UFUNCTION(NetMulticast , Reliable)
	void MulPlaySound(class USoundBase* Sound , FVector Location);
};
