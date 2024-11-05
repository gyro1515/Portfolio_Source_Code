// Fill out your copyright notice in the Description page of Project Settings.


#include "C_TopDownController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "C_TopDownCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterSelectWidget.h"
#include "Widget/C_Inventory.h"
#include "Widget/C_UI.h"
#include "C_TopDownViewPawn.h"
#include "C_SaveTopDown.h"
#include "Kismet/GameplayStatics.h"
#include "C_TopDownGameInstance.h"


AC_TopDownController::AC_TopDownController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Construter!")));

	
}

void AC_TopDownController::ControlAccess(FString playerName, int playerClass)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Control!")));
	selectW->RemoveFromParent();
	//selectW->RemoveFromViewport();
	//selectW->RemoveFromRoot();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		//tmpString = TEXT("Client");
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	Selection(playerName, playerClass);

	
}

void AC_TopDownController::BeginPlay()
{
	Super::BeginPlay();

	if (this->IsLocalPlayerController()) 
	{
		selectW = Cast<UCharacterSelectWidget>(CreateWidget(this, selectWidgetClass));
	
		if (selectW != nullptr)
		{
			selectW->AddToViewport(10);
		}
	
	}
	//�κ��丮 ����
	if (!InventoryC && InventoryClass)
	{
		InventoryC = Cast<UC_Inventory>(CreateWidget(GetWorld(), InventoryClass));
		if (InventoryC)
		{
			//InventoryC->SetPlayer(selectedCharacter);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), TEXT("InvenSetting!"));
		}
	}
	isInvenOn = false;

	// �ε����� ����
	//if (!loadingWidget && LoadingClass)
	//{
	//	loadingWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), LoadingClass));
	//}

	


	// ĳ���� ����
	UC_SaveTopDown* LoadGameInstance;
	UC_TopDownGameInstance* tmpGI = Cast<UC_TopDownGameInstance>(GetWorld()->GetGameInstance());
	FString levelS = tmpGI->lastMapName;
	FString NextLS = tmpGI->CurrentName;
	LoadGameInstance = Cast<UC_SaveTopDown>(UGameplayStatics::LoadGameFromSlot(*levelS, 0));
	if (LoadGameInstance)
	{
		selectW->ChosenName = LoadGameInstance->charName;
		ControlAccess(selectW->ChosenName, 0);
		PMain_UI->MapCheck = true;
		PMain_UI->RenderT = false;
		SetUpdateUI(NextLS);
	}

	// ���� ����, ������ ���� �� ����
	//FItemBaseC tmpItemB = *(InventoryC->dataTable->FindRow<FItemBaseC>(FName(TEXT("Posion_0")), TEXT("Posion_0")));
	//hpPotion = GetWorld()->SpawnActor<ACItemStrut>(InventoryC->tItem);
	//hpPotion->SetItemU(tmpItemB);
	//tmpItemB = *(InventoryC->dataTable->FindRow<FItemBaseC>(FName(TEXT("Posion_1")), TEXT("Posion_1")));
	//mpPotion = GetWorld()->SpawnActor<ACItemStrut>(InventoryC->tItem);
	//mpPotion->SetItemU(tmpItemB);
	//SetPotion();
}

void AC_TopDownController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (selectedCharacter != nullptr)
	{
		SetUpdateHM();
		if (!PMain_UI->MapCheck)
		{
			PMain_UI->SetMiniPLocation(Tank->GetActorLocation(),
				DPS->GetActorLocation(), Heal->GetActorLocation());
		}
		
		
	}

	if (bIsPotionCoolTime)
	{
		tmpPotionCoolTime += DeltaTime;
		if (tmpPotionCoolTime >= potionCoolTime)
		{
			tmpPotionCoolTime = 0.0f;
			bIsPotionCoolTime = false;
		}
		PMain_UI->SetPotionCoolTime();
		InventoryC->SetCoolTime();
	}
}

