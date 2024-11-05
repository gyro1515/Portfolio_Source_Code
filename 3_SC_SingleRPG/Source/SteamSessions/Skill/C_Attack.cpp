// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_Attack.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AI/C_AIController.h"
#include "AI/C_BasicMonster.h"
#include "C_TopDownCharacter.h"
#include "AI/C_LOSPillar.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/DecalComponent.h"
#include "NiagaraComponent.h"

//#include "Skill/C_AttackStruct.h"

// Sets default values
AC_Attack::AC_Attack()
{
    PrimaryActorTick.bCanEverTick = true;

    collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    collider->SetCapsuleSize(Radius, HalfHeight);
    collider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    RootComponent = collider;

    // 충돌 이벤트 바인딩
    collider->OnComponentBeginOverlap.AddDynamic(this, &AC_Attack::OnOverlapBegin);
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
    ProjectileMovement->bRotationFollowsVelocity = true;

    Damage = 20.0f; // 기본 피해량 설정
    Duration = 0.5f; // 공격 지속 시간 설정

    //SetActorHiddenInGame(true);
    //SetActorEnableCollision(false);
    //SetActorTickEnabled(false);
}

void AC_Attack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor != Owner)
    {
        // 브레이크를 없애서 몬스터 힐, 플래이어 한방 스킬, 도트 스킬은 몬스터가 히드 되게, 반대는 플레이어가 히트되게
        switch (baseAttackHitType)
        {
        case AttackHitType::MONSTER_HEAL:
        case AttackHitType::ONE_SHOT:
        case AttackHitType::DOT_DEAL:
        {
            AC_BasicMonster* Monster = Cast<AC_BasicMonster>(OtherActor);
            if (Monster)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("MonsterHit")));
                Monster->SerTakeDamage(Damage);
                switch (baseAttackType)
                {
                case AttackType::SLASH:
                case AttackType::CHARGING_SLASH:
                case AttackType::FLOOR:
                case AttackType::FLOOR_JUMP:
                case AttackType::METEOR:
                case AttackType::SPAWN:
                    GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Attack::OffCollider, 0.1, false);
                    break;
                case AttackType::CHARGING_PROJECTILE:
                case AttackType::PROJECTILE:
                    switch (baseProjectileType)
                    {
                    case ProjectileType::BOOM:
                    {
                        //FAttackBaseC* tmpBase;
                        FAttackBaseC tmpBase;
                        AC_TopDownCharacter* tmpChar = Cast<AC_TopDownCharacter>(Owner);
                        if (tmpChar)
                        {
                            //tmpBase = tmpChar->dataTable->FindRow<FAttackBaseC>(attackBase->ProjectileBoomName, attackBase->ProjectileBoomName.ToString());
                            tmpBase = *(tmpChar->dataTable->FindRow<FAttackBaseC>(attackBaseU.ProjectileBoomName, attackBaseU.ProjectileBoomName.ToString()));
                            FActorSpawnParameters SpawnParams;
                            SpawnParams.Owner = Owner;
                            FRotator Rotation = GetActorRotation();
                            if (SweepResult.Location.X == 0.0 && SweepResult.Location.Y == 0.0 && SweepResult.Location.Z == 0.0)
                            {
                                AC_Attack* tmpBoom = GetWorld()->SpawnActor<AC_Attack>(BaseAdditiveSkill, Owner->GetActorLocation() + Owner->GetActorForwardVector() * attackBaseU.AttackDistance, Rotation, SpawnParams);
                                tmpBoom->SetAttackBaseU(tmpBase);
                                tmpBoom->SetActiveOn();
                            }
                            else
                            {
                                AC_Attack* tmpBoom = GetWorld()->SpawnActor<AC_Attack>(BaseAdditiveSkill, SweepResult.Location, Rotation, SpawnParams);
                                tmpBoom->SetAttackBaseU(tmpBase);
                                tmpBoom->SetActiveOn();
                            }
                        }
                    }
                    case ProjectileType::NON_PENETRATE:
                        SetActorHiddenInGame(true);
                        SetActorEnableCollision(false);
                        if (spawnPaticle)
                        {
                            spawnPaticle->DestroyComponent();
                        }
                        break;
                    default:
                        break;
                    }
                    
                    break;
                default:
                    break;
                }
                AC_AIController* tmpC = Cast<AC_AIController>(Monster->GetController());
                if (tmpC)
                {
                    tmpC->ServerIncreaseAggro(Cast<AC_TopDownCharacter>(GetOwner()), Damage);
                }
            }
        }
            break;
        case AttackHitType::HEAL:
        case AttackHitType::MONSTER_ONE_SHOT:
        case AttackHitType::MONSTER_DOT_DEAL:
        {

            if (baseAttackType != AttackType::SPAWN)
            {
                AC_LOSPillar* Pillar = Cast<AC_LOSPillar>(OtherActor);
                if (Pillar)
                {
                    Destroy();
                    Pillar->DestroyPillar();
                }

            }


            AC_TopDownCharacter* Player = Cast<AC_TopDownCharacter>(OtherActor);
            if (Player)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("PlayerHit")));
                Player->TakeDamage(Damage);
                switch (baseAttackType)
                {
                case AttackType::SLASH:
                case AttackType::CHARGING_SLASH:
                case AttackType::FLOOR:
                case AttackType::FLOOR_JUMP:
                case AttackType::METEOR:
                case AttackType::SPAWN:
                    GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Attack::OffCollider, 0.1, false);
                    break;
                case AttackType::CHARGING_PROJECTILE:
                case AttackType::PROJECTILE:
                    switch (baseProjectileType)
                    {
                    case ProjectileType::BOOM:
                    {
                        //FAttackBaseC* tmpBase;
                        FAttackBaseC tmpBase;
                        AC_TopDownCharacter* tmpChar = Cast<AC_TopDownCharacter>(Owner);
                        if (tmpChar)
                        {
                            //tmpBase = tmpChar->dataTable->FindRow<FAttackBaseC>(attackBase->ProjectileBoomName, attackBase->ProjectileBoomName.ToString());
                            tmpBase = *(tmpChar->dataTable->FindRow<FAttackBaseC>(attackBaseU.ProjectileBoomName, attackBaseU.ProjectileBoomName.ToString()));
                            FActorSpawnParameters SpawnParams;
                            SpawnParams.Owner = Owner;
                            FRotator Rotation = GetActorRotation();
                            if (SweepResult.Location.X == 0.0 && SweepResult.Location.Y == 0.0 && SweepResult.Location.Z == 0.0)
                            {
                                AC_Attack* tmpBoom = GetWorld()->SpawnActor<AC_Attack>(BaseAdditiveSkill, Owner->GetActorLocation() + Owner->GetActorForwardVector() * attackBaseU.AttackDistance, Rotation, SpawnParams);
                                tmpBoom->SetAttackBaseU(tmpBase);
                                tmpBoom->SetActiveOn();
                            }
                            else
                            {
                                AC_Attack* tmpBoom = GetWorld()->SpawnActor<AC_Attack>(BaseAdditiveSkill, SweepResult.Location, Rotation, SpawnParams);
                                tmpBoom->SetAttackBaseU(tmpBase);
                                tmpBoom->SetActiveOn();
                            }
                        }
                    }
                    case ProjectileType::NON_PENETRATE:
                        SetActorHiddenInGame(true);
                        SetActorEnableCollision(false);
                        if (spawnPaticle)
                        {
                            spawnPaticle->DestroyComponent();
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
            break;
        default:
            break;
        }

       
    }


}

