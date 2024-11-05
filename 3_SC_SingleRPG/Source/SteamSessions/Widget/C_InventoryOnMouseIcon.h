// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_InventoryOnMouseIcon.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_InventoryOnMouseIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void SetIcon(UTexture2D* texture);

public:
	UPROPERTY(VisibleAnywhere)
	class UImage* onMouseIconC;

};
