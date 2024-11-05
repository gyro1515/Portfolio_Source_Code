// Fill out your copyright notice in the Description page of Project Settings.


#include "C_TopDownViewPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "C_TopDownController.h"
#include "C_TopDownCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Widget/C_TopDownViewMove.h"
#include "Blueprint/WidgetLayoutLibrary.h"


// Sets default values
AC_TopDownViewPawn::AC_TopDownViewPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootScene);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	//CameraBoom->TargetArmLength = 800.f;
	CameraBoom->TargetArmLength = 1600.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CameraMove = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("CameraMove"));

}

// Called when the game starts or when spawned
void AC_TopDownViewPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(DefaultMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Started, this, &AC_TopDownViewPawn::ViewMove);
			EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Triggered, this, &AC_TopDownViewPawn::ViewMove);
			EnhancedInputComponent->BindAction(WheelRotation, ETriggerEvent::Triggered, this, &AC_TopDownViewPawn::ViewRotation);
			EnhancedInputComponent->BindAction(toPlayer, ETriggerEvent::Started, this, &AC_TopDownViewPawn::ViewLocation);
			EnhancedInputComponent->BindAction(WheelClick, ETriggerEvent::Started, this, &AC_TopDownViewPawn::SetMouseOff);
			EnhancedInputComponent->BindAction(WheelClick, ETriggerEvent::Completed, this, &AC_TopDownViewPawn::SetMouseON);
		}

	}

	//topDownViewMoveWidget = Cast<UC_TopDownViewMove>(CreateWidget(GetWorld(),topDownViewMoveWidgetClass));
	//topDownViewMoveWidget->SetTopDownViewPawn(this);
	//topDownViewMoveWidget->AddToViewport(1);

	moveVector.X = 0.0f;
	moveVector.Y = 0.0f;
	moveVector.Z = 0.0f;

	topDownController = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AC_TopDownViewPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (topDownController->selectW->IsInViewport()) return;
	if (topDownController->isInvenOn) return;
	if (!canMove) return;

	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	float tmpL = localViewPortSize.X * 0.07f;
	float tmpR = localViewPortSize.X * 0.93f;
	float tmpT = localViewPortSize.Y * 0.07f;
	float tmpB = localViewPortSize.Y * 0.93f;

	if (mousePosition.X < tmpL	|| mousePosition.X > tmpR || mousePosition.Y < tmpT || mousePosition.Y > tmpB)
	{
		localViewPortSize /= 2;
		mousePosition.X -= localViewPortSize.X;
		mousePosition.Y -= localViewPortSize.Y;
		moveVector.X = -mousePosition.Y;
		moveVector.Y = mousePosition.X;

		FRotator acRot = GetActorRotation();
		FRotator tmpRot = moveVector.GetSafeNormal().Rotation();
		tmpRot += acRot;

		CameraMove->AddInputVector(tmpRot.Vector());
	}
	else
	{
		moveVector.Y = 0.0f;
		moveVector.X = 0.0f;
	}

	
}

// Called to bind functionality to input
void AC_TopDownViewPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	//{
	//	EnhancedInputComponent->BindAction(WheelAction, ETriggerEvent::Started, this, &AC_TopDownViewPawn::ViewMove);
	//	EnhancedInputComponent->BindAction(WheelRotation, ETriggerEvent::Triggered, this, &AC_TopDownViewPawn::ViewRotation);
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("SetKey")));
	//
	//}
}

void AC_TopDownViewPawn::ViewMove(const FInputActionValue& value)
{

	FVector tmpMoveVector = value.Get<FVector>() * 50;
	// 여기선 Z값만 쓰기
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveX: %f"), moveVector.X));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveY: %f"), moveVector.Y));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveZ: %f"), moveVector.Z));
	CameraBoom->TargetArmLength += tmpMoveVector.Z;
	if (CameraBoom->TargetArmLength > 3000)
	{
		CameraBoom->TargetArmLength = 3000;
	}
	else if (CameraBoom->TargetArmLength < 400)
	{
		CameraBoom->TargetArmLength = 400;
	}
	//CameraMove->AddInputVector(moveVector);
}

void AC_TopDownViewPawn::ViewRotation(const FInputActionValue& value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Rot")));
	APlayerController* tmp = Cast<APlayerController>(GetController());
	if (tmp->IsInputKeyDown(EKeys::MiddleMouseButton))
	{
		FVector2D lookVector = value.Get<FVector2D>();
		//FRotator rot = { 3.14f * lookVector.Y,3.14f * lookVector.X,0.0f };
		FRotator rot = { 0.0f,3.14f * lookVector.X,0.0f };
		//CameraBoom->AddWorldRotation(rot);
		AddActorWorldRotation(rot);
		

		// 피치 로테이션 뺄거면 아래 두 줄 주석처리
		FRotator rot2 = { 3.14f * lookVector.Y, 0.0f, 0.0f };
		CameraBoom->AddLocalRotation(rot2);
	}
}

void AC_TopDownViewPawn::ViewLocation()
{
	AC_TopDownController* tmp = Cast<AC_TopDownController>(GetController());
	if (tmp)
	{
		SetActorLocation(tmp->selectedCharacter->GetActorLocation());
	}
}

void AC_TopDownViewPawn::SetMouseOff()
{
	APlayerController* tmp = Cast<APlayerController>(GetController());
	if (tmp)
	{
		tmp->GetMousePosition(tmpMousePos.X, tmpMousePos.Y);
		tmp->SetShowMouseCursor(false);
		canMove = false;
	}
}

void AC_TopDownViewPawn::SetMouseON()
{
	APlayerController* tmp = Cast<APlayerController>(GetController());
	if (tmp)
	{
		tmp->SetMouseLocation(tmpMousePos.X, tmpMousePos.Y);
		tmp->SetShowMouseCursor(true);
		canMove = true;
	}
}

