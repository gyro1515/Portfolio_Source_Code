// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/C_MapPortal.h"
#include "Components/CapsuleComponent.h"
#include "C_TopDownCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "C_SaveTopDown.h"
#include "C_TopDownController.h"
#include "Widget/C_Inventory.h"
#include "C_TopDownGameInstance.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AC_MapPortal::AC_MapPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PortalCollider"));
	collider->OnComponentBeginOverlap.AddDynamic(this, &AC_MapPortal::OverlapBegin);
	//collider->OnComponentEndOverlap.AddDynamic(this, &AC_MapPortal::OverlapEnd);
	RootComponent = collider;

}

// Called when the game starts or when spawned
void AC_MapPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MapPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_MapPortal::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AC_TopDownCharacter* player = Cast<AC_TopDownCharacter>(OtherActor);
		if (player)
		{
			if (NextLevelName != TEXT(""))
			{
				UC_SaveTopDown* saveData = Cast<UC_SaveTopDown>(UGameplayStatics::CreateSaveGameObject(UC_SaveTopDown::StaticClass()));
				AC_TopDownController* tmpCont = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
				saveData->SaveData(tmpCont);
				
				FString levelS = UGameplayStatics::GetCurrentLevelName(GetWorld());
				if (UGameplayStatics::SaveGameToSlot(saveData, *levelS, 0))
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("SaveMap!")));
				}

				// ���� �ν��Ͻ��� ���� �ʳ��� ����, ���� �ʿ��� ������ �ҷ����� �뵵
				UC_TopDownGameInstance* tmpGI = Cast<UC_TopDownGameInstance>(GetWorld()->GetGameInstance());
				tmpGI->lastMapName = levelS;
				tmpGI->CurrentName = NextLevelName.ToString();

				// �ε��� �������� �߰��ϱ�
				//tmpCont->loadingWidget->AddToViewport();
				//FLatentActionInfo LatentInfo;
				//LatentInfo.CallbackTarget = this;
				//LatentInfo.ExecutionFunction = "ChangeLevel";
				//LatentInfo.Linkage = 1;
				//LatentInfo.UUID = 1;
				//UGameplayStatics::LoadStreamLevel(this, NextLevelName, true, true, LatentInfo);

				// UGameplayStatics::OpenLevel(this, NextLevelName);
			}
			// ���߿� 3���� �;߸� �̵��ϰ� �����?
			//player->GetFName();
			//characters.Add(player);
		}
	}
}

void AC_MapPortal::OverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{

	}
}

void AC_MapPortal::ChangeLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChangeLevel!")));
	AC_TopDownController* tmpCont = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
	tmpCont->loadingWidget->RemoveFromParent();

	FString levelS = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::UnloadStreamLevel(this, FName(*levelS), FLatentActionInfo(), false);
	UGameplayStatics::OpenLevel(this, NextLevelName);

}

