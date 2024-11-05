// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "CharacterSelectWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTextChangeDelegate, const FText&, NewText);
/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void ChooseTank();

	UFUNCTION()
	void ChooseDPS();

	UFUNCTION()
	void ChooseHeal();

	UFUNCTION()
	void Confirmed();



	UFUNCTION()
	int GetChosenInt() { return ChosenClass; }


public:
	UPROPERTY(VisibleDefaultsOnly)
	class UButton* btank;
	
	UPROPERTY(VisibleDefaultsOnly)
	class UButton* bdps;

	UPROPERTY(VisibleDefaultsOnly)
	class UButton* bheal;

	UPROPERTY(VisibleAnywhere)
	int ChosenClass = 0;



	UPROPERTY(VisibleDefaultsOnly)
	class UButton* bconfirm;


	//UPROPERTY(meta = (BindWidget))
	UPROPERTY()
	class UEditableTextBox* enamebox;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FTextChangeDelegate OnTextChanged;

	UFUNCTION(BlueprintCallable, Category = "Event")
	void OnChangeName(const FText& Text);

	UPROPERTY(VisibleAnywhere)
	FString ChosenName;

};
