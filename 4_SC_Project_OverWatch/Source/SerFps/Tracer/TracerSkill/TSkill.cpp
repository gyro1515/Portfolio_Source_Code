// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracer/TracerSkill/TSkill.h"
#include "Tracer/C_CharacterTracer.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATSkill::ATSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if ( HasAuthority() )
	{
		SetReplicates(true);
	}

}

// Called when the game starts or when spawned
void ATSkill::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<AC_CharacterTracer>(GetOwner());

}

// Called every frame
void ATSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( isCoolTime )
	{
		tmpCoolTime += DeltaTime;
		if ( tmpCoolTime >= coolTime )
		{
			tmpCoolTime = 0.0f;
			isCoolTime = false;
		}
	}
}

void ATSkill::UseSkill()
{
}

void ATSkill::MulPlayMontage_Implementation(UAnimMontage* MontageToPlay , float InPlayRate)
{
	player->PlayAnimMontage(MontageToPlay,InPlayRate);
}

void ATSkill::MulSpawnEffect_Implementation(UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld() , SystemTemplate ,
	SpawnLocation , SpawnRotation , Scale);
}

void ATSkill::MulPlaySound_Implementation(USoundBase* Sound , FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld() , Sound , Location);
}

