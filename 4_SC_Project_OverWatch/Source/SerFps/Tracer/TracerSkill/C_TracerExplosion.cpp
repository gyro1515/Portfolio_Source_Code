// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracer/TracerSkill/C_TracerExplosion.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "CharacterBase/C_BaseCharacter.h"

// Sets default values
AC_TracerExplosion::AC_TracerExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->SetSphereRadius(Radius);
	RootComponent = Collider;
	if ( HasAuthority() )
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this , &AC_TracerExplosion::OnHitBeginOverlap);
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	//NiagaraComponent->SetRelativeScale3D(FVector(0.1f , 0.1f , 0.1f));

}

// Called when the game starts or when spawned
void AC_TracerExplosion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_TracerExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( AttachedActor )
	{
		SetActorLocation(AttachedActor->GetActorLocation() + AttachedLocation*0.5f);
	}

	time += DeltaTime;

	if (count < 3 )
	{
		if ( time < 1.0f )
		{
			float t = FMath::Lerp(ScaleMax*0.5f , 0 , time);
			NiagaraComponent->SetRelativeScale3D(FVector(t , t , t));
		}
		else
		{
			time = 0.0f;
			count++;
		}
	}
	else
	{
		isActive = true;
		float t = FMath::Lerp(0 , ScaleMax, time/Duration);
		NiagaraComponent->SetRelativeScale3D(FVector(t , t , t));

		if ( time > Duration )
		{
			Destroy();
		}
	}

}

void AC_TracerExplosion::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if ( !isActive ) return;

	AC_BaseCharacter* tmpPlayer = Cast<AC_BaseCharacter>(OtherActor);
	if ( tmpPlayer )
	{
		UGameplayStatics::ApplyDamage(tmpPlayer , Damage,nullptr, nullptr, nullptr);
	}
	else
	{
		return;
	}

}

void AC_TracerExplosion::AttachBomb(const FVector& location , AActor* Actor)
{
	AttachedLocation = location;
	AttachedActor = Actor;
}

