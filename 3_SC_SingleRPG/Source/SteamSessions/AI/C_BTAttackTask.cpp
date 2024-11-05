// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BTAttackTask.h"
#include "AI/C_AIBehaviorComponent.h"
#include "AI/C_AIController.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "Kismet/KismetMathLibrary.h"


UC_BTAttackTask::UC_BTAttackTask()
{
	bNotifyTick = true;
    NodeName = "Attack";


}

EBTNodeResult::Type UC_BTAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());
    AC_TopDownCharacter* target = behavior->GetPlayer();

    if (target == nullptr)
        return EBTNodeResult::Failed;

    FRotator rot = UKismetMathLibrary::FindLookAtRotation(monster->GetActorLocation(), target->GetActorLocation());
    FVector tmpV = target->GetActorLocation() - monster->GetActorLocation();
    tmpV.Z = 0;
    FRotator tmpRot = tmpV.Rotation();
    monster->SetActorRotation(tmpRot);

    //
    monster->MonsterSkill0(target);
    //

    return EBTNodeResult::InProgress;
}

void UC_BTAttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());

    time += monster->AttackSpeed * DeltaSeconds;

    if (time > 1.0f)
    {
        time = 0.0f;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }

}