void AC_TopDownController::Selection(const FString& playerName, const int& playerClass)
{
	


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnLocation = GetPawn()->GetActorLocation();
	Tank = GetWorld()->SpawnActor<AC_TopDownCharacter>(TankC, FTransform(SpawnLocation), SpawnParams);
	UE_LOG(LogTemp, Warning, TEXT("spawnTank"));
	FString tmp = TEXT("Tank_") + playerName;
	Tank->SetCharacterName(tmp);
	Tank->UpdateHpPercent(Tank->CharacterHp, Tank->CharacterMaxHp);
	selectedCharacter = Tank;
	myCharacters.Add(Tank);

	FVector DPSL = SpawnLocation;
	DPSL.Y += 100;
	DPS = GetWorld()->SpawnActor<AC_TopDownCharacter>(DPSC, FTransform(DPSL), SpawnParams);
	UE_LOG(LogTemp, Warning, TEXT("spawnDPS"));
	tmp = TEXT("DPS_") + playerName;
	DPS->SetCharacterName(tmp);
	DPS->UpdateHpPercent(DPS->CharacterHp, DPS->CharacterMaxHp);
	myCharacters.Add(DPS);
	
	FVector HealL = SpawnLocation;
	HealL.Y -= 100;
	Heal = GetWorld()->SpawnActor<AC_TopDownCharacter>(HealC, FTransform(HealL), SpawnParams);
	UE_LOG(LogTemp, Warning, TEXT("spawnHeal"));
	tmp = TEXT("Heal_") + playerName;
	Heal->SetCharacterName(tmp);
	Heal->UpdateHpPercent(Heal->CharacterHp, Heal->CharacterMaxHp);
	myCharacters.Add(Heal);

	// ���� ���콺 ��� ����
	//FInputModeGameAndUI inputMode;
	//inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	//SetInputMode(inputMode);

	// ������ �ҷ�����
	//UC_SaveTopDown* LoadGameInstance = Cast<UC_SaveTopDown>(UGameplayStatics::CreateSaveGameObject(UC_SaveTopDown::StaticClass()));
	UC_SaveTopDown* LoadGameInstance;
	UC_TopDownGameInstance* tmpGI = Cast<UC_TopDownGameInstance>(GetWorld()->GetGameInstance());
	FString levelS = tmpGI->lastMapName;
	LoadGameInstance = Cast<UC_SaveTopDown>(UGameplayStatics::LoadGameFromSlot(*levelS, 1));
	if (LoadGameInstance)
	{
		LoadGameInstance->LoadData(this);
		Tank->SetActorLocation(SpawnLocation);
		DPS->SetActorLocation(DPSL);
		Heal->SetActorLocation(HealL);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("LoadData!")));

	}


	// ���� ����, ������ ���� �� ����
	FItemBaseC tmpItemB = *(InventoryC->dataTable->FindRow<FItemBaseC>(FName(TEXT("Posion_0")), TEXT("Posion_0")));
	hpPotion = GetWorld()->SpawnActor<ACItemStrut>(InventoryC->tItem);
	hpPotion->SetItemU(tmpItemB);
	tmpItemB = *(InventoryC->dataTable->FindRow<FItemBaseC>(FName(TEXT("Posion_1")), TEXT("Posion_1")));
	mpPotion = GetWorld()->SpawnActor<ACItemStrut>(InventoryC->tItem);
	mpPotion->SetItemU(tmpItemB);
	SetPotion();

	// �ε� �� ���� UI

	if (!PMain_UI && PMain_UIClass)
	{
		PMain_UI = Cast<UC_UI>(CreateWidget(this, PMain_UIClass));

		PMain_UI->AddToViewport();
		PMain_UI->SetPotionCount();
		PMain_UI->SetCharName(Tank->CharacterName, DPS->CharacterName, Heal->CharacterName);
		PMain_UI->MapCheck = true;
		PMain_UI->RenderT = false;
		SetUpdateUI(FString("TopDownMap"));
	}
	SetC_Outline();

}

void AC_TopDownController::CallInven()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("InvenCheck!")));
	if (InventoryC)
	{
		if (isInvenOn)
		{
			InventoryC->OffWidget();
			InventoryC->RemoveFromParent();
			isInvenOn = false;

		}
		else
		{
			InventoryC->SetPlayer(selectedCharacter);
			InventoryC->AddToViewport(1);
			isInvenOn = true;
		}
	}
}

void AC_TopDownController::SetPotion()
{
	hpPotion->ItemCount = 0;
	mpPotion->ItemCount = 0;
	if (InventoryC)
	{
		for (int32 i = 0; i < 20; i++)
		{
			if (InventoryC->items[i])
			{
				if (InventoryC->items[i]->ItemName == hpPotion->ItemName)
				{
					hpPotion->ItemCount += InventoryC->items[i]->ItemCount;
				}
				else if (InventoryC->items[i]->ItemName == mpPotion->ItemName)
				{
					mpPotion->ItemCount += InventoryC->items[i]->ItemCount;
				}
			}
		}
		if (PMain_UI) PMain_UI->SetPotionCount();
	}
}

