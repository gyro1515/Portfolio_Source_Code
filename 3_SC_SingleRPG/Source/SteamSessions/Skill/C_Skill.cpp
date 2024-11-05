// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_Skill.h"

#include "C_TopDownCharacter.h"
#include "Components/ShapeComponent.h"
#include "AI/C_AIController.h"
#include "AI/C_BasicMonster.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
AC_Skill::AC_Skill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    player = nullptr;
    Damage = 0.0f;
    Duration = 0.0f;
    CoolTime = 0.0f;
    isCoolTime = false;
    tmpCoolTime = 0.0f;
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void AC_Skill::BeginPlay()
{
	Super::BeginPlay();

    // 모든 형태 콜라이드 캐스트 가능(블루프린트에서 만들어진 것만)
	collider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
	collider->OnComponentBeginOverlap.AddDynamic(this, &AC_Skill::OnOverlapBegin);
	//collider->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
}

// Called every frame
void AC_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Skill::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {

        AC_BasicMonster* Monster = Cast<AC_BasicMonster>(OtherActor);
        if (Monster)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MonsterHit")));

            //UGameplayStatics::ApplyDamage(Monster, Damage, nullptr, this, nullptr);
            Monster->SerTakeDamage(Damage);

            AC_AIController* tmpC = Cast<AC_AIController>(Monster->GetController());
            if (tmpC)
            {
                tmpC->ServerIncreaseAggro(Cast<AC_TopDownCharacter>(player), Damage);
                GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("AggroDamage!!!")));

            }


        }
    }
}

void AC_Skill::FireSkill()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), TEXT("SkillFire!"));
    //SetActorTransform(transform);
    ////SetActorHiddenInGame(false);
    //SetActorEnableCollision(true);
    ////SetActorTickEnabled(true);
}

void AC_Skill::DestroySkill()
{
	Super::Destroy();
}

void AC_Skill::InactiveSkill()
{
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

