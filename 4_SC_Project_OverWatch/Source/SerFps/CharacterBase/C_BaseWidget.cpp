// Fill out your copyright notice in the Description page of Project Settings.

// 위젯
#include "CharacterBase/C_BaseWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
//
#include "CharacterBase/C_BaseCharacter.h"
#include "Genji/C_CharacterGenji.h"

void UC_BaseWidget::NativeOnInitialized()
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
	//if ( crossHairC && QGaugeIconC && QButtonIconC && skillIcon1C && skillIcon0C && skillButtonIcon0C && skillButtonIcon1C && weaponIconC 
	//	&& hpBarC && curHpC && maxHpC && QGaugeNumC && QGaugePerC && curBulletC && maxBulletC )
	//{
	//	GEngine->AddOnScreenDebugMessage(-1 , 5.0f , FColor::MakeRandomColor() , TEXT("WidgetReady"));
	//}
	SetQGaugeIcon(false);
}

void UC_BaseWidget::NativeTick(const FGeometry& MyGeometry , float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);

}

void UC_BaseWidget::SetWidget(AC_BaseCharacter* _baseChar)
{
	// 겐지 기준
	player = _baseChar;
	AC_CharacterGenji* charGenji = Cast<AC_CharacterGenji>(_baseChar);

	curHpC->SetText(FText::FromString(FString::FromInt(( (int32)player->curHp))));
	maxHpC->SetText(FText::FromString(FString::FromInt(( (int32)player->maxHp))));
	QGaugeNumC->SetText(FText::FromString(FString::FromInt(( (int32)charGenji->GetQGauge()))));
	QGaugePerC->SetText(FText::FromString(TEXT("%")));
	curBulletC->SetText(FText::FromString(FString::FromInt(( (int32)charGenji->maxPyoChangCount))));
	maxBulletC->SetText(FText::FromString(FString::FromInt(( (int32)charGenji->leftPyoChangCount))));
	skillE_CooltimeC->SetText(FText::FromString(TEXT("")));
	skillLS_CooltimeC->SetText(FText::FromString(TEXT("")));

	hpBarC->SetPercent(( player->curHp / player->maxHp ));
}

void UC_BaseWidget::SetHp(float _curHp , float _maxHp)
{
	if ( !player ) return;
	
	hpBarC->SetPercent(_curHp/ _maxHp);
	curHpC->SetText(FText::FromString(FString::FromInt(( (int32)_curHp ))));
}

void UC_BaseWidget::SetBullet(int32 _cutBullet)
{
	if ( !curBulletC ) return;
	curBulletC->SetText(FText::FromString(FString::FromInt(( _cutBullet ))));
}

void UC_BaseWidget::SetQGauge(float _QGauge)
{
	if ( !QGaugeNumC ) return;

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

void UC_BaseWidget::SetQGaugeIcon(bool iconOnOff)
{
	if ( !QGaugeIconC || !QGauge_CircleIconC  || !QGaugeNumC || !QGaugePerC ) return;

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

void UC_BaseWidget::SetIconCoolTime(SkillState skillState , bool _isCoolTime)
{
	if ( !skillIcon1C || !skillIcon0C ) return;

	if ( _isCoolTime )
	{
		switch ( skillState )
		{
		case SkillState::Skill_E:
			skillIcon1C->SetBrushTintColor(FLinearColor(0.1f , 0.1f , 0.1f , 0.65));
			break;
		case SkillState::SKill_LShift:
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
		case SkillState::Skill_E:
			skillIcon1C->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.65));
			skillE_CooltimeC->SetText(FText::FromString(TEXT("")));
			break;
		case SkillState::SKill_LShift:
			skillIcon0C->SetBrushTintColor(FLinearColor(1.0f , 1.0f , 1.0f , 0.65));
			skillLS_CooltimeC->SetText(FText::FromString(TEXT("")));
			break;
		default:
			break;
		}
	}
	
}

void UC_BaseWidget::SetIconCoolTimeTmp(SkillState skillState , float _tmpCoolTime)
{
	if ( !IsValid(player) ) return;
	if ( !skillE_CooltimeC || !skillLS_CooltimeC ) return;

	switch ( skillState )
	{
	case SkillState::Skill_E:
		skillE_CooltimeC->SetText(FText::FromString(FString::FromInt(( (int32)_tmpCoolTime ))));
		break;
	case SkillState::SKill_LShift:
		skillLS_CooltimeC->SetText(FText::FromString(FString::FromInt(( (int32)_tmpCoolTime ))));
		break;
	default:
		break;
	}
}
