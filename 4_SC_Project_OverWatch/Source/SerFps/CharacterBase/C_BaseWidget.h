// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_BaseWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class SkillState : uint8
{
	SKill_Q ,
	Skill_E,
	SKill_LShift
};

UCLASS()
class SERFPS_API UC_BaseWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	// 아이콘 이미지
	UPROPERTY()
	class UImage* crossHairC;
	UPROPERTY()
	class UImage* QGaugeIconC;
	UPROPERTY()
	class UImage* QGauge_CircleIconC;
	UPROPERTY()
	class UImage* QButtonIconC;
	UPROPERTY()
	class UImage* skillIcon0C;
	UPROPERTY()
	class UImage* skillIcon1C;
	UPROPERTY()
	class UImage* skillButtonIcon0C;
	UPROPERTY()
	class UImage* skillButtonIcon1C;
	UPROPERTY()
	class UImage* weaponIconC;
	// 체력바
	UPROPERTY()
	class UProgressBar* hpBarC;
	// 텍스트
	UPROPERTY()
	class UTextBlock* curHpC;
	UPROPERTY()
	class UTextBlock* maxHpC;
	UPROPERTY()
	class UTextBlock* QGaugeNumC;
	UPROPERTY()
	class UTextBlock* QGaugePerC;
	UPROPERTY()
	class UTextBlock* curBulletC;
	UPROPERTY()
	class UTextBlock* maxBulletC;
	UPROPERTY()
	class UTextBlock* skillE_CooltimeC;
	UPROPERTY()
	class UTextBlock* skillLS_CooltimeC;
	// 캐릭터
	class AC_BaseCharacter* player;
public:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry , float InDeltaTime) override;

	void SetWidget(class AC_BaseCharacter* _baseChar);
	void SetHp(float _curHp, float _maxHp);
	void SetBullet(int32 _cutBullet);
	void SetQGauge(float _QGauge);
	void SetQGaugeIcon(bool iconOnOff);
	void SetIconCoolTime(SkillState skillState, bool _isCoolTime);
	void SetIconCoolTimeTmp(SkillState skillState, float _tmpCoolTime);

};
