// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AN_PyoChangOn.h"
#include "Genji/C_CharacterGenji.h"

void UAN_PyoChangOn::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;
    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->Pyo->SetHiddenInGame(false);
    tmp->ResetPyoLocation();
    tmp->Long->AttachToComponent(tmp->DefaultMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LongSword"));

}
