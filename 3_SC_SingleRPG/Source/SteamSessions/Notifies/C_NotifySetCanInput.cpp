// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/C_NotifySetCanInput.h"
#include "C_TopDownCharacter.h"
#include "GameFramework/Controller.h"

FString UC_NotifySetCanInput::GetNotifyName_Implementation() const
{
	return "SetCanInput";
}

void UC_NotifySetCanInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AC_TopDownCharacter* tmpChar = Cast<AC_TopDownCharacter>(MeshComp->GetOwner());
	if (tmpChar)
	{
		tmpChar->canInput = true;
		tmpChar->GetController()->StopMovement();
	}
}

void UC_NotifySetCanInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	AC_TopDownCharacter* tmpChar = Cast<AC_TopDownCharacter>(MeshComp->GetOwner());
	if (tmpChar)
	{
		tmpChar->canInput = false;
	}
}