void AC_TopDownController::SelPotion(const FInputActionValue& value)
{
	FVector selVector = value.Get<FVector>();
	if (selVector.X)
	{
		UsePotion(hpPotion);
	}
	else if (selVector.Y)
	{
		UsePotion(mpPotion);
	}
}

void AC_TopDownController::UsePotion(class ACItemStrut* potion)
{
	if (InventoryC)
	{
		for (int32 i = 0; i < 20; i++)
		{
			if (InventoryC->items[i])
			{
				if (InventoryC->items[i]->ItemName == potion->ItemName)
				{
					InventoryC->UseItemA(InventoryC->items, i);
					PMain_UI->SetPotionCount();
					return;
				}
			}
		}
	}
}

//bool AC_TopDownController::AddInven(ACItemStrut* addItem)
//{
//	TArray<ACItemStrut*>& tmp = InventoryC->items;
//	for (int i = 0; i < tmp.Num(); i++)
//	{
//		if (tmp[i] && tmp[i]->ItemType != ItemType::Equipment && tmp[i]->ItemName == addItem->ItemName)
//		{
//			tmp[i]->ItemCount += addItem->ItemCount;
//			InventoryC->SetInven();
//			addItem->Destroy();
//			return true;
//		}
//	}
//	for (int i = 0; i < tmp.Num(); i++)
//	{
//		if (tmp[i] == nullptr)
//		{
//			tmp[i] = addItem;
//			InventoryC->SetInven();
//			return true;
//		}
//		
//	}
//	return false;
//
//}

void AC_TopDownController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AC_TopDownController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AC_TopDownController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AC_TopDownController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AC_TopDownController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &AC_TopDownController::OnRollStarted);
		
		EnhancedInputComponent->BindAction(CameraRotAction, ETriggerEvent::Triggered, this, &AC_TopDownController::OnCamTriggered);

		//
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &AC_TopDownController::OnMeleeStarted);
		EnhancedInputComponent->BindAction(QSkillAction, ETriggerEvent::Started, this, &AC_TopDownController::OnQStarted);
		EnhancedInputComponent->BindAction(WSkillAction, ETriggerEvent::Started, this, &AC_TopDownController::OnWStarted);
		EnhancedInputComponent->BindAction(ESkillAction, ETriggerEvent::Started, this, &AC_TopDownController::OnEStarted);
		EnhancedInputComponent->BindAction(I_InventoryAction, ETriggerEvent::Started, this, &AC_TopDownController::CallInven);
		EnhancedInputComponent->BindAction(sel1CharacterAction, ETriggerEvent::Started, this, &AC_TopDownController::SelCharacter);
		EnhancedInputComponent->BindAction(sel2CharacterAction, ETriggerEvent::Started, this, &AC_TopDownController::SelCharacter);
		EnhancedInputComponent->BindAction(sel3CharacterAction, ETriggerEvent::Started, this, &AC_TopDownController::SelCharacter);
		EnhancedInputComponent->BindAction(potionAction, ETriggerEvent::Started, this, &AC_TopDownController::SelPotion);

	}
}


void AC_TopDownController::OnInputStarted()
{
	if (bSelAllCharacter)
	{
		Tank->GetController()->StopMovement();
		DPS->GetController()->StopMovement();
		Heal->GetController()->StopMovement();

	}
	else selectedCharacter->GetController()->StopMovement();
}

void AC_TopDownController::OnSetDestinationTriggered()
{
	if (selectedCharacter->canInput) return;
	
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	//APawn* ControlledPawn = GetPawn();
	////APawn* ControlledPawn = GetCharacter();
	//if (ControlledPawn != nullptr)
	//{
	//	//FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	//	//ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	//	AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(GetPawn());
	//	FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	//	tmp->AddMovementInput(WorldDirection, 1.0, false);
	//}
	//FVector WorldDirection = (CachedDestination - selectedCharacter->GetActorLocation()).GetSafeNormal();
	//selectedCharacter->AddMovementInput(WorldDirection, 1.0, false);
	if (bSelAllCharacter)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Tank->GetController(), CachedDestination);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(DPS->GetController(), CachedDestination);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Heal->GetController(), CachedDestination);
	}
	else UAIBlueprintHelperLibrary::SimpleMoveToLocation(selectedCharacter->GetController(), CachedDestination);
	
}

