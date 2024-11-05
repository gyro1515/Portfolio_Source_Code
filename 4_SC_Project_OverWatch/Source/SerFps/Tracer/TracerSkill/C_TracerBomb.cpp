// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracer/TracerSkill/C_TracerBomb.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Tracer/TracerSkill/C_TracerExplosion.h"

AC_TracerBomb::AC_TracerBomb()
{
	PrimaryActorTick.bCanEverTick = true;
	if ( HasAuthority() )
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this , &AC_TracerBomb::OnBeginOverlap);
		SetReplicates(true);
		SetReplicateMovement(true);
	}

}

void AC_TracerBomb::BeginPlay()
{
	Super::BeginPlay();

}

void AC_TracerBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_TracerBomb::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , 
	int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if ( OtherActor == this || OtherActor == Owner || OtherActor->Owner == Owner || !HasAuthority() ) return;
	if ( realbomb ) return;

	realbomb = GetWorld()->SpawnActor<AC_TracerExplosion>(tracerbombclass,SweepResult.Location , FRotator::ZeroRotator);

	if ( realbomb )
	{
		//realbomb->AttachBomb(SweepResult.Location - OtherActor->GetActorLocation() , OtherActor);
		realbomb->AttachBomb(GetActorLocation() - OtherActor->GetActorLocation() , OtherActor);
		Destroy();
	}
}

