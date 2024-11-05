// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/C_InventoryOnMouseIcon.h"

#include "Components/Image.h"

void UC_InventoryOnMouseIcon::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	onMouseIconC = Cast<UImage>(GetWidgetFromName(TEXT("OnMouseIcon")));
}

void UC_InventoryOnMouseIcon::SetIcon(UTexture2D* texture)
{
	if (onMouseIconC)
	{
		if (texture->IsValidLowLevel())
		{
			onMouseIconC->SetBrushFromTexture(texture);
		}
	}
}