// Called when the game starts or when spawned
void AC_Attack::BeginPlay()
{
	Super::BeginPlay();
    //GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Attack::DestroySlash, Duration, false);


    //TArray<FName> rowNames = dataTable->GetRowNames();
    //
    //for (int i = 0; i < rowNames.Num(); i++)
    //{
    //    FString tmpF = rowNames[i].ToString();
    //    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), *tmpF);
    //
    //}
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    ProjectileMovement->SetActive(false);
    //ProjectileMovement->bSimulationEnabled = false;

}

// Called every frame
void AC_Attack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    switch (baseAttackType)
    {
    case AttackType::SLASH:
        break;
    case AttackType::FLOOR:
        break;
    case AttackType::PROJECTILE:
        break;
    case AttackType::FLOOR_JUMP:
        break;
    case AttackType::CHARGING_SLASH:
        break;
    case AttackType::CHARGING_PROJECTILE:
        break;
    case AttackType::METEOR:
        break;
    case AttackType::SPAWN:
        break;
    default:
        break;
    }
    
    if (isOnDuration)
    {
        tmpDuration += DeltaTime;
        if (tmpDuration > Duration)
        {
            isOnDuration = false;
            tmpDuration = 0.0f;
            if (Duration >= CoolTime)
            {
                DestroySlash();
            }
            else
            {
                if (spawnPaticle)
                {
                    spawnPaticle->SetHiddenInGame(true);
                    spawnPaticle->DestroyComponent();
                }
                else
                {
                    UNiagaraComponent* tmpNiagara = Cast<UNiagaraComponent>(GetComponentByClass(UNiagaraComponent::StaticClass()));
                    tmpNiagara->SetHiddenInGame(true);
                }
                SetActorHiddenInGame(true);
                SetActorEnableCollision(false);
            }
        }

        if (isOnFloorDelay)
        {
            tmpFloorDelay += DeltaTime;
            if (tmpFloorDelay>= FloorDelay)
            {
                tmpFloorDelay = 0.0f;
                // 딜레이 시간 지났으면 콜라이더 온
                SetActorEnableCollision(true);
                isOnFloorDelay = false;
            }
        }
        else if (isOnAttackDelay)
        {
            tmpAttackDelay += DeltaTime;
            if (tmpAttackDelay >= AttackDelay)
            {
                tmpAttackDelay = 0.0f;
                // 딜레이 시간 지났으면 콜라이더, 메시 온, 프로젝타일이라면 프로젝 타일 온
                SetActorHiddenInGame(false);
                SetActorEnableCollision(true);
                if (baseAttackType == AttackType::PROJECTILE)
                {
                    ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;

                    ProjectileMovement->SetActive(true);
                    ProjectileMovement->bSimulationEnabled = true;
                }
                //if (attackBase->AttackEffectPaticle)// 캐스케이드 파티클이 있으면 파티클도 온
                if (attackBaseU.AttackEffectPaticle)// 캐스케이드 파티클이 있으면 파티클도 온
                {
                    spawnPaticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackBaseU.AttackEffectPaticle, GetTransform());
                    spawnPaticle->SetupAttachment(collider);
                    spawnPaticle->SetWorldRotation(Owner->GetActorRotation());
                }
                isOnAttackDelay = false;
            }
        }
        else
        {
            // 오버랩과 같은 방식, 도트 딜 힐은 콜라이더 계속 껏다 키기
            switch (baseAttackHitType)
            {
            case AttackHitType::ONE_SHOT:
            case AttackHitType::MONSTER_ONE_SHOT:
                break;
            case AttackHitType::DOT_DEAL:
            case AttackHitType::HEAL:
            case AttackHitType::MONSTER_DOT_DEAL:
            case AttackHitType::MONSTER_HEAL:
                tmpDotDealInterval += DeltaTime;
                if (tmpDotDealInterval >= DotDealInterval)
                {
                    tmpDotDealInterval = 0.0f;
                    SetActorEnableCollision(false);
                    SetActorEnableCollision(true);
                    //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), TEXT("Dot!"));

                }
                break;
            default:
                break;
            }
        }
        
    
    }

    if (isOnCoolDown)
    {
        time += DeltaTime;

        if (time > CoolTime)
        {
            time = 0.0f;
            isOnCoolDown = false;
            if (Duration < CoolTime)
            {
                DestroySlash();
            }
        }
    }

    //if (spawnPaticle && baseAttackType != AttackType::SLASH)
    if (spawnPaticle)
    {
        spawnPaticle->SetWorldLocation(GetActorLocation());
        //if (baseAttackType == AttackType::SLASH)
        //{
        //    spawnPaticle->SetWorldRotation(GetActorRotation());
        //}
    }
}

