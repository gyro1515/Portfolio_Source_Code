// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_GenjiSkill_Reload.h"
#include "Genji/C_CharacterGenji.h"

// Sets default values
AC_GenjiSkill_Reload::AC_GenjiSkill_Reload()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_GenjiSkill_Reload::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GenjiSkill_Reload::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_GenjiSkill_Reload::UseSkill()
{
	MulPlayMontage(ReloadMotion);

}

void AC_GenjiSkill_Reload::Reload()
{
	if ( !IsValid(player) ) return;
	player->leftPyoChangCount = player->maxPyoChangCount;
	player->ClientSetLeftPyoChang(player->leftPyoChangCount);
}

void AC_GenjiSkill_Reload::SerTestUseSkill_Implementation()
{
	MulPlayMontage(ReloadMotion);

}

