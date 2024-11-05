// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/C_InventoryButton.h"
#include "Widget/C_Inventory.h"
#include "Blueprint/UserWidget.h"

UC_InventoryButton::UC_InventoryButton()
{
	inven = nullptr;
	myNum = -1;
	OnClicked.AddDynamic(this, &UC_InventoryButton::ReadyClick);
	OnHovered.AddDynamic(this, &UC_InventoryButton::ReadyHovered);
	OnUnhovered.AddDynamic(this, &UC_InventoryButton::ReadyUnHovered);
}

void UC_InventoryButton::ReadyClick()
{
	if (myNum != -1)
	{
		if (inven)
		{
			clickT.Broadcast(myNum);
		}
	}
}

void UC_InventoryButton::ReadyHovered()
{
	if (myNum != -1)
	{
		if (inven)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::MakeRandomColor(), TEXT("ReadyHovered"));
			hoveredT.Broadcast(myNum);
		}
	}
}

void UC_InventoryButton::ReadyUnHovered()
{
	if (myNum != -1)
	{
		if (inven)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::MakeRandomColor(), TEXT("ReadyUn!Hovered"));
			unHoveredT.Broadcast(myNum);
		}
	}
}

void UC_InventoryButton::SetInven(UC_Inventory* _inven)
{
	inven = _inven;
	if (inven)
	{
		clickT.AddDynamic(inven, &UC_Inventory::MouseClick);
		hoveredT.AddDynamic(inven, &UC_Inventory::MouseHovered);
		unHoveredT.AddDynamic(inven, &UC_Inventory::MouseUnHovered);
	}
}
