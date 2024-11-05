// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AN_G_RClick.h"
#include "Genji/C_CharacterGenji.h"

void UAN_G_RClick::Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp , Animation , EventReference);

    if ( MeshComp == nullptr ) return;
    if ( MeshComp->GetOwner() == nullptr ) return;
    AC_CharacterGenji* tmp = Cast<AC_CharacterGenji>(MeshComp->GetOwner());

    //if ( tmp == nullptr ) return;
    //if ( tmp == nullptr || !tmp->HasAuthority() ) return;
    if ( tmp == nullptr || !tmp->Controller || !tmp->Controller->IsLocalPlayerController() ) return;

    // 클라에서만 실행하고 서버에서 멀티캐스트로 불렛 소환하기
    tmp->FirePyoForClientR();



    //if ( tmp == nullptr || !tmp->HasAuthority() ) return;
   //tmp->FirePyoTest3();
}
