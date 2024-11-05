// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_GenjiSkill_RightClick.h"

// Sets default values
AC_GenjiSkill_RightClick::AC_GenjiSkill_RightClick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_GenjiSkill_RightClick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GenjiSkill_RightClick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_GenjiSkill_RightClick::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
}

void AC_GenjiSkill_RightClick::UseSkill()
{
	if ( isCoolTime ) return;
	isCoolTime = true;
	MulPlayMontage(AttackMotion);
}

