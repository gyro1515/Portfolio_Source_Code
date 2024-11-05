// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_TopDownGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_TopDownGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FString lastMapName;
	FString CurrentName;
};
