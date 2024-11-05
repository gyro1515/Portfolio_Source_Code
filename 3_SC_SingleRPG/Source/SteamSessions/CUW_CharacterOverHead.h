// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_CharacterOverHead.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UCUW_CharacterOverHead : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void SetName(const FString& NewText);

	UFUNCTION()
	void SetHP(float curHp,float maxHp);


	UPROPERTY()
	class UTextBlock* CharName;

	UPROPERTY()
	class UProgressBar* HpBar;

	//UPROPERTY()
	//class UTexture2D* ClassImage;

};
