// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/C_UI.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Skill/C_Attack.h"
#include "C_TopDownCharacter.h"
#include "C_TopDownController.h"
#include "Skill/C_SkillManager.h"
#include "Materials/Material.h"
#include "EnhancedInputSubsystems.h"
#include "Components/TextBlock.h"



void UC_UI::NativeOnInitialized()
{

	Super::NativeOnInitialized();

	TankHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("CH1_HP")));
	DPSHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("CH2_HP")));
	HealHp = Cast<UProgressBar>(GetWidgetFromName(TEXT("CH3_HP")));

	TankIM = Cast<UImage>(GetWidgetFromName(TEXT("CH1_Name")));
	DPSIM = Cast<UImage>(GetWidgetFromName(TEXT("CH2_Name")));
	HealIM = Cast<UImage>(GetWidgetFromName(TEXT("CH3_Name")));


	MainHp = Cast<UProgressBar>(GetWidgetFromName(TEXT("Main_HP")));

	UI_Q = Cast<UImage>(GetWidgetFromName(TEXT("SkillUI_Q")));
	UI_W = Cast<UImage>(GetWidgetFromName(TEXT("SkillUI_W")));
	UI_E = Cast<UImage>(GetWidgetFromName(TEXT("SkillUI_E")));

	UI_Item1 = Cast<UImage>(GetWidgetFromName(TEXT("ItemUI_1")));
	UI_Item2 = Cast<UImage>(GetWidgetFromName(TEXT("ItemUI_2")));

	MiniM = Cast<UImage>(GetWidgetFromName(TEXT("MiniMap")));

	MiniP1 = Cast<UImage>(GetWidgetFromName(TEXT("Mini_P1")));
	MiniP2 = Cast<UImage>(GetWidgetFromName(TEXT("Mini_P2")));
	MiniP3 = Cast<UImage>(GetWidgetFromName(TEXT("Mini_P3")));

	TestController = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());

	hpCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("HpNum")));
	mpCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("MpNum")));
	hpBar = Cast<UTextBlock>(GetWidgetFromName(TEXT("Hp")));
	mpBar = Cast<UTextBlock>(GetWidgetFromName(TEXT("Mp")));
	TankName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Tank")));
	DpsName = Cast<UTextBlock>(GetWidgetFromName(TEXT("DPS")));
	HealName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Heal")));

	MiniMapSize = FVector2D(3000, 3500);
	MiniMapC_Set = FVector2D(0, 0);
}

void UC_UI::SetPlayerUI(AC_TopDownCharacter* player)
{

	Testplayer = player;
	//Testplayer->SkillManager->attacks[AttackInput::Q]->isOnCoolDown
	/*
	if (Testplayer->SkillManager->attacks[AttackInput::Q]->isOnCoolDown)
	{
		FString tmpF = FString::Printf(TEXT("TestGOODGOOD"));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), tmpF);
	}
	*/

	//testMda = LoadObject<UMaterial>(nullptr, TEXT("/Game/TopDown/TestM/testMDa"));


	UMaterialInstanceDynamic* DynamicMaterial1 = UMaterialInstanceDynamic::Create(testMda, this);
	UMaterialInstanceDynamic* DynamicMaterial2 = UMaterialInstanceDynamic::Create(testMda, this);
	UMaterialInstanceDynamic* DynamicMaterial3 = UMaterialInstanceDynamic::Create(testMda, this);
	UMaterialInstanceDynamic* DynamicMaterial4 = UMaterialInstanceDynamic::Create(testMda, this);
	UMaterialInstanceDynamic* DynamicMaterial5 = UMaterialInstanceDynamic::Create(testMda, this);


	if (Testplayer != nullptr)
	{
		//DynamicMaterial1->SetTextureParameterValue("SetImageDa"
		//	, Testplayer->q_AttackBase->AttackIcon);
		//
		//UI_Q->SetBrushFromMaterial(DynamicMaterial1);
		//
		//DynamicMaterial2->SetTextureParameterValue("SetImageDa"
		//	, Testplayer->w_AttackBase->AttackIcon);
		//
		//UI_W->SetBrushFromMaterial(DynamicMaterial2);
		//
		//DynamicMaterial3->SetTextureParameterValue("SetImageDa"
		//	, Testplayer->e_AttackBase->AttackIcon);
		//
		//UI_E->SetBrushFromMaterial(DynamicMaterial3);
		
		//240611 ����
		DynamicMaterial1->SetTextureParameterValue("SetImageDa"
			, Testplayer->q_AttackBaseU.AttackIcon);

		UI_Q->SetBrushFromMaterial(DynamicMaterial1);

		DynamicMaterial2->SetTextureParameterValue("SetImageDa"
			, Testplayer->w_AttackBaseU.AttackIcon);

		UI_W->SetBrushFromMaterial(DynamicMaterial2);

		DynamicMaterial3->SetTextureParameterValue("SetImageDa"
			, Testplayer->e_AttackBaseU.AttackIcon);

		UI_E->SetBrushFromMaterial(DynamicMaterial3);

		// ������ 
		DynamicMaterial4->SetTextureParameterValue("SetImageDa"
			, TestController->hpPotion->ttetsU.Icon);
		UI_Item1->SetBrushFromMaterial(DynamicMaterial4);

		DynamicMaterial5->SetTextureParameterValue("SetImageDa"
			, TestController->mpPotion->ttetsU.Icon);
		UI_Item2->SetBrushFromMaterial(DynamicMaterial5);
	}

	// ü�� ����
	SetHpBar();

	FString tmpF = FString::Printf(TEXT("TestGood"));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), tmpF);


	if (RenderT)
	{
		MiniP1->SetRenderScale(FVector2D(0, 0));
		MiniP2->SetRenderScale(FVector2D(0, 0));
		MiniP3->SetRenderScale(FVector2D(0, 0));
	}
	else
	{
		MiniP1->SetRenderScale(FVector2D(1, 1));
		MiniP2->SetRenderScale(FVector2D(1, 1));
		MiniP3->SetRenderScale(FVector2D(1, 1));
	}


}

