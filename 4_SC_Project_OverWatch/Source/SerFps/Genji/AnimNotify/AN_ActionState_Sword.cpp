// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AN_ActionState_Sword.h"
#include "Genji/C_CharacterGenji.h"

void UAN_ActionState_Sword::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;
    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->actionState = EActionState::Sword;
}
