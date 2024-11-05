// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/CItemStrut.h"

#include "C_InventoryButtonHovered.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_InventoryButtonHovered : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	void SetHoveredItemWidget(FItemBaseC _hoveredItem);
public:
	FItemBaseC hoveredItem;
	UPROPERTY(VisibleAnywhere)
	class UImage* onMouseIcon;
	UPROPERTY(VisibleAnywhere)
	class UTextBlock* itemNameText;
	UPROPERTY(VisibleAnywhere)
	class UTextBlock* itemType;
	UPROPERTY(VisibleAnywhere)
	class UTextBlock* itemPrice;
	UPROPERTY(VisibleAnywhere)
	class UTextBlock* itemAbil;
	bool isOn;
};
