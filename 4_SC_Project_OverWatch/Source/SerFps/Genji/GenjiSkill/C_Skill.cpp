// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_Skill.h"
#include "Genji/C_CharacterGenji.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AC_Skill::AC_Skill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (HasAuthority())
	{
		//SetReplicates(true); // 경고 뜸
		bReplicates = true;
	}
}

// Called when the game starts or when spawned
void AC_Skill::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<AC_CharacterGenji>(GetOwner());

}

// Called every frame
void AC_Skill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isCoolTime)
	{
		tmpCoolTime += DeltaTime;
		if (tmpCoolTime >= coolTime)
		{
			tmpCoolTime = 0.0f;
			isCoolTime = false;
		}
	}
}

void AC_Skill::UseSkill()
{
	//tmpCoolTime = 0.0f;
}

void AC_Skill::MulPlaySound_Implementation(USoundBase* Sound, FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location, 1.0f, 1.0f, 0.0f, Attenuation);
}

void AC_Skill::MulSpawnEffect_Implementation(UNiagaraSystem* SystemTemplate , FVector SpawnLocation , FRotator SpawnRotation , FVector Scale)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld() , SystemTemplate ,
		SpawnLocation , SpawnRotation , Scale);
}

void AC_Skill::MulPlayMontage_Implementation(UAnimMontage* MontageToPlay, float InPlayRate)
{
	if ( !player ) return;
	UAnimInstance* AnimInstance = player->DefaultMesh->GetAnimInstance();
	if (MontageToPlay && AnimInstance)
		AnimInstance->Montage_Play(MontageToPlay, InPlayRate);

}

