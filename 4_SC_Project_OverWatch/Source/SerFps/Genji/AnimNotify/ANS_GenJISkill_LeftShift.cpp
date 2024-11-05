// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/ANS_GenJISkill_LeftShift.h"
#include "Genji/C_CharacterGenji.h"
#include "Genji/GenjiSkill/C_GenjiSkill_LeftShift.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

void UANS_GenJISkill_LeftShift::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    if (tmp->skillLeftShift == nullptr) return;
    
    //tmp->skillLeftShift->skillOn = true;
    //tmp->GetCapsuleComponent()->SetGenerateOverlapEvents(true);
    //tmp->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void UANS_GenJISkill_LeftShift::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    if (tmp->skillLeftShift == nullptr || !tmp->skillLeftShift->skillOn) return;
    tmp->skillLeftShift->skillOn = false;
    tmp->skillLeftShift->gravityOn = true;
    //tmp->GetCharacterMovement()->bApplyGravityWhileJumping = true;
    //tmp->GetCharacterMovement()->GravityScale = 3.0f;
    //tmp->GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
}
