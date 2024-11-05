// Fill out your copyright notice in the Description page of Project Settings.

#include "CUW_CharacterOverHead.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UCUW_CharacterOverHead::NativeOnInitialized()
{


	CharName = Cast<UTextBlock>(GetWidgetFromName(TEXT("D_Name")));
	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("D_HpBar")));

}

void UCUW_CharacterOverHead::SetName(const FString& NewText)
{
	if (CharName)
	{
		CharName->SetText(FText::FromString(NewText));
	}
}

void UCUW_CharacterOverHead::SetHP(float curHp,float maxHp)
{
	if (HpBar)
	{
		HpBar->SetPercent(curHp / maxHp);
	}
}
