// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/C_BaseBullet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBase/C_BaseCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

// Sets default values
AC_BaseBullet::AC_BaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	RootComponent = Collider;
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	if ( HasAuthority() )
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this , &AC_BaseBullet::OnHitBeginOverlap);
		/*SetReplicates(true);
		SetReplicateMovement(true);*/
	}
}

// Called when the game starts or when spawned
void AC_BaseBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_BaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BaseBullet::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if ( OtherActor == this || OtherActor == Owner || OtherActor->Owner == Owner || !HasAuthority() ) return;
	
	TSubclassOf<UDamageType> DamageType;
	AC_BaseCharacter* tmpPlayer = Cast<AC_BaseCharacter>(Owner);
	AC_BaseCharacter* tmpEnemy = Cast<AC_BaseCharacter>(OtherActor);
	if ( tmpPlayer && tmpEnemy )
	{
		float tmpdam = UGameplayStatics::ApplyDamage(tmpEnemy , damage ,
			tmpPlayer->GetController() , this, DamageType);
	}
}

void AC_BaseBullet::MulPlaySound_Implementation(USoundBase* Sound , FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld() , Sound , Location , 1.0f , 1.0f , 0.0f , Attenuation);
}

void AC_BaseBullet::MulSpawnEffect_Implementation(UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld() , SystemTemplate ,
		SpawnLocation , SpawnRotation , Scale);
}

