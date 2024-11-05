// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Engine/UserDefinedStruct.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"

//#include "Skill/C_AttackStruct.h"

#include "C_Attack.generated.h"

UENUM(BlueprintType)
enum class AttackInput : uint8
{
    Q, W, E, R, A, S, D,F
};

UENUM(BlueprintType)
enum class AttackType : uint8
{
    SLASH,
    FLOOR,
    PROJECTILE,
    FLOOR_JUMP,
    CHARGING_SLASH,
    CHARGING_PROJECTILE,
    METEOR,
    SPAWN
};
UENUM(BlueprintType)
enum class AttackHitType : uint8
{
    ONE_SHOT,
    DOT_DEAL,
    HEAL,
    MONSTER_ONE_SHOT,
    MONSTER_DOT_DEAL,
    MONSTER_HEAL,
};

UENUM(BlueprintType)
enum class ProjectileType : uint8
{
    PENETRATE,
    NON_PENETRATE,
    BOOM
};

USTRUCT(Atomic, BlueprintType)
struct FAttackBaseC : public FTableRowBase
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackName", MakeStructureDefaultValue = "어택 이름"))
    FName AttackName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SelAttackType", MakeStructureDefaultValue = "SLASH"))
    AttackType SelAttackType;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SelAttackHitType", MakeStructureDefaultValue = "ONE_SHOT"))
    AttackHitType SelAttackHitType;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Damage", MakeStructureDefaultValue = "0"))
    float Damage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Duration", MakeStructureDefaultValue = "0"))
    float Duration;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ColRadius", MakeStructureDefaultValue = "0"))
    float ColRadius;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ColHalfHeight", MakeStructureDefaultValue = "0"))
    float ColHalfHeight;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ColRotation", MakeStructureDefaultValue = "0.0, 0.0, 0.0"))
    FVector ColRotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CoolTime", MakeStructureDefaultValue = "0"))
    float CoolTime;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "HpCost", MakeStructureDefaultValue = "0"))
    float HpCost;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MpCost", MakeStructureDefaultValue = "0"))
    float MpCost;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackDistance", MakeStructureDefaultValue = "100"))
    float AttackDistance;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DotDealInterval", MakeStructureDefaultValue = "0"))
    float DotDealInterval;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackDelay", MakeStructureDefaultValue = "0"))
    float AttackDelay;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "FloorDelay", MakeStructureDefaultValue = "0"))
    float FloorDelay;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SelProjectileType", MakeStructureDefaultValue = "PENETRATE"))
    ProjectileType SelProjectileType;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ProjectileSpeed", MakeStructureDefaultValue = "500"))
    float ProjectileSpeed;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ProjectileBoomName", MakeStructureDefaultValue = "어택 이름"))
    FName ProjectileBoomName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DecalSize", MakeStructureDefaultValue = "100.0, 100.0, 100.0"))
    FVector DecalSize;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DecalMaterial", MakeStructureDefaultValue = "None"))
    TObjectPtr<UMaterialInterface> DecalMaterial;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMesh", MakeStructureDefaultValue = "None"))
    TObjectPtr<UStaticMesh> AttackMesh;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMeshMaterial", MakeStructureDefaultValue = "None"))
    TObjectPtr<UMaterial> AttackMeshMaterial;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMeshLocation", MakeStructureDefaultValue = "0.0,0.0,0.0"))
    FVector AttackMeshLocation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMeshRotation", MakeStructureDefaultValue = "0.0,0.0,0.0"))
    FRotator AttackMeshRotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackMeshScale", MakeStructureDefaultValue = "1.0,1.0,1.0"))
    FVector AttackMeshScale;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackIcon", MakeStructureDefaultValue = "None"))
    TObjectPtr<UTexture2D> AttackIcon;
    UPROPERTY(EditAnywhere, meta = (DisplayName = "AttackEffectNiagara", MakeStructureDefaultValue = "None"))
    TObjectPtr<UNiagaraSystem> AttackEffectNiagara;
    UPROPERTY(EditAnywhere, meta = (DisplayName = "AttackEffectPaticle", MakeStructureDefaultValue = "None"))
    TObjectPtr<UParticleSystem> AttackEffectPaticle;
};

UCLASS()
class STEAMSESSIONS_API AC_Attack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Attack();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UCapsuleComponent* collider;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY()
    UParticleSystemComponent* spawnPaticle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    TSubclassOf<class AC_Attack> BaseAdditiveSkill;

    // 충돌 처리 함수
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // 피해량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Damage;

    // 공격 지속 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Radius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float HalfHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float CoolTime;

    float FloorDelay;
    float AttackDelay;

    float time;

    FVector proT;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    bool isOnCoolDown = false;
    bool isOnDuration = false;
    float tmpDuration;
    bool isOnFloorDelay = false;
    float tmpFloorDelay;
    bool isOnAttackDelay = false;
    float tmpAttackDelay;

    // 프로젝타일용
    FVector worldDicrec;


private:
    FTimerHandle TimerHandle;
public:
    void DestroySlash();
    void OffCollider();

public:
    // 데이터 테이블용
    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //class UDataTable* dataTable;

    FAttackBaseC* attackBase;
    UPROPERTY()
    FAttackBaseC attackBaseU;
    AttackType baseAttackType = AttackType::SLASH;
    AttackHitType baseAttackHitType = AttackHitType::ONE_SHOT;
    ProjectileType baseProjectileType = ProjectileType::NON_PENETRATE;
    void SetAttack(FName attackName);
    void SetAttackBase(FAttackBaseC* _attackBase);
    void SetAttackBaseU(FAttackBaseC _attackBase);
    void SetDestroy();
    void SetActiveOn();

    float DotDealInterval;
    float tmpDotDealInterval;

};
