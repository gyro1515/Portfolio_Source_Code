// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/C_BTT_BasicMonster.h"
#include "AI/C_AIController.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "AI/C_AIBehaviorComponent.h"


UC_BTT_BasicMonster::UC_BTT_BasicMonster()
{
	NodeName = "BasicMonster";
}

void UC_BTT_BasicMonster::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();

    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());
    AC_TopDownCharacter* target = behavior->GetPlayer();


    if (monster->MonsterHp < 1)
    {
        behavior->ChangeType(EBehaviorType::Death);
        return;
    }

    if (target == nullptr)
    {
        //behavior->ChangeType(EBehaviorType::Patrol);
        return;
    }

    float distance = monster->GetDistanceTo(target);

    if (distance < controller->GetAttackRange())
    {
        behavior->ChangeType(EBehaviorType::Attack);
        return;
    }

    //if (distance < controller->GetSightRange())
    if (distance > controller->GetAttackRange() && !monster->isAttacking)
    {
        behavior->ChangeType(EBehaviorType::Trace);
        return;
    }

    //behavior->ChangeType(EBehaviorType::Patrol);

}
