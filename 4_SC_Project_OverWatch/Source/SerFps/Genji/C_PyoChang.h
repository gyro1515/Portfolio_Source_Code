// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase/C_BaseBullet.h"
#include "C_PyoChang.generated.h"

UCLASS()
class AC_PyoChang : public AC_BaseBullet
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PyoChang();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	//UPROPERTY(EditAnywhere)
	//class UShapeComponent* Collider;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UProjectileMovementComponent* Projectile;
	//UPROPERTY(EditAnywhere)
	//float duration = 1.0f;
	//UPROPERTY(EditAnywhere)
	//float damage = 10.0f;

	bool bObjectActive = false;
	float totalDistance = 0.0f;

	class AC_CharacterGenji* player;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UParticleSystem* SkillEffectP;
	UPROPERTY(EditAnywhere , Category = SkillSetting)
	class UNiagaraSystem* SkillEffectN;
	UPROPERTY(VisibleAnywhere , Category = SkillSetting)
	class UNiagaraComponent* niagaraCom;
	UPROPERTY(VisibleAnywhere , Category = SkillSetting)
	UAudioComponent* pyoAudio;

	UPROPERTY(VisibleDefaultsOnly , Category = Mesh , BlueprintReadWrite)
	USkeletalMeshComponent* DefaultMesh;
	bool bIsDestroy = false;
	float tmpDesTime = 0.0f;
public:
	// 오버랩
	UFUNCTION()
	void OnBeginOverlapPyoChang(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// 히트
	UFUNCTION()
	void OnHitPyoChang(UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void FirePyoChang(const FVector& Direction);

	UFUNCTION(Server,Reliable)

	void SerFirePyoChang(const FVector& Direction);

	UFUNCTION(BlueprintCallable)
	void FirePyoChangQuick();
	void FirePyoChangQuickR();


	UFUNCTION(BlueprintCallable)
	void SetActive(bool bActive);
	UFUNCTION(NetMulticast , Reliable)
	void MulSetActive(bool bActive , const FVector& _Direction);

protected:
	UFUNCTION(BlueprintCallable)
	void Inactive();
	UFUNCTION(NetMulticast, Reliable)
	void MulSetComEffect(bool isOnOff);
	

};
