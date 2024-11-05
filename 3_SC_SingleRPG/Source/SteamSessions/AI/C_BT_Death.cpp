// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BT_Death.h"
#include "AI/C_AIBehaviorComponent.h"
#include "AI/C_AIController.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"


UC_BT_Death::UC_BT_Death()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UC_BT_Death::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());

    monster->PlayAnimMontage(monster->Death);
    monster->DeathParticle();

    return EBTNodeResult::InProgress;
}

void UC_BT_Death::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    time += DeltaSeconds;
    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());

    if (time > 6.0f)
    {
        FActorSpawnParameters actorParam;
        actorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        FVector tmpLoction = monster->GetActorLocation();
        tmpLoction.Z += 20;
        // 드랍 아이템 개수 설정
        int32 tmpInt = FMath::RandRange(2, 5);
        for (int32 i = 0; i < tmpInt; i++)
        {
            monster->dropItem = GetWorld()->SpawnActor<ACItemStrut>(monster->ItemClass, tmpLoction, monster->GetActorRotation(), actorParam);
            monster->dropItem->DropRandomItem();
        }
        monster->Destroy();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

    }
    else if (time > 3.0f)
    {
        if (!monster->isDead)
        {
            monster->Die();
        }
    }

}
