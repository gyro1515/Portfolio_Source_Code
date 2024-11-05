// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracer/C_TracerWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
//
#include "CharacterBase/C_BaseCharacter.h"
#include "Tracer/C_CharacterTracer.h"

void UC_TracerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// 이미지
	crossHairC = Cast<UImage>(GetWidgetFromName(TEXT("CrossHair")));
	QGaugeIconC = Cast<UImage>(GetWidgetFromName(TEXT("QGauge")));
	QGauge_CircleIconC = Cast<UImage>(GetWidgetFromName(TEXT("QGauge_Circle")));
	QButtonIconC = Cast<UImage>(GetWidgetFromName(TEXT("QButton")));
	skillIcon0C = Cast<UImage>(GetWidgetFromName(TEXT("SkillIcon_0")));
	skillIcon1C = Cast<UImage>(GetWidgetFromName(TEXT("SkillIcon_1")));
	skillButtonIcon0C = Cast<UImage>(GetWidgetFromName(TEXT("SkillButtonIcon_0")));
	skillButtonIcon1C = Cast<UImage>(GetWidgetFromName(TEXT("SkillButtonIcon_1")));
	weaponIconC = Cast<UImage>(GetWidgetFromName(TEXT("WeaponIcon")));
	// 프로그래스 바
	hpBarC = Cast<UProgressBar>(GetWidgetFromName(TEXT("CharHp")));
	// 텍스트
	curHpC = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurHp")));
	maxHpC = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxHp")));
	QGaugeNumC = Cast<UTextBlock>(GetWidgetFromName(TEXT("QGaugeNum")));
	QGaugePerC = Cast<UTextBlock>(GetWidgetFromName(TEXT("QGaugePer")));
	curBulletC = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurBullet")));
	maxBulletC = Cast<UTextBlock>(GetWidgetFromName(TEXT("MaxBullet")));
	skillE_CooltimeC = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LS_Cooltime")));
	skillLS_CooltimeC = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_E_Cooltime")));
	SetQGaugeIcon(false);

}

void UC_TracerWidget::NativeTick(const FGeometry& MyGeometry , float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);

}

void UC_TracerWidget::SetWidget(AC_BaseCharacter* _baseChar)
{
	player = _baseChar;
	AC_CharacterTracer* charTracer = Cast<AC_CharacterTracer>(_baseChar);

	curHpC->SetText(FText::FromString(FString::FromInt(( (int32)player->curHp ))));
	maxHpC->SetText(FText::FromString(FString::FromInt(( (int32)player->maxHp ))));
	QGaugeNumC->SetText(FText::FromString(FString::FromInt(( (int32)charTracer->UltGauge ))));
	QGaugePerC->SetText(FText::FromString(TEXT("%")));
	curBulletC->SetText(FText::FromString(FString::FromInt(( (int32)charTracer->maxBullet ))));
	maxBulletC->SetText(FText::FromString(FString::FromInt(( (int32)charTracer->curBullet ))));
	skillE_CooltimeC->SetText(FText::FromString(TEXT("")));
	skillLS_CooltimeC->SetText(FText::FromString(TEXT("")));

	hpBarC->SetPercent(( player->curHp / player->maxHp ));

}

void UC_TracerWidget::SetHp(float _curHp , float _maxHp)
{
	hpBarC->SetPercent(_curHp / _maxHp);
	curHpC->SetText(FText::FromString(FString::FromInt(( (int32)_curHp ))));

}

void UC_TracerWidget::SetBullet(int32 _cutBullet)
{
	curBulletC->SetText(FText::FromString(FString::FromInt(( _cutBullet ))));

}

void UC_TracerWidget::SetQGauge(float _QGauge)
{
	QGaugeNumC->SetText(FText::FromString(FString::FromInt(( (int32)_QGauge ))));
	if ( _QGauge >= 10.0f )
	{
		QGaugePerC->SetText(FText::FromString(TEXT("     %")));
	}
	else if ( _QGauge >= 100.0f )
	{
		QGaugePerC->SetText(FText::FromString(TEXT("       %")));
		SetQGaugeIcon(true);
		return;
	}
	else
	{
		QGaugePerC->SetText(FText::FromString(TEXT("%")));
	}
}

void UC_TracerWidget::SetQGaugeIcon(bool iconOnOff)
{
	if ( iconOnOff )
	{
		QGaugeIconC->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.65));
		QGauge_CircleIconC->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.0f));
		QGaugeNumC->SetColorAndOpacity(FLinearColor(1.0f , 1.0f , 1.0f , 0.0f));
		QGaugePerC->SetColorAndOpacity(FLinearColor(1.0f , 1.0f , 1.0f , 0.0f));
	}
	else
	{
		QGaugeIconC->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.0f));
		QGauge_CircleIconC->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.65));
		QGaugeNumC->SetColorAndOpacity(FLinearColor(1.0f , 1.0f , 1.0f , 1.0f));
		QGaugePerC->SetColorAndOpacity(FLinearColor(1.0f , 1.0f , 1.0f , 1.0f));
	}

}

void UC_TracerWidget::SetIconCoolTime(TSkillState skillState , bool _isCoolTime)
{
	if ( _isCoolTime )
	{
		switch ( skillState )
		{
		case TSkillState::Skill_E:
			skillIcon1C->SetBrushTintColor(FLinearColor(0.1f , 0.1f , 0.1f , 0.65));
			break;
		case TSkillState::SKill_LShift:
			skillIcon0C->SetBrushTintColor(FLinearColor(0.1f , 0.1f , 0.1f , 0.65));
			break;
		default:
			break;
		}
	}
	else
	{
		switch ( skillState )
		{
		case TSkillState::Skill_E:
			skillIcon1C->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.65));
			skillE_CooltimeC->SetText(FText::FromString(TEXT("")));
			break;
		case TSkillState::SKill_LShift:
			skillIcon0C->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.65));
			skillLS_CooltimeC->SetText(FText::FromString(TEXT("")));
			break;
		default:
			break;
		}
	}

}

void UC_TracerWidget::SetIconCoolTimeTmp(TSkillState skillState , float _tmpCoolTime)
{
	switch ( skillState )
	{
	case TSkillState::Skill_E:
		skillE_CooltimeC->SetText(FText::FromString(FString::FromInt(( (int32)_tmpCoolTime ))));
		break;
	case TSkillState::SKill_LShift:
		skillLS_CooltimeC->SetText(FText::FromString(FString::FromInt(( (int32)_tmpCoolTime ))));
		break;
	default:
		break;
	}

}
