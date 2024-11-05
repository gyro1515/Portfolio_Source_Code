// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_HealPack.generated.h"

UCLASS()
class SERFPS_API AC_HealPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_HealPack();
public:
	UPROPERTY(EditAnywhere)
	class UShapeComponent* Collider;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TObjectPtr<USoundAttenuation> Attenuation;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UNiagaraComponent* niagaraCom1;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UNiagaraComponent* niagaraCom2;
	UPROPERTY(EditAnywhere)
	float HealHp = 50.0f;
private:
	UPROPERTY(EditAnywhere, meta = ( AllowPrivateAccess = "true" ))
	float respawnTime = 5.0f;
	float tmpRespawnTime = 0.0f;
	bool bIsCoolTime;
	
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
	void MulSetHiddenInGame_Ni2(bool _bHidden);
};
