// Fill out your copyright notice in the Description page of Project Settings.


#include "C_TopDownGameMode.h"
#include "C_TopDownController.h"
#include "C_TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"


AC_TopDownGameMode::AC_TopDownGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AC_TopDownController::StaticClass();
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/CBP_TopDownCharacter"));
	////static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/C_Test1"));
	//if (PlayerPawnBPClass.Class != nullptr)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/CBP_TopDownController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

}
