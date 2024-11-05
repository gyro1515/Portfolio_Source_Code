// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_ZoneWidget.generated.h"

/**
 * 
 */
UCLASS()
class SERFPS_API UC_ZoneWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry , float InDeltaTime) override;
public:
	UPROPERTY(EditAnywhere)
	class UAudioComponent* zoneSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* HeartSound;

};
