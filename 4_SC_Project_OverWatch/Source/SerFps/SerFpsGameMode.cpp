// Copyright Epic Games, Inc. All Rights Reserved.

#include "SerFpsGameMode.h"
#include "SerFpsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASerFpsGameMode::ASerFpsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
