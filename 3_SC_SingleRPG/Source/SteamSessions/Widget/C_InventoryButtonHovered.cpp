// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/C_InventoryButtonHovered.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Item/CItemStrut.h"

void UC_InventoryButtonHovered::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	onMouseIcon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	itemNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemNameText")));
	itemType = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemType")));
	itemPrice = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemPrice")));
	itemAbil = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemAbil")));
	isOn = false;
}

void UC_InventoryButtonHovered::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UC_InventoryButtonHovered::SetHoveredItemWidget(FItemBaseC _hoveredItem)
{
	hoveredItem = _hoveredItem;
	if (hoveredItem.ItemName == TEXT("")) return;
	if (hoveredItem.Icon)
	{
		onMouseIcon->SetBrushFromTexture(hoveredItem.Icon);
	}
	else return;

	FString tmp = hoveredItem.ItemName.ToString();
	itemNameText->SetText(FText::FromString(tmp));

	switch (hoveredItem.ItemType)
	{
	case ItemType::Equipment:
		tmp = TEXT("장비 아이템");
		break;
	case ItemType::Consumption:
		tmp = TEXT("소비 아이템");
		break;
	case ItemType::Material:
		tmp = TEXT("재료 아이템");
		break;
	default:
		break;
	}
	itemType->SetText(FText::FromString(tmp));

	// 아이템 가격 추후 추가
	tmp = TEXT("가격: 1,000원");
	itemPrice->SetText(FText::FromString(tmp));

	// 아이템 효과 설명
	FString tmpHp;
	FString tmpMp;

	switch (hoveredItem.ItemType)
	{
	case ItemType::Equipment:
		if (hoveredItem.Hp == 0) tmpHp = TEXT("");
		else tmpHp = TEXT("체력: ") + FString::FromInt(hoveredItem.Hp) + "\n";

		if (hoveredItem.Mp == 0) tmpMp = TEXT("");
		else tmpMp = TEXT("마나: ") + FString::FromInt(hoveredItem.Mp) + "\n";
		break;
	case ItemType::Consumption:
		if (hoveredItem.Hp == 0) tmpHp = TEXT("");
		else tmpHp = TEXT("체력 회복량: ") + FString::FromInt(hoveredItem.Hp) + "\n";

		if (hoveredItem.Mp == 0) tmpMp = TEXT("");
		else tmpMp = TEXT("마나 회복량: ") + FString::FromInt(hoveredItem.Mp) + "\n";
		break;
	case ItemType::Material:
		tmpHp = TEXT("");
		tmpMp = TEXT("");
		break;
	default:
		break;
	}
	

	FString tmpAtt;
	if (hoveredItem.Attack == 0) tmpAtt = TEXT("");
	else tmpAtt = TEXT("공격력: ") + FString::FromInt(hoveredItem.Attack) + "\n";

	FString tmpDef;
	if (hoveredItem.Def == 0) tmpDef = TEXT("");
	else tmpDef = TEXT("방어력: ") + FString::FromInt(hoveredItem.Def) + "\n";

	FString tmpSpeed;
	if (hoveredItem.Speed == 0) tmpSpeed = TEXT("");
	else tmpSpeed = TEXT("속도: ") + FString::FromInt(hoveredItem.Speed) + "\n";

	FString tmpSkillAcceleration;
	if (hoveredItem.SkillAcceleration == 0) tmpSkillAcceleration = TEXT("");
	else tmpSkillAcceleration = TEXT("스킬가속: ") + FString::FromInt(hoveredItem.SkillAcceleration) + "\n";

	FString allTmp = tmpHp + tmpMp + tmpAtt + tmpDef + tmpSpeed + tmpSkillAcceleration;

	FString tmpAbil; //= TEXT("효과: \n");
	if (allTmp == TEXT(""))
	{
		if (hoveredItem.ItemEffect == TEXT("")) tmpSkillAcceleration = TEXT("");
		else tmpAbil = TEXT("아이템 설명:\n") + hoveredItem.ItemEffect + "\n";
	}
	else
	{
		if (hoveredItem.ItemEffect == TEXT("")) tmpSkillAcceleration = TEXT("");
		else tmpAbil = TEXT("\n아이템 설명:\n") + hoveredItem.ItemEffect + "\n";
	}

	allTmp += tmpAbil;

	itemAbil->SetText(FText::FromString(allTmp));
}
