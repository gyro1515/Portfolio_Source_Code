// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "CharacterSelectWidget.h"
#include "C_TopDownController.generated.h"

/**
 * 
 */
class UNiagaraSystem;

UCLASS()
class STEAMSESSIONS_API AC_TopDownController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AC_TopDownController();

	UFUNCTION()
	void ControlAccess(FString playerName = "Player", int playerClass = 0);

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Click Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Roll Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RollAction;

	/** CamRotation Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CameraRotAction;


	/** Lbutton Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MeleeAction;

	/** Q Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QSkillAction;

	/** W Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* WSkillAction;

	/** E Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ESkillAction;

	/** I Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* I_InventoryAction;

	/** 1 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* sel1CharacterAction;

	/** 2 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* sel2CharacterAction;

	/** 3 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* sel3CharacterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* potionAction;

	//WidgetCharacterSelectRPC
	UFUNCTION()
	void Selection(const FString& playerName, const int& playerClass);

	//character classes
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AC_TopDownCharacter> TankC;
	UPROPERTY()
	class AC_TopDownCharacter* Tank;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AC_TopDownCharacter> DPSC;
	UPROPERTY()
	class AC_TopDownCharacter* DPS;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AC_TopDownCharacter> HealC;
	UPROPERTY()
	class AC_TopDownCharacter* Heal;

	TArray<class AC_TopDownCharacter*> myCharacters;
	// �׽�Ʈ�� �÷��̾�
	UPROPERTY()

	class AC_TopDownCharacter* selectedCharacter;

	bool bSelAllCharacter = false;

	// �κ��丮
	UPROPERTY(EditAnywhere, Category = "Inven")
	TSubclassOf<UUserWidget> InventoryClass;

	UPROPERTY(VisibleAnywhere, Category = "Inven")
	class UC_Inventory* InventoryC;

	bool isInvenOn;

	UFUNCTION(BlueprintCallable)
	void CallInven();

	// ����
	class ACItemStrut* hpPotion;
	class ACItemStrut* mpPotion;

	bool bIsPotionCoolTime = false;
	float potionCoolTime = 2.5f;
	float tmpPotionCoolTime = 0.0f;

	UFUNCTION()
	void SetPotion();

	UFUNCTION()
	void SelPotion(const FInputActionValue& value);

	UFUNCTION()
	void UsePotion(class ACItemStrut* potion);

	// �ε� ����
	UPROPERTY(EditAnywhere, Category = "Loading")
	TSubclassOf<UUserWidget> LoadingClass;

	UPROPERTY(VisibleAnywhere, Category = "Loading")
	class UUserWidget* loadingWidget;

	// // player UI
	UPROPERTY(VisibleAnywhere)
	class UC_UI* PMain_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PMain_UIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
	UTexture2D* test;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
	UTexture2D* test2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
	UMaterial* testMda2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
	UTexture* minimapTank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
	UTexture* minimapDPS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MiniMap")
	UTexture* minimapHeal;

	UTexture* MiniRender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OutLine")
	UMaterial* SetOutM;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	UFUNCTION()
	void OnRollStarted();
	void OnCamTriggered(const FInputActionValue& value);

	void OnMeleeStarted();
	void OnQStarted();
	void OnWStarted();
	void OnEStarted();

	void SelCharacter(const FInputActionValue& value);
	void SetC_Outline();

	// UI

	void SetUpdateUI(FString levelS = "");
	void SetUpdateHM();


private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	
	FVector SpawnLocation = { 1000.0f,1810.0f,92.0f };
	

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UCharacterSelectWidget> selectWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	UCharacterSelectWidget* selectW;

	FString tmpString;

	AC_TopDownController* tmpCont;

};
