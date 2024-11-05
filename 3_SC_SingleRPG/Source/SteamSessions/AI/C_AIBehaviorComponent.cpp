// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_AIBehaviorComponent.h"
#include "C_TopDownCharacter.h"
#include "AI/C_BasicMonster.h"
#include "BehaviorTree/BlackboardComponent.h"


bool UC_AIBehaviorComponent::IsType(EBehaviorType InType)
{
	return GetType() == InType;
}

void UC_AIBehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);
}

bool UC_AIBehaviorComponent::IsBossType(EBossPatternType InType)
{
	return GetBossType() == InType;
}

void UC_AIBehaviorComponent::ChangeType(EBossPatternType InType)
{
	EBossPatternType type = GetBossType();
	Blackboard->SetValueAsEnum(BossKey, (uint8)InType);
}

AC_TopDownCharacter* UC_AIBehaviorComponent::GetPlayer()
{
	return Cast<AC_TopDownCharacter>(Blackboard->GetValueAsObject(PlayerKey));
}

AC_TopDownCharacter* UC_AIBehaviorComponent::GetSub1Player()
{
	return Cast<AC_TopDownCharacter>(Blackboard->GetValueAsObject(subPlayer1));
}

AC_TopDownCharacter* UC_AIBehaviorComponent::GetSub2Player()
{
	return Cast<AC_TopDownCharacter>(Blackboard->GetValueAsObject(subPlayer2));
}

UC_AIBehaviorComponent::UC_AIBehaviorComponent()
{
}

void UC_AIBehaviorComponent::BeginPlay()
{
}

EBehaviorType UC_AIBehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}

EBossPatternType UC_AIBehaviorComponent::GetBossType()
{
	return (EBossPatternType)Blackboard->GetValueAsEnum(BossKey);
}
