// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/C_HealPack.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
// 액터들
#include "CharacterBase/C_BaseBullet.h"
#include "CharacterBase/C_BaseCharacter.h"
#include "Genji/C_CharacterGenji.h"

// Sets default values
AC_HealPack::AC_HealPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	Collider->OnComponentBeginOverlap.AddDynamic(this , &AC_HealPack::OnHitBeginOverlap);
	RootComponent = Collider;
	niagaraCom1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect1"));
	niagaraCom1->SetupAttachment(RootComponent);
	niagaraCom2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect2"));
	niagaraCom2->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AC_HealPack::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);
	//niagaraCom2->SetIsReplicated(true);

}

// Called every frame
void AC_HealPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( !bIsCoolTime ) return;
	tmpRespawnTime += DeltaTime;
	if ( tmpRespawnTime >= respawnTime )
	{
		tmpRespawnTime = 0.0f;
		bIsCoolTime = false;
		MulSetHiddenInGame_Ni2(false);

	}
}

void AC_HealPack::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if ( OtherActor == this || !HasAuthority() ) return;

	AC_BaseCharacter* tmpChar = Cast<AC_BaseCharacter>(OtherActor);
	if ( !tmpChar || tmpChar->GetCapsuleComponent() != OtherComp ) return;
	bIsCoolTime = true;
	MulSetHiddenInGame_Ni2(true);
	
	if ( tmpChar->curHp + HealHp >= tmpChar->maxHp )
	{
		tmpChar->curHp = tmpChar->maxHp;
		//GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , TEXT("HealMax"));

	}
	else
	{
		tmpChar->curHp += HealHp;
		//GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , TEXT("Heal"));
	}
	// 우선 겐지만, 트레이서 추가 필요
	AC_CharacterGenji* tmpGenji = Cast<AC_CharacterGenji>(OtherActor);
	tmpGenji->ClientSetCurHp(tmpChar->curHp, tmpChar->maxHp);
	
}

void AC_HealPack::MulSetHiddenInGame_Ni2_Implementation(bool _bHidden)
{
	if ( _bHidden )
	{
		niagaraCom2->SetHiddenInGame(true);
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		niagaraCom2->SetHiddenInGame(false);
		Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

