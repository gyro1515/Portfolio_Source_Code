// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/C_Inventory.h"
#include "Blueprint/UserWidget.h"
#include "Input/Reply.h"

#include "Widget/C_InventoryButton.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/C_InventoryOnMouseIcon.h"
#include "Widget/C_InventoryButtonHovered.h"
#include "Components/CanvasPanel.h"
#include "Engine/Canvas.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "C_TopDownController.h"
#include "C_TopDownCharacter.h"
#include "Materials/Material.h"

void UC_Inventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 아이템 세팅, 인벤토리에 넣기
	items.SetNum(20);
	TArray<FName> rowNames = dataTable->GetRowNames();

	for (int i = 0; i < 20; i++)
	{
		// 아이템 세팅, 10개만
		if (i % 2 == 0)
		{
			FName tmpFN = rowNames[FMath::RandRange(0, rowNames.Num() - 1)];
			FItemBaseC tmpIB = *(dataTable->FindRow<FItemBaseC>(tmpFN, tmpFN.ToString()));

			// 액터 소환 후 인벤토리에 저장
			FActorSpawnParameters actorParam;
			//actorParam.Owner = player;
			actorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			items[i] = GetWorld()->SpawnActor<ACItemStrut>(tItem, actorParam);
			items[i]->SetItemU(tmpIB);
		}
		else
		{
			items[i] = nullptr;
		}

		// 버튼
		FString tmpS = "Button_" + FString::FromInt(i);
		UC_InventoryButton* tmpB = Cast<UC_InventoryButton>(GetWidgetFromName(FName(tmpS)));

		if (tmpB)
		{
			tmpB->myNum = i;
			tmpB->SetInven(this);
		}
		buttons.Add(tmpB);

		// 아이콘 이미지, 테스트로 아이템 랜덤으로 넣어주기, 세팅은 마지막에
		tmpS = "ItemIcon_" + FString::FromInt(i);
		UImage* tmpI = Cast<UImage>(GetWidgetFromName(FName(tmpS)));
		//FName tmpFN = rowNames[FMath::RandRange(0, rowNames.Num() - 1)];
		itemIcons.Add(tmpI);

		// 아이템 개수
		tmpS = "TextBlock_" + FString::FromInt(i);
		UTextBlock* tmpTB = Cast<UTextBlock>(GetWidgetFromName(FName(tmpS)));
		itemCount.Add(tmpTB);
	}
	// 인벤토리 세팅
	SetInven();


	//인벤토리 이동용 버튼
	moveButtonC = Cast<UButton>(GetWidgetFromName(TEXT("MoveButton")));
	if (moveButtonC)
	{
		moveButtonC->OnPressed.AddDynamic(this, &UC_Inventory::MoveInven);
		moveButtonC->OnReleased.AddDynamic(this, &UC_Inventory::StopInven);

	}
	canMoveInven = false;

	// 마우스 클릭시 아이템 초기화, 처음에는 없음
	onMouseItem = nullptr;
	tmpInvenNum = 0;
	// 마우스 호버시 아이템 초기화,
	onHoveredItem = nullptr;
	isHovered = false;
	tmpHoveredNum = 0;

	onMouseIconWidget = Cast<UC_InventoryOnMouseIcon>(CreateWidget(GetWorld(), onMouseIconClass));
	
	onHoveredWidget = Cast<UC_InventoryButtonHovered>(CreateWidget(GetWorld(), onHoveredIconClass));
	if (onMouseIconWidget && onHoveredWidget && moveButtonC)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), TEXT("Inventory!!!!!!!!!!!!!!!!!!!"));
	}

	mainController = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
}

