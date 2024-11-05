// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "C_InventoryButton.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickTest, int32, buttonNum);

UCLASS()
class STEAMSESSIONS_API UC_InventoryButton : public UButton
{
	GENERATED_BODY()
public:
	UC_InventoryButton();

	UFUNCTION()
	void ReadyClick();
	UFUNCTION()
	void ReadyHovered();
	UFUNCTION()
	void ReadyUnHovered();

	void SetInven(class UC_Inventory* _inven);

public:
	UPROPERTY()
	FClickTest clickT;
	UPROPERTY()
	FClickTest hoveredT;
	UPROPERTY()
	FClickTest unHoveredT;
public:
	UPROPERTY(EditAnywhere)
	int32 myNum;

	UPROPERTY(EditAnywhere)
	class UC_Inventory* inven;
	
};
