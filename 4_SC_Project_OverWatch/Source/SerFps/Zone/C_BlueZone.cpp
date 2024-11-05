// Fill out your copyright notice in the Description page of Project Settings.
#include "C_BlueZone.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
AC_BlueZone::AC_BlueZone()
{
    RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootSphere"));
    RootSphere->InitSphereRadius(100.0f);
    RootComponent = RootSphere;

    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(RootComponent);
    NiagaraComponent->SetRelativeScale3D(FVector(0.65f, 0.65f, 0.65f));
}

// Called when the game starts or when spawned
void AC_BlueZone::BeginPlay()
{
	Super::BeginPlay();
}
