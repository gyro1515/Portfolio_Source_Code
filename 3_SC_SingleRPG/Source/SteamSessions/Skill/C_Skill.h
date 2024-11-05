// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Skill.generated.h"

UCLASS()
class STEAMSESSIONS_API AC_Skill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Skill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: // 변수는 여기에서 추가
    // 플레이어 캐릭터
    class AC_TopDownCharacter* player;

    // 범위를 나타내는 컴포넌트, 박스, 스피어, 캡슐 컴포넌트가 있더라도 캐스팅 가능하게 
    class UShapeComponent* collider;

    UPROPERTY(VisibleAnywhere)
    class UAnimMontage* SkillMotion;

    // 피해량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Damage;

    // 공격 지속 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Duration;
    // 스킬 쿨타임
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float CoolTime;


    // 시전시 사운드, 스킬 사운드, 히트 사운드

    // 애니메이션도 여기서?

public: // 함수는 여기서 추가
    // 충돌 처리 함수
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //UFUNCTION()
    virtual void SetPlayer(AC_TopDownCharacter* _player) { player = _player; }
    virtual void FireSkill();
    virtual void InactiveSkill();
    
    FORCEINLINE bool IsCoolTime() { return isCoolTime; }
protected:
    FTimerHandle TimerHandle;
    bool isCoolTime;
    float tmpCoolTime;

private:
    void DestroySkill();


};