void AC_Attack::DestroySlash()
{
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    if (spawnPaticle)
    {
        //spawnPaticle->SetActive(false);
        spawnPaticle->DestroyComponent();
    }
    Destroy();
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), TEXT("Destroy!"));
}

void AC_Attack::OffCollider()
{
    SetActorEnableCollision(false);
}

void AC_Attack::SetAttack(FName attackName)
{

}

void AC_Attack::SetAttackBase(FAttackBaseC* _attackBase)
{
    attackBase = _attackBase;
    if (attackBase)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(attackBase->AttackName.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), *attackBase->AttackName.ToString());
    }
    else return;

    collider->SetCapsuleSize(attackBase->ColRadius, attackBase->ColHalfHeight);

    Damage = attackBase->Damage;
    Duration = attackBase->Duration;
    if (Duration) isOnDuration = true;
    AttackDelay = attackBase->AttackDelay;
    if (AttackDelay) isOnAttackDelay = true;
    CoolTime = attackBase->CoolTime;
    if (CoolTime) isOnCoolDown = true;

    UStaticMeshComponent* tmpStatic = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
    if (attackBase->AttackMesh && tmpStatic)
    {
        tmpStatic->SetStaticMesh(attackBase->AttackMesh);
        if (attackBase->AttackMeshMaterial)
        {
            tmpStatic->SetMaterial(0, attackBase->AttackMeshMaterial);
        }
        FTransform tmp = tmpStatic->GetRelativeTransform();
        tmp.SetLocation(attackBase->AttackMeshLocation);
        tmp.SetScale3D(attackBase->AttackMeshScale);
        //tmp.SetRotation(attackBase->AttackMeshRotation);
        tmpStatic->SetRelativeTransform(tmp);
        tmpStatic->SetRelativeRotation(attackBase->AttackMeshRotation);

    }

    baseAttackType = attackBase->SelAttackType;
    baseAttackHitType = attackBase->SelAttackHitType;

    switch (baseAttackType)
    {
    case AttackType::SLASH:
        break;
    case AttackType::FLOOR:
        FloorDelay = attackBase->FloorDelay;
        if (FloorDelay) isOnFloorDelay = true;
        //Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
        break;
    case AttackType::PROJECTILE:
    {
        ProjectileMovement->InitialSpeed = attackBase->ProjectileSpeed;
        ProjectileMovement->MaxSpeed = attackBase->ProjectileSpeed;
        baseProjectileType = attackBase->SelProjectileType;
    }
        break;
    case AttackType::FLOOR_JUMP:
        //Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

        break;
    case AttackType::CHARGING_SLASH:
        break;
    case AttackType::CHARGING_PROJECTILE:
        ProjectileMovement->InitialSpeed = attackBase->ProjectileSpeed;
        ProjectileMovement->MaxSpeed = attackBase->ProjectileSpeed;
        break;
    case AttackType::METEOR:
        break;
    case AttackType::SPAWN:
        break;
    default:
        break;
    }
    
    switch (baseAttackHitType)
    {
    case AttackHitType::ONE_SHOT:
    case AttackHitType::MONSTER_ONE_SHOT:

        break;
    case AttackHitType::DOT_DEAL:
    case AttackHitType::HEAL:
    case AttackHitType::MONSTER_DOT_DEAL:
    case AttackHitType::MONSTER_HEAL:
        DotDealInterval = attackBase->DotDealInterval;
        break;
    default:
        break;
    }

    if (baseProjectileType != ProjectileType::BOOM)
    {
        UNiagaraComponent* tmpNiagara = Cast<UNiagaraComponent>(GetComponentByClass(UNiagaraComponent::StaticClass()));
        if (attackBase->AttackEffectNiagara && tmpNiagara)
        {
            tmpNiagara->SetAsset(attackBase->AttackEffectNiagara);
        }
        else if (attackBase->AttackEffectPaticle)
        {
            //tmpPaticle->SetTemplate(attackBase->AttackEffectPaticle);
            //tmpPaticle->SetActive(true);
            //tmpPaticle->RewindEmitterInstances();
            if (!isOnAttackDelay)
            {
                spawnPaticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackBase->AttackEffectPaticle, GetTransform());
                spawnPaticle->SetupAttachment(collider);
                spawnPaticle->SetWorldRotation(Owner->GetActorRotation());
            }

        }
    }
    


    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