void UC_UI::SetTeamHp(AC_TopDownCharacter* Tank, AC_TopDownCharacter* DPS, AC_TopDownCharacter* Heal)
{

	TankHP->SetPercent(Tank->CharacterHp / Tank->CharacterMaxHp);
	DPSHP->SetPercent(DPS->CharacterHp / DPS->CharacterMaxHp);
	HealHp->SetPercent(Heal->CharacterHp / Heal->CharacterMaxHp);



}

void UC_UI::SetMyHp(AC_TopDownCharacter* playerHP)
{

	MainHp->SetPercent(playerHP->CharacterHp / playerHP->CharacterMaxHp);

}

void UC_UI::SetCoolTime()
{
	if (Testplayer != nullptr && Testplayer->SkillManager->attacks[AttackInput::Q] != nullptr
		&& Testplayer->SkillManager->attacks[AttackInput::Q]->isOnCoolDown)
	{
		UI_Q->GetDynamicMaterial()->SetScalarParameterValue("CoolTime",
			Testplayer->SkillManager->attacks[AttackInput::Q]->time / Testplayer->q_AttackBaseU.CoolTime);
	}
	//else if (Testplayer != nullptr && (Testplayer->SkillManager->attacks[AttackInput::Q] == nullptr || Testplayer->SkillManager->attacks[AttackInput::Q]->isOnCoolDown))
	else if (Testplayer != nullptr)
		UI_Q->GetDynamicMaterial()->SetScalarParameterValue("CoolTime", 1);

	if (Testplayer != nullptr && Testplayer->SkillManager->attacks[AttackInput::W] != nullptr
		&& Testplayer->SkillManager->attacks[AttackInput::W]->isOnCoolDown)
	{
		UI_W->GetDynamicMaterial()->SetScalarParameterValue("CoolTime",
			Testplayer->SkillManager->attacks[AttackInput::W]->time / Testplayer->w_AttackBaseU.CoolTime);

	}
	else if (Testplayer != nullptr)
		UI_W->GetDynamicMaterial()->SetScalarParameterValue("CoolTime", 1);

	if (Testplayer != nullptr && Testplayer->SkillManager->attacks[AttackInput::E] != nullptr
		&& Testplayer->SkillManager->attacks[AttackInput::E]->isOnCoolDown)
	{
		UI_E->GetDynamicMaterial()->SetScalarParameterValue("CoolTime",
			Testplayer->SkillManager->attacks[AttackInput::E]->time / Testplayer->e_AttackBaseU.CoolTime);

	}
	else if (Testplayer != nullptr)
		UI_E->GetDynamicMaterial()->SetScalarParameterValue("CoolTime", 1);


	



	// ƽ���� ������

	/*
	if (Testplayer->SkillManager->attacks[AttackInput::Q]->isOnCoolDown &&
		Testplayer->SkillManager->attacks[AttackInput::Q] != nullptr)
	{
		FString tmpF = FString::Printf(TEXT("TestGOODGOOD"));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), tmpF);
	}
	*/



}

void UC_UI::SetPotionCoolTime()
{
	if (TestController->bIsPotionCoolTime)
	{
		UI_Item1->GetDynamicMaterial()->SetScalarParameterValue("CoolTime",
			TestController->tmpPotionCoolTime / TestController->potionCoolTime);
		UI_Item2->GetDynamicMaterial()->SetScalarParameterValue("CoolTime",
			TestController->tmpPotionCoolTime / TestController->potionCoolTime);
	}
	else
	{
		UI_Item1->GetDynamicMaterial()->SetScalarParameterValue("CoolTime", 1);
		UI_Item2->GetDynamicMaterial()->SetScalarParameterValue("CoolTime", 1);
	}
}

void UC_UI::SetPotionCount()
{
	hpCount->SetText(FText::FromString(FString::FromInt((TestController->hpPotion->ItemCount))));
	mpCount->SetText(FText::FromString(FString::FromInt((TestController->mpPotion->ItemCount))));
}

