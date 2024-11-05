// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AN_SwordOn.h"
#include "Genji/C_CharacterGenji.h"

void UAN_SwordOn::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;
    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if (tmp == nullptr) return;
    tmp->Long->AttachToComponent(tmp->DefaultMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHand"));
    tmp->Pyo->SetHiddenInGame(true);

}
