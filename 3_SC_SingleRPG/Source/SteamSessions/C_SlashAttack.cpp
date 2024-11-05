// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SlashAttack.h"
#include "AI/C_AIController.h"
#include "AI/C_BasicMonster.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
AC_SlashAttack::AC_SlashAttack()
{
    PrimaryActorTick.bCanEverTick = true;

    // BoxComponent 초기화
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f)); // 크기 조절
    BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    RootComponent = BoxComponent;

    // 충돌 이벤트 바인딩
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_SlashAttack::OnOverlapBegin);

    Damage = 20.0f; // 기본 피해량 설정
    Duration = 0.5f; // 공격 지속 시간 설정
}

// Called when the game starts or when spawned
void AC_SlashAttack::BeginPlay()
{
    Super::BeginPlay();

    // 일정 시간 후에 파괴
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_SlashAttack::DestroySlash, Duration, false);
}

// Called every frame
void AC_SlashAttack::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AC_SlashAttack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        AC_BasicMonster* Monster = Cast<AC_BasicMonster>(OtherActor);
        if (Monster)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MonsterHit")));

            //UGameplayStatics::ApplyDamage(Monster, Damage, nullptr, this, nullptr);
            Monster->SerTakeDamage(20.0f);

            AC_AIController* tmpC = Cast<AC_AIController>(Monster->GetController());
            if (tmpC)
            {
                tmpC->ServerIncreaseAggro(Cast<AC_TopDownCharacter>(GetOwner()), 20.0f);
            }


        }
    }
}

void AC_SlashAttack::DestroySlash()
{
    Destroy();
}