void UC_Inventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (onMouseItem)
	{
		FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		mousePosition.X += 50;
		mousePosition.Y += 0;
		onMouseIconWidget->SetRenderTransform(FWidgetTransform(mousePosition, FVector2D(1, 1), FVector2D(0, 0), 0.0f));
		//FVector2D tmpP = onMouseIconWidget->GetRenderTransform().Translation;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("OnMouse Postion.X: %f, Y: %f"), tmpP.X, tmpP.Y));
	}
	else if (canMoveInven) // 마우스거 가지고 있는 아이템이 없을때만 인벤토리 이동가능하게
	{
		UCanvasPanel* moveCavas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("InvenBox")));
		if (moveCavas)
		{
			// ********** 뷰포트 기준 마우스 위치(로컬)와 실제 마우스 위치(절대)는 다름, 위젯은 로컬이 기준, 
			FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
			FVector2D localViewPortSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize() / 2;
			mousePosition.X -= localViewPortSize.X;
			mousePosition.Y -= localViewPortSize.Y;

			FVector2D tmpDesiredSize = GetDesiredSize() / 2;

			mousePosition += tmpMousePos;
			mousePosition.X = FMath::Clamp(mousePosition.X, -localViewPortSize.X + tmpDesiredSize.X, localViewPortSize.X - tmpDesiredSize.X);
			mousePosition.Y = FMath::Clamp(mousePosition.Y, -localViewPortSize.Y + tmpDesiredSize.Y, localViewPortSize.Y - tmpDesiredSize.Y);

			moveCavas->SetRenderTransform(FWidgetTransform(mousePosition, FVector2D(1, 1), FVector2D(0, 0), 0.0f));
		}
	}
	if (isHovered)
	{
		UCanvasPanel* moveCavas = Cast<UCanvasPanel>(onHoveredWidget->GetWidgetFromName(TEXT("HoveredItem")));
		if (moveCavas)
		{
			FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

			FVector2D ttt = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize() / 2;

			mousePosition.X -= ttt.X;
			mousePosition.Y -= ttt.Y;
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("M-X: %f, Y: %f"), mousePosition.X, mousePosition.Y));

			FVector2D tmpDesiredSize = onHoveredWidget->GetDesiredSize();

			if (mousePosition.X + tmpDesiredSize.X + 20.0f > ttt.X)
			{
				mousePosition.X -= tmpDesiredSize.X / 2 + 20.0f;
			}
			else
			{
				mousePosition.X += tmpDesiredSize.X / 2 + 20.0f;
			}

			mousePosition.Y += tmpDesiredSize.Y / 2;
			mousePosition.Y = FMath::Clamp(mousePosition.Y, -ttt.Y + tmpDesiredSize.Y / 2,
				ttt.Y - tmpDesiredSize.Y / 2);

			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("H-X: %f, Y: %f"), mousePosition.X, mousePosition.Y));
			moveCavas->SetRenderTransform(FWidgetTransform(mousePosition, FVector2D(1, 1), FVector2D(0, 0), 0.0f));
		}
	}
	// 더블 클릭 가능 시간
	if (bcanDoubleClick)
	{
		doubleClickTime += InDeltaTime;
		if (doubleClickTime >= 0.2f) // 초과시 더블 클릭 안됨
		{
			bcanDoubleClick = false;
			doubleClickTime = 0.0f;
		}
	}
}

FReply UC_Inventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply tmp;
	tmp.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	//if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		if (onMouseItem)
		{
			AC_TopDownCharacter* tmpChar = Cast<AC_TopDownCharacter>(player);
			if (tmpChar)
			{
				FVector tmpLocation = tmpChar->GetActorLocation();
				FRotator tmpRotation = tmpChar->GetActorRotation();
				FVector tmpFront = tmpChar->GetActorForwardVector();
				tmpLocation += tmpFront * 300;
				//tmpLocation.X += FMath::RandRange(-100.0, 100.0);
				//tmpLocation.Y += FMath::RandRange(-100.0, 100.0);
				FVector tmpRandV = FMath::VRand();
				tmpRandV.Z = 0;
				tmpLocation += tmpRandV.GetSafeNormal() * FMath::RandRange(0.0, 100.0);
	
				//onMouseItem->SetActorLocation(tmpLocation);
				//onMouseItem->SetActorRotation(tmpRotation);
				//onMouseItem->SetItemActive();

				// 위 형식 안돼서(이유 모름) 다시 소환하기
				FActorSpawnParameters actorParam;
				actorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				ACItemStrut* tmpItem = GetWorld()->SpawnActor<ACItemStrut>(tItem, tmpLocation, tmpRotation, actorParam);
				tmpItem->SetItemU(onMouseItem->ttetsU);
				tmpItem->ItemCount = onMouseItem->ItemCount;
				tmpItem->SetItemActive();

				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), TEXT("Drop!"));
				
				if (onMouseItem)
				{
					onMouseItem->Destroy();
					onMouseItem = nullptr;

				}
				onMouseIconWidget->RemoveFromParent();
				

			}
		}
	}
	return tmp.NativeReply;
}

