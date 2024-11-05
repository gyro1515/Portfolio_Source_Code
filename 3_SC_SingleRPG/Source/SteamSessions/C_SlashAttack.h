// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SlashAttack.generated.h"

UCLASS()
class STEAMSESSIONS_API AC_SlashAttack : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AC_SlashAttack();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // 범위를 나타내는 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* BoxComponent;

    // 피해량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Damage;

    // 충돌 처리 함수
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 공격 지속 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Duration;

private:
    FTimerHandle TimerHandle;

    void DestroySlash();
};
