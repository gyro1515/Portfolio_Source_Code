// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SaveTopDown.h"
#include "C_TopDownController.h"
#include "Widget/C_Inventory.h"
#include "C_TopDownCharacter.h"
#include "Item/CItemStrut.h"
#include "Widget/C_Inventory.h"
#include "CharacterSelectWidget.h"

void UC_SaveTopDown::SaveData(AC_TopDownController* controller)
{
	characterHp_T = controller->Tank->CharacterHp;
	characterHp_D = controller->DPS->CharacterHp;
	characterHp_H = controller->Heal->CharacterHp;
	charName = controller->selectW->ChosenName;

	items.SetNum(20);
	ItemCounts.SetNum(20);
	for (int32 i = 0; i < 20; i++)
	{
		if (controller->InventoryC->items[i] != nullptr)
		{
			items[i] = controller->InventoryC->items[i]->ttetsU;
			ItemCounts[i] = controller->InventoryC->items[i]->ItemCount;
		}
		else
		{
			items[i];
			ItemCounts[i] = 0;
		}
		
	}

}

void UC_SaveTopDown::LoadData(AC_TopDownController* controller)
{
	AC_TopDownController* tmpCont = Cast<AC_TopDownController>(controller);
	tmpCont->Tank->CharacterHp = characterHp_T;
	tmpCont->Tank->UpdateHpPercent(tmpCont->Tank->CharacterHp, tmpCont->Tank->CharacterMaxHp);

	tmpCont->DPS->CharacterHp = characterHp_D;
	tmpCont->DPS->UpdateHpPercent(tmpCont->DPS->CharacterHp, tmpCont->DPS->CharacterMaxHp);

	tmpCont->Heal->CharacterHp = characterHp_H;
	tmpCont->Heal->UpdateHpPercent(tmpCont->Heal->CharacterHp, tmpCont->Heal->CharacterMaxHp);

	for (int32 i = 0; i < 20; i++)
	{
		if (tmpCont->InventoryC->items[i])
		{
			ACItemStrut* tmp = tmpCont->InventoryC->items[i];
			tmpCont->InventoryC->items[i] = nullptr;
			tmp->Destroy();
		}
		else
		{
			controller->InventoryC->items[i] = nullptr;
		}
	}
	UC_Inventory* tmpInven = Cast<UC_Inventory>(tmpCont->InventoryC);
	tmpInven->SetReadyLoad();

	for (int32 i = 0; i < 20; i++)
	{
		if (items[i].ItemName != TEXT(""))
		{
			//tmpInven->items[i]->SetItem(&items[i]);
			tmpInven->items[i]->SetItemU(items[i]);
			tmpInven->items[i]->ItemCount = ItemCounts[i];
		}
		else
		{
			ACItemStrut* tmp = tmpCont->InventoryC->items[i];
			tmpCont->InventoryC->items[i] = nullptr;
			tmp->Destroy();
		}
	}
	tmpCont->InventoryC->SetInven();

}
