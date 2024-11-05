// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/ANS_Genji_OnOffCanAttack.h"
#include "Genji/C_CharacterGenji.h"

void UANS_Genji_OnOffCanAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->bCanAttack = false;
}

void UANS_Genji_OnOffCanAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);
    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->bCanAttack = true;

}
