// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/C_ZoneWidget.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UC_ZoneWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UC_ZoneWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//zoneSound = CreateDefaultSubobject<UAudioComponent>(TEXT("zoneSoundCom"));
	//zoneSound = NewObject<UAudioComponent>(this , UAudioComponent::StaticClass());
	

}

void UC_ZoneWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	zoneSound = UGameplayStatics::SpawnSound2D(this , HeartSound,1.0f, 1.0f, 0.0f, nullptr, false, false);
	zoneSound->bAutoActivate = false; // 자동 재생 비활성화
	zoneSound->SetUISound(true);
	zoneSound->Stop();
	
}

void UC_ZoneWidget::NativeTick(const FGeometry& MyGeometry , float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);

}
