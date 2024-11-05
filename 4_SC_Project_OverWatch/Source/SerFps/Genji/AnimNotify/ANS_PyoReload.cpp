// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/ANS_PyoReload.h"
#include "Genji/C_CharacterGenji.h"

void UANS_PyoReload::NotifyBegin(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp , Animation , TotalDuration , EventReference);

    if ( MeshComp == nullptr ) return;
    if ( MeshComp->GetOwner() == nullptr ) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if ( tmp == nullptr ) return;
    tmp->bPyoReload = true;

}

void UANS_PyoReload::NotifyEnd(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp , Animation , EventReference);

    if ( MeshComp == nullptr ) return;
    if ( MeshComp->GetOwner() == nullptr ) return;

    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if ( tmp == nullptr ) return;
    tmp->bPyoReload = false;
}