void AC_Attack::SetAttackBaseU(FAttackBaseC _attackBase)
{
    attackBaseU = _attackBase;
    if (attackBaseU.AttackName != TEXT(""))
    {
        //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(attackBase->AttackName.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), *attackBaseU.AttackName.ToString());
    }
    else return;

    collider->SetCapsuleSize(attackBaseU.ColRadius, attackBaseU.ColHalfHeight);

    Damage = attackBaseU.Damage;
    Duration = attackBaseU.Duration;
    if (Duration) isOnDuration = true;
    AttackDelay = attackBaseU.AttackDelay;
    if (AttackDelay) isOnAttackDelay = true;
    CoolTime = attackBaseU.CoolTime;
    if (CoolTime) isOnCoolDown = true;

    UStaticMeshComponent* tmpStatic = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
    if (attackBaseU.AttackMesh && tmpStatic)
    {
        tmpStatic->SetStaticMesh(attackBaseU.AttackMesh);
        if (attackBaseU.AttackMeshMaterial)
        {
            tmpStatic->SetMaterial(0, attackBaseU.AttackMeshMaterial);
        }
        FTransform tmp = tmpStatic->GetRelativeTransform();
        tmp.SetLocation(attackBaseU.AttackMeshLocation);
        tmp.SetScale3D(attackBaseU.AttackMeshScale);
        //tmp.SetRotation(attackBase->AttackMeshRotation);
        tmpStatic->SetRelativeTransform(tmp);
        tmpStatic->SetRelativeRotation(attackBaseU.AttackMeshRotation);

    }

    baseAttackType = attackBaseU.SelAttackType;
    baseAttackHitType = attackBaseU.SelAttackHitType;

    switch (baseAttackType)
    {
    case AttackType::SLASH:
        break;
    case AttackType::FLOOR:
        FloorDelay = attackBaseU.FloorDelay;
        if (FloorDelay) isOnFloorDelay = true;
        //Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
        break;
    case AttackType::PROJECTILE:
    {
        ProjectileMovement->InitialSpeed = attackBaseU.ProjectileSpeed;
        ProjectileMovement->MaxSpeed = attackBaseU.ProjectileSpeed;
        baseProjectileType = attackBaseU.SelProjectileType;
    }
    break;
    case AttackType::FLOOR_JUMP:
        //Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

        break;
    case AttackType::CHARGING_SLASH:
        break;
    case AttackType::CHARGING_PROJECTILE:
        ProjectileMovement->InitialSpeed = attackBaseU.ProjectileSpeed;
        ProjectileMovement->MaxSpeed = attackBaseU.ProjectileSpeed;
        break;
    case AttackType::METEOR:
        break;
    case AttackType::SPAWN:
        break;
    default:
        break;
    }

    switch (baseAttackHitType)
    {
    case AttackHitType::ONE_SHOT:
    case AttackHitType::MONSTER_ONE_SHOT:

        break;
    case AttackHitType::DOT_DEAL:
    case AttackHitType::HEAL:
    case AttackHitType::MONSTER_DOT_DEAL:
    case AttackHitType::MONSTER_HEAL:
        DotDealInterval = attackBaseU.DotDealInterval;
        break;
    default:
        break;
    }

    if (baseProjectileType != ProjectileType::BOOM)
    {
        UNiagaraComponent* tmpNiagara = Cast<UNiagaraComponent>(GetComponentByClass(UNiagaraComponent::StaticClass()));
        if (attackBaseU.AttackEffectNiagara && tmpNiagara)
        {
            tmpNiagara->SetAsset(attackBaseU.AttackEffectNiagara);
        }
        else if (attackBaseU.AttackEffectPaticle)
        {
            //tmpPaticle->SetTemplate(attackBase->AttackEffectPaticle);
            //tmpPaticle->SetActive(true);
            //tmpPaticle->RewindEmitterInstances();
            if (!isOnAttackDelay)
            {
                spawnPaticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackBaseU.AttackEffectPaticle, GetTransform());
                spawnPaticle->SetupAttachment(collider);
                spawnPaticle->SetWorldRotation(Owner->GetActorRotation());
            }

        }
    }



    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

void AC_Attack::SetDestroy()
{
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Attack::DestroySlash, Duration, false);
}


void AC_Attack::SetActiveOn()
{
    SetActorTickEnabled(true);
    if (!isOnAttackDelay)
    {
        SetActorHiddenInGame(false);
        if (!isOnFloorDelay)
        {
            SetActorEnableCollision(true);
        }
        if (baseAttackType == AttackType::PROJECTILE)
        {
            ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
            //ProjectileMovement->Velocity = worldDicrec * ProjectileMovement->InitialSpeed;
            ProjectileMovement->SetActive(true);
            ProjectileMovement->bSimulationEnabled = true;

            //if (GetActorForwardVector() == Owner->GetActorForwardVector())
            //{
            //    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Rot X: %f, Y: %f, Z: %f"), GetActorRotation().Roll, GetActorRotation().Pitch, GetActorRotation().Yaw));
            //
            //}
        }
    }

    if (Duration > CoolTime)
    {
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Attack::DestroySlash, Duration, false);
    }
    else
    {
        GetWorldTimerManager().SetTimer(TimerHandle, this, &AC_Attack::DestroySlash, CoolTime, false);
    }
}

