// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_TopDownViewMove.generated.h"

/**
 * 
 */
UCLASS()
class STEAMSESSIONS_API UC_TopDownViewMove : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

public:
	void SetTopDownViewPawn(class AC_TopDownViewPawn* _topDownViewPawn) { topDownViewPawn = _topDownViewPawn; }

public:
	UFUNCTION()
	void LHover();
	UFUNCTION()
	void RHover();
	UFUNCTION()
	void THover();
	UFUNCTION()
	void BHover();
	UFUNCTION()
	void LRUnHover();
	UFUNCTION()
	void TBUnHover();
	UFUNCTION()
	void LTHover();
	UFUNCTION()
	void LBHover();
	UFUNCTION()
	void RTHover();
	UFUNCTION()
	void RBHover();
	UFUNCTION()
	void Hover();
	UFUNCTION()
	void UnHover();
public:
	UPROPERTY(EditAnywhere)
	class UButton* buttonsL;
	UPROPERTY(EditAnywhere)
	class UButton* buttonsR;
	UPROPERTY(EditAnywhere)
	class UButton* buttonsT;
	UPROPERTY(EditAnywhere)
	class UButton* buttonsB;

	UPROPERTY(EditAnywhere)
	class UButton* buttonsLT;
	UPROPERTY(EditAnywhere)
	class UButton* buttonsLB;
	UPROPERTY(EditAnywhere)
	class UButton* buttonsRT;
	UPROPERTY(EditAnywhere)
	class UButton* buttonsRB;

	class AC_TopDownViewPawn* topDownViewPawn;

};
