// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_LOSPillar.h"

// Sets default values
AC_LOSPillar::AC_LOSPillar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_LOSPillar::BeginPlay()
{
	Super::BeginPlay();
	curLocation = GetActorLocation();
	startLocation = GetActorLocation();
	curLocation.Z += curHeight;
	SetActorLocation(curLocation);

}

// Called every frame
void AC_LOSPillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (curLocation.Z > startLocation.Z + MaxHeight) return;
	curLocation.Z += Speed * DeltaTime;
	SetActorLocation(curLocation);
}

void AC_LOSPillar::DestroyPillar()
{
	Destroy();
}

