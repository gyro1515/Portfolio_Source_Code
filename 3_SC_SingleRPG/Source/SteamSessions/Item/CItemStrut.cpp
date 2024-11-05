// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CItemStrut.h"
#include "C_TopDownController.h"
#include "C_TopDownCharacter.h"
#include "Components/ShapeComponent.h"
#include "Widget/C_Inventory.h"

// Sets default values
ACItemStrut::ACItemStrut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACItemStrut::BeginPlay()
{
	Super::BeginPlay();
	
	// 데이터 테스트용
	//TArray<FName> rowNames = dataTable->GetRowNames();
	//FName tmpFN = rowNames[FMath::RandRange(0, rowNames.Num() - 1)];
	//ttets = dataTable->FindRow<FItemBaseC>(tmpFN, tmpFN.ToString());
	tmpStatic = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	tmpSkeletal = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	collider = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
	collider->OnComponentBeginOverlap.AddDynamic(this, &ACItemStrut::OnOverlapBegin);
	collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//if (ttets->SkeletalMesh == nullptr)
	//{
	//	tmpStatic->SetStaticMesh(ttets->StaticMesh);
	//}
	//else
	//{
	//	tmpSkeletal->SetSkeletalMesh(ttets->SkeletalMesh);
	//}
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

// Called every frame
void ACItemStrut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACItemStrut::SetItem(FItemBaseC* tIem)
{
	ttets = tIem;
	//UStaticMeshComponent* tmpStatic = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	//USkeletalMeshComponent* tmpSkeletal = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	ItemName = ttets->ItemName;
	Hp = ttets->Hp;
	Mp = ttets->Mp;
	Attack = ttets->Attack;
	Def = ttets->Def;
	Speed = ttets->Speed;
	SkillAcceleration = ttets->SkillAcceleration;
	ItemType = ttets->ItemType;
	ItemCount = ttets->ItemCount;
	ItemEffect = ttets->ItemEffect;
	SkeletalMesh = ttets->SkeletalMesh;
	StaticMesh = ttets->StaticMesh;
	Icon = ttets->Icon;

	if (ttets->SkeletalMesh == nullptr)
	{
		tmpStatic->SetStaticMesh(ttets->StaticMesh);
		tmpSkeletal->SetSkeletalMesh(nullptr);
	}
	else
	{
		tmpSkeletal->SetSkeletalMesh(ttets->SkeletalMesh);
		tmpStatic->SetStaticMesh(nullptr);
	}
	//SetActorHiddenInGame(false);
	//SetActorEnableCollision(true);
	//SetActorTickEnabled(true);
}

void ACItemStrut::SetItemU(FItemBaseC tIem)
{
	ttetsU = tIem;
	//UStaticMeshComponent* tmpStatic = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	//USkeletalMeshComponent* tmpSkeletal = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	ItemName = ttetsU.ItemName;
	Hp = ttetsU.Hp;
	Mp = ttetsU.Mp;
	Attack = ttetsU.Attack;
	Def = ttetsU.Def;
	Speed = ttetsU.Speed;
	SkillAcceleration = ttetsU.SkillAcceleration;
	ItemType = ttetsU.ItemType;
	ItemCount = ttetsU.ItemCount;
	ItemEffect = ttetsU.ItemEffect;
	SkeletalMesh = ttetsU.SkeletalMesh;
	StaticMesh = ttetsU.StaticMesh;
	Icon = ttetsU.Icon;

	if (ttetsU.SkeletalMesh == nullptr)
	{
		tmpStatic->SetStaticMesh(ttetsU.StaticMesh);
		tmpSkeletal->SetSkeletalMesh(nullptr);
	}
	else
	{
		tmpSkeletal->SetSkeletalMesh(ttetsU.SkeletalMesh);
		tmpStatic->SetStaticMesh(nullptr);
	}
}

void ACItemStrut::UseItem(ACItemStrut* item)
{
	ItemCount -= 1;

	AC_TopDownController* tmpCont = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
	if (Hp)
	{
		tmpCont->selectedCharacter->RecoveryHP(-Hp);
	}
	else if (Mp)
	{
		tmpCont->selectedCharacter->RecoveryMP(-Mp);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ItemCount: %d"), ItemCount));

	if (ItemCount <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::MakeRandomColor(), TEXT("ItemDelete!"));
		Destroy();
		item = nullptr;
	}
	tmpCont->bIsPotionCoolTime = true;
	tmpCont->SetPotion();
}

void ACItemStrut::SetItemActive()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ACItemStrut::DropRandomItem()
{
	TArray<FName> rowNames = dataTable->GetRowNames();
	FName tmpFN = rowNames[FMath::RandRange(0, rowNames.Num() - 1)];
	ttetsU = *(dataTable->FindRow<FItemBaseC>(tmpFN, tmpFN.ToString()));
	SetItemU(ttetsU);
	if (ItemType != ItemType::Equipment)
	{
		ItemCount = FMath::RandRange(1, 5);
	}
	SetItemActive();
}

void ACItemStrut::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AC_TopDownCharacter* Player = Cast<AC_TopDownCharacter>(OtherActor);
		if (Player)
		{
			AC_TopDownController* tmpCont = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
			if (tmpCont->InventoryC->AddInven(this))
			{
				tmpCont->SetPotion();
				SetActorHiddenInGame(true);
				SetActorEnableCollision(false);
				SetActorTickEnabled(false);
			}
		}
	}
}

