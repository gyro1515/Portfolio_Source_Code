// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AnimNotifyState_Genji_Pyo_Throw.h"
#include "Genji/C_CharacterGenji.h"

void UAnimNotifyState_Genji_Pyo_Throw::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->bThrowPyo = true;
}

void UAnimNotifyState_Genji_Pyo_Throw::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->bThrowPyo = false;
    tmp->ResetPyoLocation();
    //GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , TEXT("SetLoc"));
}
