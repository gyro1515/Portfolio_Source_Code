// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/UserDefinedStruct.h"
#include "NiagaraSystem.h"
//#include "C_AttackStruct.generated.h"

/**
 * 
 */
class STEAMSESSIONS_API C_AttackStruct
{
public:
	C_AttackStruct();
	~C_AttackStruct();
};
//
//UENUM(BlueprintType)
//enum class AttackType : uint8
//{
//    SLASH,
//    FLOOR,
//    PROJECTILE,
//    FLOOR_JUMP,
//    CHARGING_SLASH,
//    CHARGING_PROJECTILE,
//    METEOR,
//    SPAWN
//};
//UENUM(BlueprintType)
//enum class AttackHitType : uint8
//{
//    ONE_SHOT,
//    DOT_DEAL,
//    HEAL,
//    MONSTER_ONE_SHOT,
//    MONSTER_DOT_DEAL,
//    MONSTER_HEAL,
//};
//
//USTRUCT(Atomic, BlueprintType)
//struct FAttackBaseC : public FTableRowBase
//{
//    GENERATED_BODY()
//public:
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackName", MakeStructureDefaultValue = "어택 이름"))
//    FName AttackName;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SelAttackType", MakeStructureDefaultValue = "SLASH"))
//    AttackType SelAttackType;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SelAttackHitType", MakeStructureDefaultValue = "ONE_SHOT"))
//    AttackHitType SelAttackHitType;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Damage", MakeStructureDefaultValue = "0"))
//    float Damage;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Duration", MakeStructureDefaultValue = "0"))
//    float Duration;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ColRadius", MakeStructureDefaultValue = "0"))
//    float ColRadius;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ColHalfHeight", MakeStructureDefaultValue = "0"))
//    float ColHalfHeight;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CoolTime", MakeStructureDefaultValue = "0"))
//    float CoolTime;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "HpCost", MakeStructureDefaultValue = "0"))
//    float HpCost;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MpCost", MakeStructureDefaultValue = "0"))
//    float MpCost;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DotDealInterval", MakeStructureDefaultValue = "0"))
//    float DotDealInterval;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DecalRadius", MakeStructureDefaultValue = "0"))
//    float DecalRadius;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMesh", MakeStructureDefaultValue = "None"))
//    TObjectPtr<UStaticMesh> AttackMesh;
//    // 메시들은 나중에 없어질 수도?
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMeshMaterial", MakeStructureDefaultValue = "None"))
//    TObjectPtr<UMaterial> AttackMeshMaterial;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMeshScale", MakeStructureDefaultValue = "0.000000,0.000000,0.000000"))
//    FVector AttackMeshScale;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackIcon", MakeStructureDefaultValue = "None"))
//    TObjectPtr<UTexture2D> AttackIcon;
//    UPROPERTY(EditAnywhere, meta = (DisplayName = "AttackEffect", MakeStructureDefaultValue = "None"))
//    TObjectPtr<UNiagaraSystem> AttackEffect;
//
//};