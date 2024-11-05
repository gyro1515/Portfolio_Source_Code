// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BT_Pattern_02.h"
#include "AI/C_AIBehaviorComponent.h"
#include "AI/C_AIController.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "Kismet/KismetMathLibrary.h"


UC_BT_Pattern_02::UC_BT_Pattern_02()
{
    bNotifyTick = true;
    NodeName = "Attack";

}

EBTNodeResult::Type UC_BT_Pattern_02::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());
    AC_TopDownCharacter* target = behavior->GetPlayer();

    if (target == nullptr)
        return EBTNodeResult::Failed;


    monster->isAttacking = true;
    Wipe = GetWorld()->SpawnActor<ADecalActor>(monster->DecalWipe, monster->GetActorLocation(), FRotator::ZeroRotator);

    //

    //

    return EBTNodeResult::InProgress;
}

void UC_BT_Pattern_02::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());
    AC_TopDownCharacter* target = behavior->GetPlayer();

    time += DeltaSeconds;
    delay += DeltaSeconds;

    if (delay > 5.0f)
    {
        for (int i = 0; i < 36; i++)
        {
            FRotator Rot;
            Rot.Pitch = 0;
            Rot.Roll = 0;
            Rot.Yaw = (360.0f / 36.0f) * i;
            monster->SetActorRotation(Rot.Quaternion());
            monster->MonsterSkill2(target);

        }

        delay = 0.0f;
    }

    if (time > 8.0f)
    {
        delay = 0.0f;
        time = 0.0f;
        monster->isAttacking = false;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }

}
