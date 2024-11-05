// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AnimNotify_Genji_LClick.h"
#include "Genji/C_CharacterGenji.h"
#include "Genji/C_PyoChang.h"



void UAnimNotify_Genji_LClick::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (MeshComp == nullptr) return;
    if (MeshComp->GetOwner() == nullptr) return;
    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    if ( tmp == nullptr || !tmp->Controller || !tmp->Controller->IsLocalPlayerController() ) return;
    //if ( tmp == nullptr || !tmp->HasAuthority() ) return;
    //if (tmp == nullptr) return;
    // 클라에서만 실행하고 서버에서 멀티캐스트로 불렛 소환하기
    tmp->FirePyoForClient();

   
}
