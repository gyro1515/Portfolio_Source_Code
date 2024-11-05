// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/C_TopDownViewMove.h"
#include "Components/Button.h"
#include "C_TopDownViewPawn.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void UC_TopDownViewMove::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//buttonsL = Cast<UButton>(GetWidgetFromName(TEXT("Button_L")));
	//buttonsL->OnHovered.AddDynamic(this, &UC_TopDownViewMove::LHover);
	//buttonsL->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::LRUnHover);
	//buttonsR = Cast<UButton>(GetWidgetFromName(TEXT("Button_R")));
	//buttonsR->OnHovered.AddDynamic(this, &UC_TopDownViewMove::RHover);
	//buttonsR->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::LRUnHover);
	//buttonsT = Cast<UButton>(GetWidgetFromName(TEXT("Button_T")));
	//buttonsT->OnHovered.AddDynamic(this, &UC_TopDownViewMove::THover);
	//buttonsT->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::TBUnHover);
	//buttonsB = Cast<UButton>(GetWidgetFromName(TEXT("Button_B")));
	//buttonsB->OnHovered.AddDynamic(this, &UC_TopDownViewMove::BHover);
	//buttonsB->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::TBUnHover);

	buttonsL = Cast<UButton>(GetWidgetFromName(TEXT("Button_L")));
	buttonsL->OnHovered.AddDynamic(this, &UC_TopDownViewMove::Hover);
	buttonsL->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);
	buttonsR = Cast<UButton>(GetWidgetFromName(TEXT("Button_R")));
	buttonsR->OnHovered.AddDynamic(this, &UC_TopDownViewMove::Hover);
	buttonsR->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);
	buttonsT = Cast<UButton>(GetWidgetFromName(TEXT("Button_T")));
	buttonsT->OnHovered.AddDynamic(this, &UC_TopDownViewMove::Hover);
	buttonsT->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);
	buttonsB = Cast<UButton>(GetWidgetFromName(TEXT("Button_B")));
	buttonsB->OnHovered.AddDynamic(this, &UC_TopDownViewMove::Hover);
	buttonsB->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);

	//buttonsLT = Cast<UButton>(GetWidgetFromName(TEXT("Button_LT")));
	//buttonsLT->OnHovered.AddDynamic(this, &UC_TopDownViewMove::LTHover);
	//buttonsLT->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);
	//buttonsLB = Cast<UButton>(GetWidgetFromName(TEXT("Button_LB")));
	//buttonsLB->OnHovered.AddDynamic(this, &UC_TopDownViewMove::LBHover);
	//buttonsLB->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);
	//buttonsRT = Cast<UButton>(GetWidgetFromName(TEXT("Button_RT")));
	//buttonsRT->OnHovered.AddDynamic(this, &UC_TopDownViewMove::RTHover);
	//buttonsRT->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);
	//buttonsRB = Cast<UButton>(GetWidgetFromName(TEXT("Button_RB")));
	//buttonsRB->OnHovered.AddDynamic(this, &UC_TopDownViewMove::RBHover);
	//buttonsRB->OnUnhovered.AddDynamic(this, &UC_TopDownViewMove::UnHover);

}

void UC_TopDownViewMove::LHover()
{
	topDownViewPawn->moveVector.Y = -1.0f;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveL")));

}

void UC_TopDownViewMove::RHover()
{
	topDownViewPawn->moveVector.Y = 1.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveR")));

}

void UC_TopDownViewMove::THover()
{
	topDownViewPawn->moveVector.X = 1.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveT")));

}

void UC_TopDownViewMove::BHover()
{
	topDownViewPawn->moveVector.X = -1.0f;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MoveB")));
}

void UC_TopDownViewMove::LRUnHover()
{
	topDownViewPawn->moveVector.Y = 0.0f;
}

void UC_TopDownViewMove::TBUnHover()
{
	topDownViewPawn->moveVector.X = 0.0f;
}

void UC_TopDownViewMove::LTHover()
{
	topDownViewPawn->moveVector.X =  1.0f;
	topDownViewPawn->moveVector.Y = -1.0f;
}									 
									 
void UC_TopDownViewMove::LBHover()	 
{									 
	topDownViewPawn->moveVector.X = -1.0f;
	topDownViewPawn->moveVector.Y = -1.0f;
}									 
									 
void UC_TopDownViewMove::RTHover()	 
{									 
	topDownViewPawn->moveVector.X =  1.0f;
	topDownViewPawn->moveVector.Y =  1.0f;
}									 
									 
void UC_TopDownViewMove::RBHover()	 
{									 
	topDownViewPawn->moveVector.X = -1.0f;
	topDownViewPawn->moveVector.Y =  1.0f;
}

void UC_TopDownViewMove::Hover()
{
	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize() / 2;
	mousePosition.X -= localViewPortSize.X;
	mousePosition.Y -= localViewPortSize.Y;
	//mousePosition = mousePosition.GetSafeNormal();
	topDownViewPawn->moveVector.X = -mousePosition.Y;
	topDownViewPawn->moveVector.Y = mousePosition.X;
}
									 
void UC_TopDownViewMove::UnHover()	 
{									 
	topDownViewPawn->moveVector.X =  0.0f;
	topDownViewPawn->moveVector.Y =  0.0f;
}
