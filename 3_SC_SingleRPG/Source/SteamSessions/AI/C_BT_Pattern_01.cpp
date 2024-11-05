// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BT_Pattern_01.h"
#include "AI/C_AIBehaviorComponent.h"
#include "AI/C_AIController.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"


UC_BT_Pattern_01::UC_BT_Pattern_01()
{
	bNotifyTick = true;
	NodeName = "Attack";

}

EBTNodeResult::Type UC_BT_Pattern_01::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());
    
    int r = FMath::RandRange(0, 1);

    if (r)
    {
        target = behavior->GetSub1Player();
    }
    else
    {
        target = behavior->GetSub2Player();
    }


    if (target == nullptr)
        return EBTNodeResult::Failed;


    //

    monster->isAttacking = true;
    In = GetWorld()->SpawnActor<ADecalActor>(monster->DecalIn, target->GetActorLocation(), FRotator::ZeroRotator);
    Out = GetWorld()->SpawnActor<ADecalActor>(monster->DecalOut, target->GetActorLocation(), FRotator::ZeroRotator);

    //monster->MonsterSkill1(target);

    //

    return EBTNodeResult::InProgress;
}

void UC_BT_Pattern_01::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());

    FRotator rot = UKismetMathLibrary::FindLookAtRotation(monster->GetActorLocation(), target->GetActorLocation());
    monster->SetActorRotation(rot.Quaternion());

    if (delay < 1.5f)
    {
        Location = target->GetActorLocation();
    }

    //if (In)
    if(IsValid(In))
    {
        In->SetActorLocation(Location + V);
    }

    //if(Out)
    if (IsValid(Out))
    {
        Out->SetActorLocation(Location + V);
    }

    time +=  DeltaSeconds;
    delay += DeltaSeconds;

    if (delay > 3.0f)
    {
        monster->MonsterSkill1(target , Location);
        In->Destroy();
        Out->Destroy();
        delay = 0.0f;
    }

    if (time > 5.0f)
    {
        time = 0.0f;
        delay = 0.0f;
        monster->isAttacking = false;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }


}