void AC_TopDownController::OnSetDestinationReleased()
{
	if (selectedCharacter->canInput) return;

	// If it was a short press
	//if (FollowTime <= ShortPressThreshold)
	//{
	//	// We move there and spawn some particles
	//	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	//	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Released!")));
	//
	//}
	{
		if (bSelAllCharacter)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Tank->GetController(), CachedDestination);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(DPS->GetController(), CachedDestination);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Heal->GetController(), CachedDestination);
		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(selectedCharacter->GetController(), CachedDestination);
		}
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Released!")));

	}

	FollowTime = 0.f;

}

void AC_TopDownController::OnRollStarted()
{
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(GetCharacter());
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(GetCharacter());

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Roll!")));
	selectedCharacter->RPCRoll();
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(selectedCharacter);
	//if (tmp)
	//{
	//	tmp->RPCRoll();
	//}
}

void AC_TopDownController::OnCamTriggered(const FInputActionValue& value)
{
	//if(IsInputKeyDown(EKeys::LeftMouseButton))
	if(IsInputKeyDown(EKeys::MiddleMouseButton))
	{
		FVector2D lookVector = value.Get<FVector2D>();
		//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(GetPawn());
		FRotator rot = { 0.0f,3.14f*lookVector.X,0.0f};

		//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(selectedCharacter);
		//if (tmp)
		//{
		//	tmp->GetCameraBoom()->AddWorldRotation(rot);
		//
		//}
		selectedCharacter->GetCameraBoom()->AddWorldRotation(rot);
	}
}

void AC_TopDownController::OnMeleeStarted()
{
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(selectedCharacter);
	//if (tmp)
	//{
	//	tmp->RPCAttack(selectedCharacter->MeleeMotion);
	//
	//}
	selectedCharacter->RPCAttack(selectedCharacter->MeleeMotion);
}

void AC_TopDownController::OnQStarted()
{
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(selectedCharacter);
	//if (tmp)
	//{
	//	tmp->UseSkill_Q();
	//
	//}
	
	selectedCharacter->UseSkill_Q();
}

void AC_TopDownController::OnWStarted()
{
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(selectedCharacter);
	//if (tmp)
	//{
	//	tmp->UseSkill_W();
	//
	//}
	selectedCharacter->UseSkill_W();
}

void AC_TopDownController::OnEStarted()
{
	//AC_TopDownCharacter* tmp = Cast<AC_TopDownCharacter>(selectedCharacter);
	//if (tmp)
	//{
	//	tmp->UseSkill_E();
	//
	//}
	selectedCharacter->UseSkill_E();
}

void AC_TopDownController::SelCharacter(const FInputActionValue& value)
{
	FVector selVector = value.Get<FVector>();
	bSelAllCharacter = false;
	if (selVector.X > 0)
	{
		if (selectedCharacter == Tank)
		{
			AC_TopDownViewPawn* tmpPawn = Cast<AC_TopDownViewPawn>(GetPawn());
			tmpPawn->ViewLocation();
			SetC_Outline();
			return;
		}
		selectedCharacter = Tank;
	}
	else if (selVector.Y)
	{
		if (selectedCharacter == DPS) 
		{
			AC_TopDownViewPawn* tmpPawn = Cast<AC_TopDownViewPawn>(GetPawn());
			tmpPawn->ViewLocation();
			SetC_Outline();
			return;
		}
		selectedCharacter = DPS;
	}
	else if (selVector.Z)
	{
		if (selectedCharacter == Heal) 
		{
			AC_TopDownViewPawn* tmpPawn = Cast<AC_TopDownViewPawn>(GetPawn());
			tmpPawn->ViewLocation();
			SetC_Outline();
			return;
		}
		selectedCharacter = Heal;
	}
	else if (selVector.X < 0)
	{
		bSelAllCharacter = true;
	}
	SetUpdateUI();
	SetC_Outline();
}