void UC_UI::SetHpBar()
{
	if (Testplayer)
	{
		FString tmpHP = FString::FromInt(Testplayer->CharacterHp);
		FString tmpMaxHP = FString::FromInt(Testplayer->CharacterMaxHp);
		FString tmpHpBar = TEXT("HP :  ") + tmpHP + TEXT(" / ") + tmpMaxHP;
		hpBar->SetText(FText::FromString(tmpHpBar));
	}
}

void UC_UI::BoolCoolTime(AttackInput test)
{

	// testDa1 = test;

}

void UC_UI::SetMiniMap(UMaterial* minimap)
{

	MiniM->SetBrushFromMaterial(minimap);


}

void UC_UI::SetMiniMapI(UMaterialInstance* minimap)
{

	MiniM->SetBrushFromMaterial(minimap);


}

void UC_UI::SetMiniMapT(UTexture2D* minimap)
{

	MiniM->SetBrushFromTexture(minimap);
	

}

void UC_UI::SetMiniMapSize(FVector2D minimapSize)
{
	MiniM->SetBrushSize(minimapSize);
}


void UC_UI::SetMiniPLocation(FVector P1, FVector P2, FVector P3)
{
	FWidgetTransform test;

	//P1.X += 1200;
	//P1.X = 2600 - P1.X;
	//P1.X /= 2600;
	//P1.X *= 256;
	//P1.X += 190;
	//
	//P1.Y += 1750;
	//P1.Y /= 3400;
	//P1.Y *= 256;
	//P1.Y += 1400;
	//
	//test.Translation = FVector2D(P1.Y, P1.X);
	//MiniP1->SetRenderTransform(test);
	//P2.X += 1200;
	//P2.X = 2600 - P2.X;
	//P2.X /= 2600;
	//P2.X *= 256;
	//P2.X += 190;
	//
	//P2.Y += 1750;
	//P2.Y /= 3400;
	//P2.Y *= 256;
	//P2.Y += 1400;
	//test.Translation = FVector2D(P2.Y, P2.X);
	//MiniP2->SetRenderTransform(test);
	//
	//P3.X += 1200;
	//P3.X = 2600 - P3.X;
	//P3.X /= 2600;
	//P3.X *= 256;
	//P3.X += 190;
	//
	//P3.Y += 1750;
	//P3.Y /= 3400;
	//P3.Y *= 256;
	//P3.Y += 1400;
	//test.Translation = FVector2D(P3.Y, P3.X);
	//MiniP3->SetRenderTransform(test);


	// ž�ٿ��: x 3000, y 3500 ũ��

	

	FVector2D tmp2D;
	tmp2D.X = P1.X / MiniMapSize.X;
	tmp2D.Y = P1.Y / MiniMapSize.Y;
	tmp2D.X = 1 - tmp2D.X;

	FVector2D localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	localViewPortSize.X -= 256.0f;
	localViewPortSize.X += MiniMapC_Set.X + (256.0f * tmp2D.Y) + 3.0;
	localViewPortSize.Y = MiniMapC_Set.Y + MiniM->GetDesiredSize().Y * tmp2D.X + 5.0;

	test.Translation = FVector2D(localViewPortSize.X, localViewPortSize.Y);
	MiniP1->SetRenderTransform(test);
	localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("M-X: %f, Y: %f\nView X: %f, Y: %f\ntmp X: %f, Y: %f" )
	//	, MiniP1->GetRenderTransform().Translation.X, MiniP1->GetRenderTransform().Translation.Y, localViewPortSize.X, localViewPortSize.Y, tmp2D.X, tmp2D.Y));
	
	tmp2D.X = P2.X / MiniMapSize.X;
	tmp2D.Y = P2.Y / MiniMapSize.Y;
	tmp2D.X = 1 - tmp2D.X;

	localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	// 256 = �̴ϸ� ������
	localViewPortSize.X -= 256.0;
	localViewPortSize.X += MiniMapC_Set.X+ (256.0f * tmp2D.Y);
	localViewPortSize.Y = MiniMapC_Set.Y + MiniM->GetDesiredSize().Y * tmp2D.X;

	test.Translation = FVector2D(localViewPortSize.X, localViewPortSize.Y);
	MiniP2->SetRenderTransform(test);

	tmp2D.X = P3.X / MiniMapSize.X;
	tmp2D.Y = P3.Y / MiniMapSize.Y;
	tmp2D.X = 1 - tmp2D.X;

	localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();

	localViewPortSize.X -= 256.0;
	localViewPortSize.X += MiniMapC_Set.X+(256.0f * tmp2D.Y);
	localViewPortSize.Y = MiniMapC_Set.Y+ MiniM->GetDesiredSize().Y * tmp2D.X;

	test.Translation = FVector2D(localViewPortSize.X, localViewPortSize.Y);
	MiniP3->SetRenderTransform(test);




	





}

void UC_UI::SetCharName(const FString& _Tank, const FString& _Dps, const FString& _Heal)
{
	TankName->SetText(FText::FromString(_Tank));
	DpsName->SetText(FText::FromString(_Dps));
	HealName->SetText(FText::FromString(_Heal));
}

