// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Engine/UserDefinedStruct.h"

#include "CItemStrut.generated.h"

UENUM(BlueprintType)
enum class ItemType : uint8
{
	Equipment,
	Consumption,
	Material,
};

/** Please add a struct description */
USTRUCT(Atomic, BlueprintType)
struct FItemBaseC : public FTableRowBase
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemName", MakeStructureDefaultValue = "아이템 이름"))
	FName ItemName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Hp", MakeStructureDefaultValue = "0"))
	int32 Hp;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Mp", MakeStructureDefaultValue = "0"))
	int32 Mp;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Attack", MakeStructureDefaultValue = "0"))
	int32 Attack;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Def", MakeStructureDefaultValue = "0"))
	int32 Def;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Speed", MakeStructureDefaultValue = "0"))
	int32 Speed;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SkillAcceleration", MakeStructureDefaultValue = "0"))
	int32 SkillAcceleration;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemType", MakeStructureDefaultValue = "Equipment"))
	ItemType ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemCount", MakeStructureDefaultValue = "1"))
	int32 ItemCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemEffect", MakeStructureDefaultValue = "아이템 설명"))
	FString ItemEffect;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SkeletalMesh", MakeStructureDefaultValue = "None"))
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "StaticMesh", MakeStructureDefaultValue = "None"))
	TObjectPtr<UStaticMesh> StaticMesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon", MakeStructureDefaultValue = "None"))
	TObjectPtr<UTexture2D> Icon;
	//class UTexture2D* Icon;

};


UCLASS()
class STEAMSESSIONS_API ACItemStrut : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACItemStrut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetItem(FItemBaseC* tIem);
	void SetItemU(FItemBaseC tIem);
	void UseItem(ACItemStrut* item);
	void SetItemActive();
	void DropRandomItem();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* dataTable;

	FItemBaseC* ttets;
	UPROPERTY()
	FItemBaseC ttetsU;

	class UShapeComponent* collider;
	class UStaticMeshComponent* tmpStatic;
	class USkeletalMeshComponent* tmpSkeletal;
	// 아이템 값들
	FName ItemName;
	int32 Hp;
	int32 Mp;
	int32 Attack;
	int32 Def;
	int32 Speed;
	int32 SkillAcceleration;
	ItemType ItemType;
	int32 ItemCount;
	FString ItemEffect;
	TObjectPtr<USkeletalMesh> SkeletalMesh;
	TObjectPtr<UStaticMesh> StaticMesh;
	TObjectPtr<UTexture2D> Icon;

};