void UC_Inventory::MouseClick(int32 buttonNum)
{
	if (items[buttonNum]) // 클릭시 해당 인벤토리 칸에 아이템이 있을 시
	{
		FString tmpF = FString::Printf(TEXT("ButtonClick : %d = "), buttonNum) + items[buttonNum]->ItemName.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), tmpF);

		// 현재 마우스에 아이템이 있는지
		if (onMouseItem)
		{
			//if (items[buttonNum]->ItemType == ItemType::Consumption && onMouseItem->ItemType == ItemType::Consumption)
			if (items[buttonNum]->ItemType != ItemType::Equipment && items[buttonNum]->ItemType == onMouseItem->ItemType && items[buttonNum]->ItemName == onMouseItem->ItemName)
			{
				items[buttonNum]->ItemCount += onMouseItem->ItemCount;
				onMouseItem->Destroy();
				onMouseItem = nullptr;
				SetInven();
				onMouseIconWidget->RemoveFromParent();
			}
			else
			{
				ACItemStrut* tmp = items[buttonNum];
				items[buttonNum] = onMouseItem;
				items[tmpInvenNum] = tmp;
				onMouseItem = nullptr;
				SetInven();
				onMouseIconWidget->RemoveFromParent();
			}
		}
		else
		{
			onMouseItem = items[buttonNum];
			items[buttonNum] = nullptr;
			tmpInvenNum = buttonNum;
			SetInven();
			onMouseIconWidget->SetIcon(onMouseItem->Icon);
			onMouseIconWidget->SetDesiredSizeInViewport(FVector2D(100, 100));
			onMouseIconWidget->AddToViewport(2);

			// 더블 클릭 가능으로 체인지
			bcanDoubleClick = true;
		}
	}
	else  // 클릭시 해당 인벤토리 칸에 아이템이 없을 시
	{
		FString tmpF = FString::Printf(TEXT("ButtonClick : %d = "), buttonNum) + "empty";
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), tmpF);
		// 현재 마우스에 아이템이 있는지
		if (onMouseItem)
		{
			items[buttonNum] = onMouseItem;
			onMouseItem = nullptr;
			SetInven();
			onMouseIconWidget->RemoveFromParent();

			
			if (tmpInvenNum == buttonNum && items[buttonNum]->ItemType == ItemType::Consumption && bcanDoubleClick) // 더블 클릭시
			{
				//UseItem(items[buttonNum]);
				UseItemA(items, buttonNum);
			}
		}
	}
}

void UC_Inventory::MouseHovered(int32 buttonNum)
{
	if (items[buttonNum])
	{

		ACItemStrut* tmpItem = items[buttonNum];
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("hoverName %s"), *tmpItem->ItemName.ToString()));
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("hoverNameTT %s"), *items[buttonNum]->ttetsU.ItemName.ToString()));

		onHoveredWidget->SetHoveredItemWidget(items[buttonNum]->ttetsU);
		isHovered = true;

		tmpHoveredNum = buttonNum;
		if (onHoveredWidget->IsInViewport())
		{
			onHoveredWidget->RemoveFromParent();
			onHoveredWidget->AddToViewport(3);
		}
		else
		{
			onHoveredWidget->AddToViewport(3);
		}
	}
}

void UC_Inventory::MouseUnHovered(int32 buttonNum)
{
	if (onHoveredWidget->IsInViewport())
	{
		onHoveredWidget->RemoveFromParent();
		isHovered = false;
	}
}

void UC_Inventory::OffWidget()
{
	if (onHoveredWidget->IsInViewport())
	{
		onHoveredWidget->RemoveFromParent();
		isHovered = false;
	}
	if (onMouseIconWidget->IsInViewport())
	{
		items[tmpInvenNum] = onMouseItem;
		onMouseItem = nullptr;
		onMouseIconWidget->RemoveFromParent();
		SetInven();
	}
}

