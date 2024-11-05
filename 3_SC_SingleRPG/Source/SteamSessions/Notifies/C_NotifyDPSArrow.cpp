// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/C_NotifyDPSArrow.h"
#include "Skill/C_SkillManager.h"
#include "Skill/C_Attack.h"
#include "C_TopDownCharacter.h"

FString UC_NotifyDPSArrow::GetNotifyName_Implementation() const
{
	return "NotifyDPSArrow";
}

void UC_NotifyDPSArrow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("NotifyIn")));

	AC_TopDownCharacter* tmpChar = Cast<AC_TopDownCharacter>(MeshComp->GetOwner());
	if (tmpChar)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("NotifyDPS")));

		FAttackBaseC tmpBase;
		FName tmpName = TEXT("Notify_DPS_0");
		tmpBase = *(tmpChar->dataTable->FindRow<FAttackBaseC>(tmpName, tmpName.ToString()));
		tmpChar->SkillManager->SpawnAttackDPS(tmpChar, tmpBase);
	}
}
