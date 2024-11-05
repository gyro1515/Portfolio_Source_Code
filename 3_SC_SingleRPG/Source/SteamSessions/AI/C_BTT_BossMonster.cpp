// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BTT_BossMonster.h"
#include "AI/C_AIController.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "AI/C_AIBehaviorComponent.h"


UC_BTT_BossMonster::UC_BTT_BossMonster()
{
	NodeName = "BossMonster";

}

void UC_BTT_BossMonster::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AC_AIController* controller = Cast<AC_AIController>(OwnerComp.GetOwner());
    UC_AIBehaviorComponent* behavior = controller->GetBehavior();

    AC_BasicMonster* monster = Cast<AC_BasicMonster>(controller->GetPawn());

    if (monster->HpPercent > 0.9f)
    {
        behavior->ChangeType(EBossPatternType::Phase_0);
    }
    else if (monster->HpPercent > 0.5f)
    {
        Skill1time += DeltaSeconds;

        if (Skill1time > 17.0f)
        {
            Skill1time = 0.0f;
            behavior->ChangeType(EBossPatternType::Phase_0);
        }
        else if(Skill1time > 15.0f)
        {
            behavior->ChangeType(EBossPatternType::Phase_1);
        }

    }
    else
    {
        Skill1time += DeltaSeconds;
        Skill2time += DeltaSeconds;

        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Skill2time: %f"), Skill2time));

        if (Skill2time > 30.0f && Skill2time <= 32.0f)
        {
            behavior->ChangeType(EBossPatternType::Phase_2);
        }
        else if (Skill2time > 32.0f)
        {
            behavior->ChangeType(EBossPatternType::Phase_0);
            Skill2time = 0.0f;
        }
        else if (Skill1time > 10.0f && Skill1time <= 12.0f)
        {
            behavior->ChangeType(EBossPatternType::Phase_1);
        }
        else if (Skill1time > 12.0f)
        {
            behavior->ChangeType(EBossPatternType::Phase_0);
            Skill1time = 0.0f;
        }
        else
        {
            behavior->ChangeType(EBossPatternType::Phase_0);
        }
    }



}