void UC_Inventory::MoveInven()
{
	canMoveInven = true;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), TEXT("MoveInvenOn!"));

	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D ttt = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize() / 2;
	mousePosition.X -= ttt.X;
	mousePosition.Y -= ttt.Y;
	UCanvasPanel* moveCavas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("InvenBox")));
	tmpMousePos = moveCavas->GetRenderTransform().Translation - mousePosition;
}

void UC_Inventory::StopInven()
{
	canMoveInven = false;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), TEXT("MoveInvenOff!"));
}

void UC_Inventory::SetInven()
{
	for (int32 i = 0; i < 20; i++)
	{
		if (items[i] != nullptr)
		{
			itemIcons[i]->SetBrushFromTexture(items[i]->Icon);
			
			switch (items[i]->ItemType)
			{
			case ItemType::Equipment:
				itemCount[i]->SetText(FText::FromString(TEXT("")));
				break;
			case ItemType::Consumption:
			{
				//UMaterial* testMda = LoadObject<UMaterial>(nullptr, TEXT("/Game/TopDown/TestM/testMDa"));
				UMaterialInstanceDynamic* DynamicMaterial1 = UMaterialInstanceDynamic::Create(testMda, this);
				DynamicMaterial1->SetTextureParameterValue("SetImageDa", items[i]->Icon);

				itemIcons[i]->SetBrushFromMaterial(DynamicMaterial1);
			}
			case ItemType::Material:
				itemCount[i]->SetText(FText::FromString(FString::FromInt((items[i]->ItemCount))));
				break;
			default:
				break;
			}
			FLinearColor tmpCol;
			tmpCol.R = 1.0;
			tmpCol.G = 1.0;
			tmpCol.B = 1.0;
			tmpCol.A = 1.0;
			itemIcons[i]->SetColorAndOpacity(tmpCol);
		}
		else
		{
			itemIcons[i]->SetBrushFromTexture(nullptr);
			FLinearColor tmpCol;
			tmpCol.R = 0;
			tmpCol.G = 0;
			tmpCol.B = 0;
			tmpCol.A = 0.3;
			itemIcons[i]->SetColorAndOpacity(tmpCol);
			itemCount[i]->SetText(FText::FromString(TEXT("")));

		}
	}
}

void UC_Inventory::SetCoolTime()
{
	if (mainController->bIsPotionCoolTime)
	{
		for (int32 i = 0; i < 20; i++)
		{
			if (items[i])
				if (items[i]->ItemType == ItemType::Consumption)
				{
					itemIcons[i]->GetDynamicMaterial()->SetScalarParameterValue("CoolTime",
						mainController->tmpPotionCoolTime / mainController->potionCoolTime);
				}
		}
	}
	else
	{
		for (int32 i = 0; i < 20; i++)
		{
			if (items[i])
				if (items[i]->ItemType == ItemType::Consumption)
				{
					itemIcons[i]->GetDynamicMaterial()->SetScalarParameterValue("CoolTime", 1);
				}
		}
	}
	
}

void UC_Inventory::SetPlayer(ACharacter* _player)
{
	player = _player;

}

void UC_Inventory::UseItemA(TArray<ACItemStrut*>& _items, int32 num)
{
	if (mainController->bIsPotionCoolTime) return;
	
	_items[num]->UseItem(_items[num]);
	if (_items[num] && _items[num]->ItemCount <= 0)
	{
		_items[num] = nullptr;
	}
	SetInven();
}

bool UC_Inventory::AddInven(ACItemStrut* addItem)
{
	for (int i = 0; i < items.Num(); i++)
	{
		if (items[i] && items[i]->ItemType != ItemType::Equipment && items[i]->ItemName == addItem->ItemName)
		{
			items[i]->ItemCount += addItem->ItemCount;
			SetInven();
			addItem->Destroy();
			return true;
		}
	}
	for (int i = 0; i < items.Num(); i++)
	{
		if (items[i] == nullptr)
		{
			items[i] = addItem;
			SetInven();
			return true;
		}

	}
	return false;
}

void UC_Inventory::SetReadyLoad()
{
	for (int32 i = 0; i < 20; i++)
	{
		FActorSpawnParameters actorParam;
		actorParam.Owner = player;
		actorParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		items[i] = GetWorld()->SpawnActor<ACItemStrut>(tItem, actorParam);
	}
}
