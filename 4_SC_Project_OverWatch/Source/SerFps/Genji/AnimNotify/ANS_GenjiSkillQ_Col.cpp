// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/ANS_GenjiSkillQ_Col.h"
#include "Genji/C_CharacterGenji.h"
#include "Components/BoxComponent.h"


void UANS_GenjiSkillQ_Col::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->QCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    tmp->QCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void UANS_GenjiSkillQ_Col::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->QCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    tmp->QCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}
