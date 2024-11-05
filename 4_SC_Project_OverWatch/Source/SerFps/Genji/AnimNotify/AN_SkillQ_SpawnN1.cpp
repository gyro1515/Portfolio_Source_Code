// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AN_SkillQ_SpawnN1.h"
#include "Genji/C_CharacterGenji.h"
#include "Genji/GenjiSkill/C_GenjiSkill_Q.h"

void UAN_SkillQ_SpawnN1::Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp , Animation , EventReference);

    if ( MeshComp == nullptr ) return;
    if ( MeshComp->GetOwner() == nullptr ) return;
    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if ( tmp == nullptr || !tmp->HasAuthority() ) return;    
    tmp->skillQ->SpawnSlash1N();
}
