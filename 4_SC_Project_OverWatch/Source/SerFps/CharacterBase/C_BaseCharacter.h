// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_BaseCharacter.generated.h"

UCLASS()
class SERFPS_API AC_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere , Category = Stat)
	float maxHp;
	UPROPERTY(Replicated)
	float curHp;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TObjectPtr<USoundAttenuation> Attenuation;
	UPROPERTY(Replicated)
	bool bDie = false;
	UPROPERTY(Replicated)
	bool bDestroy = false;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float dieTime = 3.0f;
	float tmpDieTime;
	// 위젯
	UPROPERTY(EditAnywhere , Category = "Widget")
	TSubclassOf<UUserWidget> dieWidgetClass;
	UPROPERTY(VisibleAnywhere , Category = "Widget")
	class UUserWidget* dieWidget;

	UPROPERTY(EditAnywhere , Category = "Widget")
	TSubclassOf<UUserWidget> zoneWidgetClass;
	UPROPERTY(VisibleAnywhere , Category = "Widget")
	class UC_ZoneWidget* zoneWidget;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float TakeDamage(float DamageAmount , struct FDamageEvent const& DamageEvent ,
		class AController* EventInstigator , AActor* DamageCauser) override;
	virtual void CharacterDie();
	// 멀티 캐스트 함수들
	UFUNCTION(NetMulticast , Reliable)
	void MulSpawnEffect(class UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale);
	UFUNCTION(NetMulticast , Reliable)
	void MulPlaySound(class USoundBase* Sound , FVector Location);

	// 클라이언트 함수(위젯용)
	UFUNCTION(Client, Reliable)
	void ClientAddDieWidget();
	UFUNCTION(Client , Reliable)
	void ClientAddZoneWidget();
	UFUNCTION(Client , Reliable)
	void ClientRemoveZoneWidget();

};
