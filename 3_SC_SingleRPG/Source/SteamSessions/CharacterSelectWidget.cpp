// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectWidget.h"
#include "C_TopDownController.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

void UCharacterSelectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	btank = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Tank")));
	bdps = Cast<UButton>(GetWidgetFromName(TEXT("BTN_DPS")));
	bheal = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Healer")));
	bconfirm = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Confirm")));

	enamebox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Edit_Name")));

	btank->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ChooseTank);
	bdps->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ChooseDPS);
	bheal->OnClicked.AddDynamic(this, &UCharacterSelectWidget::ChooseHeal);
	bconfirm->OnClicked.AddDynamic(this, &UCharacterSelectWidget::Confirmed);

	if (enamebox)
	{
		enamebox->OnTextChanged.AddDynamic(this, &UCharacterSelectWidget::OnChangeName);
	}
	//enamebox->OnTextChanged.AddDynamic()
	//enamebox->OnTextChanged.AddDynamic(this, &UCharacterSelectWidget::OnChangeName(const FText & Text));
}

void UCharacterSelectWidget::ChooseTank()
{
	ChosenClass = 0;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChoseClass :  %d"), ChosenClass));

}

void UCharacterSelectWidget::ChooseDPS()
{
	ChosenClass = 1;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChoseClass :  %d"), ChosenClass));

}

void UCharacterSelectWidget::ChooseHeal()
{
	ChosenClass = 2;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChoseClass :  %d"), ChosenClass));
}

void UCharacterSelectWidget::Confirmed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChoseClass :  %d"), ChosenClass));
	AC_TopDownController* tmp = Cast<AC_TopDownController>(GetOwningPlayer());
	tmp->ControlAccess(ChosenName, ChosenClass);
}

void UCharacterSelectWidget::OnChangeName(const FText& Text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChangeName")));
	ChosenName = Text.ToString();
	OnTextChanged.Broadcast(Text);
}