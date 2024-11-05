// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skill/C_Attack.h"
#include "C_UI.generated.h"


/**
 *
 */
UCLASS()
class STEAMSESSIONS_API UC_UI : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual void NativeOnInitialized() override;

	void SetPlayerUI(class AC_TopDownCharacter* player);

	void SetTeamHp(AC_TopDownCharacter* Tank, AC_TopDownCharacter* DPS, AC_TopDownCharacter* Heal);
	void SetMyHp(AC_TopDownCharacter* playerHP);

	void SetCoolTime();
	void SetPotionCoolTime();
	void SetPotionCount();
	void SetHpBar();
	void BoolCoolTime(AttackInput test);

	void SetMiniMap(UMaterial* minimap);
	void SetMiniMapI(UMaterialInstance* minimap);
	void SetMiniMapT(UTexture2D* minimap);
	void SetMiniMapSize(FVector2D minimapSize);
	void SetMiniPLocation(FVector P1, FVector P2, FVector P3);

	void SetCharName(const FString& _Tank, const FString& _Dps, const FString& _Heal);

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* TankHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* TankIM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* DPSHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* DPSIM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* HealHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* HealIM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* MainHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProgressBar* MainMp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* UI_Q;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* UI_W;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* UI_E;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* UI_Item1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* UI_Item2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* testMda;

	// ���� ����
	UPROPERTY()
	class UTextBlock* hpCount;
	UPROPERTY()
	class UTextBlock* mpCount;
	// ���õ� ĳ���� ü��
	UPROPERTY()
	class UTextBlock* hpBar;
	UPROPERTY()
	class UTextBlock* mpBar;

	UPROPERTY()
	class UTextBlock* TankName;
	UPROPERTY()
	class UTextBlock* DpsName;
	UPROPERTY()
	class UTextBlock* HealName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* MiniM;

	class AC_TopDownCharacter* Testplayer;
	class AC_TopDownController* TestController;

	// Minimap Image

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* MiniP1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* MiniP2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UImage* MiniP3;

	bool MapCheck = false;
	bool RenderT = false;


	FVector2d MiniMapSize;
	FVector2d MiniMapC_Set;

	// UPROPERTY(VisibleAnywhere)
	// class Character_SkillUI* Skill_UI;

	/*
	float Q_current = 0;
	float W_current = 0;
	float E_current = 0;

	AttackInput testDa1 = AttackInput::E;
	AttackInput testDa2 = AttackInput::E;
	AttackInput testDa3 = AttackInput::E;
	*/
};