void AC_TopDownController::SetC_Outline()
{
	//UMaterial* SetOutM = LoadObject<UMaterial>(nullptr, TEXT("/Game/TopDown/TestM/OutLine"));
	
	Tank->GetMesh()->SetOverlayMaterial(nullptr);
	DPS->GetMesh()->SetOverlayMaterial(nullptr);
	Heal->GetMesh()->SetOverlayMaterial(nullptr);


	if (bSelAllCharacter)
	{
		Tank->GetMesh()->SetOverlayMaterial(SetOutM);
		DPS->GetMesh()->SetOverlayMaterial(SetOutM);
		Heal->GetMesh()->SetOverlayMaterial(SetOutM);
	}
	else selectedCharacter->GetMesh()->SetOverlayMaterial(SetOutM);

	




}


void AC_TopDownController::SetUpdateUI(FString levelS)
{


	PMain_UI->SetPlayerUI(selectedCharacter);

	
	
	

	if (PMain_UI->MapCheck && !PMain_UI->RenderT)
	{


		if (levelS == "TopDownMap")
		{
			PMain_UI->MiniMapSize = FVector2D(2800, 3500);
			PMain_UI->MiniMapC_Set = FVector2D(4.0f, 10.0f);
			//PMain_UI->MiniMapC_Set = FVector2D(0.0f, 0.0f);

			//UTexture2D* test = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/TestM/TopdownMini"));

			PMain_UI->SetMiniMapT(test);
			PMain_UI->SetMiniMapSize(FVector2D(256.0f, 209.0f));

		}
		else if (levelS == "BossMap_S")
		{
			PMain_UI->MiniMapSize = FVector2D(7800, 7000);
			PMain_UI->MiniMapC_Set = FVector2D(125, -150);
			//UTexture2D* test2 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/TopDown/TestM/BossMini"));

			PMain_UI->SetMiniMapT(test2);
			PMain_UI->SetMiniMapSize(FVector2D(256.0f, 256.0f));

		}
		else if (levelS == "ForestMap")
		{
			PMain_UI->RenderT = true;
			

		}



		// if (selectedCharacter == Tank)
		// {
		// 	MiniRender = LoadObject<UTexture>(nullptr, TEXT("/Game/TopDown/TestM/MinimapC1"));
		// }
		// else if (selectedCharacter == DPS)
		// {
		// 	MiniRender = LoadObject<UTexture>(nullptr, TEXT("/Game/TopDown/TestM/MinimapC2"));
		// }
		// else if (selectedCharacter == Heal)
		// {
		// 	MiniRender = LoadObject<UTexture>(nullptr, TEXT("/Game/TopDown/TestM/MinimapC3"));
		// }
		// 
		// 
		// UMaterial* testMda = LoadObject<UMaterial>(nullptr, TEXT("/Game/TopDown/TestM/MinimapTest"));
		// testMda->SetTextureParameterValueEditorOnly("PlayerSel", MiniRender);


		
		PMain_UI->MapCheck = false;


	}

	if (PMain_UI->RenderT)
	{
		if (selectedCharacter == Tank)
		{
			//MiniRender = LoadObject<UTexture>(nullptr, TEXT("/Game/TopDown/TestM/MiniMapT1"));
			MiniRender = minimapTank;
		}
		else if (selectedCharacter == DPS)
		{
			//MiniRender = LoadObject<UTexture>(nullptr, TEXT("/Game/TopDown/TestM/MiniMapT2"));
			MiniRender = minimapDPS;
		}
		else if (selectedCharacter == Heal)
		{
			//MiniRender = LoadObject<UTexture>(nullptr, TEXT("/Game/TopDown/TestM/MiniMapT3"));
			MiniRender = minimapHeal;
		}


		//UMaterial* testMda2 = LoadObject<UMaterial>(nullptr, TEXT("/Game/TopDown/TestM/MinimapTest")); // 다 블루프린트로 옮기기
		//testMda2->SetTextureParameterValueEditorOnly("PlayerSel", MiniRender);

		UMaterialInstanceDynamic* MiniM = UMaterialInstanceDynamic::Create(testMda2, this);
		MiniM->SetTextureParameterValue("PlayerSel", MiniRender);

		PMain_UI->SetMiniMapI(MiniM);
		PMain_UI->SetMiniMapSize(FVector2D(256.0f, 256.0f));
		/*if (MiniM)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), TEXT("kkkkkkkkkkkkkkkkkkkkk"));
		}
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), TEXT("sssssssssssssss"));*/
	}

	
}

void AC_TopDownController::SetUpdateHM()
{
	PMain_UI->SetTeamHp(Tank, DPS, Heal);

	PMain_UI->SetMyHp(selectedCharacter);

	PMain_UI->SetCoolTime();

}

