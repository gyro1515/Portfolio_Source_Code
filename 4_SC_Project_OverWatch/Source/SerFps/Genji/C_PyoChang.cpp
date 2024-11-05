// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/C_PyoChang.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Genji/GenjiSkill/C_GenjiSkill_LeftClick.h"
#include "Genji/C_CharacterGenji.h"
#include "Camera/CameraComponent.h"
#include "Zone/C_RealZone.h"
#include "Zone/C_BlueZone.h"

// 나이아가라
//#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
//#include "NiagaraSystem.h"
// 오디오
#include "Components/AudioComponent.h"

// Sets default values
AC_PyoChang::AC_PyoChang()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
	niagaraCom->SetupAttachment(RootComponent);
	Collider->OnComponentBeginOverlap.AddDynamic(this , &AC_PyoChang::OnBeginOverlapPyoChang);
	Collider->OnComponentHit.AddDynamic(this , &AC_PyoChang::OnHitPyoChang);

	DefaultMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DefaultMesh"));
	DefaultMesh->SetupAttachment(RootComponent);
	pyoAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PyoAudio"));
	pyoAudio->SetupAttachment(DefaultMesh);

	/*SetReplicates(true);
	SetReplicateMovement(true);*/
	Inactive();
}

// Called when the game starts or when spawned
void AC_PyoChang::BeginPlay()
{
	Super::BeginPlay();
	//niagaraCom->SetActive(false , true);
	player = Cast<AC_CharacterGenji>(GetOwner());
	if ( player && player->HasAuthority() )
	{
		//Collider->OnComponentBeginOverlap.AddDynamic(this, &AC_PyoChang::OnHitBeginOverlap);
		Collider->OnComponentBeginOverlap.AddDynamic(player->skillLeftClick, &AC_GenjiSkill_LeftClick::OnHitBeginOverlap);
		
	}
	pyoAudio->AttachToComponent(DefaultMesh , FAttachmentTransformRules::SnapToTargetIncludingScale , TEXT("00000000DA9E_Skeleton"));
	
	totalDistance = duration * Projectile->InitialSpeed;
	
}

// Called every frame
void AC_PyoChang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	tmpDuration += DeltaTime;
	if ( tmpDuration >= duration )
	{
		Destroy();
		return;
	}
	AddActorLocalRotation(FRotator(0.0f, 80.0f, 0.0f));
	
	if ( !bIsDestroy ) return;
	tmpDesTime += DeltaTime;
	if ( tmpDesTime >= 2.0f )
	{
		Destroy();
		
	}
}

void AC_PyoChang::OnBeginOverlapPyoChang(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ( OtherActor == this ||  (player && OtherActor->Owner == player)  || ( player && OtherActor == player)  ) return;

	AC_PyoChang* tmpPyo = Cast<AC_PyoChang>(OtherActor);
	if ( tmpPyo ) return;
	AC_RealZone* tmpZone = Cast<AC_RealZone>(OtherActor);
	if ( tmpZone ) return;
	AC_BlueZone* tmpRZone = Cast<AC_BlueZone>(OtherActor);
	if ( tmpRZone ) return;

	
	/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: PyoChangHit") , *GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 5.0f);*/
	if ( player && player->HasAuthority() )
	{
		player->skillLeftClick->MulPlaySound(player->skillLeftClick->HitSound , SweepResult.Location);
		/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: PyoChang") , *GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 10.0f);*/
		//MulSetActive(false , FVector());
	}
	
	///////////////// 아래 원본
	SetActive(false);
	bIsDestroy = true;
}

void AC_PyoChang::OnHitPyoChang(UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit)
{
	
	if ( OtherActor == this || ( player && OtherActor->Owner == player ) || ( player && OtherActor == player ) ) return;
	/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: Finish") , *GetActorNameOrLabel())
		, true , true , FColor::MakeRandomColor() , 10.0f);*/
	AC_PyoChang* tmpPyo = Cast<AC_PyoChang>(OtherActor);
	if ( tmpPyo ) return;
	AC_RealZone* tmpZone = Cast<AC_RealZone>(OtherActor);
	if ( tmpZone ) return;
	AC_BlueZone* tmpRZone = Cast<AC_BlueZone>(OtherActor);
	if ( tmpRZone ) return;
	if ( player && player->HasAuthority() )
	{
		player->skillLeftClick->MulPlaySound(player->skillLeftClick->HitSound , Hit.Location);
		/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: PyoChangHit") , *GetActorNameOrLabel())
				, true , true , FColor::MakeRandomColor() , 10.0f);*/
		//MulSetActive(false, FVector());
	}
	

	///////////////// 아래 원본
	SetActive(false);
	bIsDestroy = true;
	
}

void AC_PyoChang::FirePyoChang(const FVector& Direction)
{
	bObjectActive = true;

	Projectile->Velocity = Direction * Projectile->InitialSpeed;
	/*Projectile->bSimulationEnabled = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	UKismetSystemLibrary::K2_SetTimer(this, "Inactive", duration, false);*/
	SetActive(true);
	/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: Bullet") , *GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 10.0f);*/
}

void AC_PyoChang::SerFirePyoChang_Implementation(const FVector& Direction)
{
	bObjectActive = true;

	MulSetActive(true, Direction);
}

void AC_PyoChang::FirePyoChangQuick()
{
	if ( !player ) return;
	
	SetActorLocation(player->GetActorLocation() + player->GetActorForwardVector() * 100.0f);
	SetActorRotation(player->GetControlRotation());

	// 카메라와 발사위치까지의 거리 구하기
	FVector CamPos = player->Camera->GetComponentLocation();
	FVector AcPos = player->GetActorLocation() + player->GetActorForwardVector() * 100.0f;
	FVector tmpV = AcPos - CamPos;

	float tmpDistance = ( FVector::DotProduct(tmpV , player->Camera->GetForwardVector()) );
	FHitResult tmpHit;
	FVector start = player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * tmpDistance;
	FVector end = player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * 10000.0f;
	GetWorld()->LineTraceSingleByChannel(tmpHit, start, end, ECollisionChannel::ECC_Camera);
	FVector direction;
	FCollisionQueryParams tmpCP;
	tmpCP.AddIgnoredActor(player);
	GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera , tmpCP);
	if (tmpHit.bBlockingHit)
	{
		direction = (tmpHit.Location - GetActorLocation()).GetSafeNormal();
	}
	else
	{
		//direction = player->Camera->GetForwardVector();
		direction = ( ( player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * ( totalDistance + tmpDistance ) ) - GetActorLocation() ).GetSafeNormal();
		//direction = ( ( GetActorLocation() + player->Camera->GetForwardVector() * totalDistance ) - GetActorLocation() ).GetSafeNormal();
	}
	Projectile->Velocity = direction * Projectile->InitialSpeed;
	/*Projectile->bSimulationEnabled = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
	UKismetSystemLibrary::K2_SetTimer(this, "Inactive", duration, false);*/
	SetActive(true);
}

void AC_PyoChang::FirePyoChangQuickR()
{
	if ( !player ) return;

	SetActorLocation(player->GetActorLocation() + player->GetActorForwardVector() * 100.0f);

	FHitResult tmpHit;
	FVector start = player->Camera->GetComponentLocation();
	FVector end = player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * 10000.0f;
	GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera);
	FVector direction;
	if ( tmpHit.bBlockingHit )
	{
		direction = ( tmpHit.Location - GetActorLocation() ).GetSafeNormal();
	}
	else
	{
		direction = ( ( player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * (totalDistance + 300.0f) ) - GetActorLocation() ).GetSafeNormal();
	}
	Projectile->Velocity = direction * Projectile->InitialSpeed;
	SetActive(true);
}

void AC_PyoChang::SetActive(bool bActive)
{
	if (bActive)
	{
		//MulSetComEffect(true);
		//Projectile->Velocity = GetActorForwardVector() * Projectile->InitialSpeed;
		Projectile->bSimulationEnabled = true;

		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
		//niagaraCom->ResetRelativeTransform();
		niagaraCom->SetActive(true, true);
		/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: Bullet") , *GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 10.0f);*/
		//if ( niagaraCom->GetAsset() )
		//{
		//	GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , FString::Printf(TEXT("Niagara: %d") , niagaraCom->IsActive()));
		//}

		//UKismetSystemLibrary::K2_SetTimer(this, "Inactive", duration, false);
		//UKismetSystemLibrary::K2_SetTimer(this, "Destroy", duration, false);
	}
	else
	{
		Projectile->bSimulationEnabled = false;

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		//SetActorTickEnabled(false);
		// 삭제용...
		//niagaraCom->Deactivate();
		niagaraCom->SetActive(false);
		//MulSetComEffect(false);
		pyoAudio->Stop();
		pyoAudio->SetActive(false);
	}
}

void AC_PyoChang::MulSetActive_Implementation(bool bActive , const FVector& _Direction)
{
	if ( bActive )
	{
		Projectile->Velocity = _Direction * Projectile->InitialSpeed;

		MulSetComEffect(true);
		//niagaraCom->SetActive(true , true);
		// 
		//Projectile->Velocity = GetActorForwardVector() * Projectile->InitialSpeed;
		Projectile->bSimulationEnabled = true;

		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		SetActorTickEnabled(true);
		//niagaraCom->ResetRelativeTransform();
		//niagaraCom->SetActive(true, true);

		//if ( niagaraCom->GetAsset() )
		//{
		//	GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , FString::Printf(TEXT("Niagara: %d") , niagaraCom->IsActive()));
		//}

		//UKismetSystemLibrary::K2_SetTimer(this, "Inactive", duration, false);
		//UKismetSystemLibrary::K2_SetTimer(this, "Destroy", duration, false);
	}
	else
	{
		Projectile->bSimulationEnabled = false;

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);

		// 삭제용...
		//niagaraCom->Deactivate();
		//niagaraCom->SetActive(false);
		//niagaraCom->SetActive(false , true);
		MulSetComEffect(false);

		Destroy();

	}
}

void AC_PyoChang::Inactive()
{
	SetActive(false);
}

void AC_PyoChang::MulSetComEffect_Implementation(bool isOnOff)
{
	niagaraCom->SetActive(isOnOff, true);
	/*if ( player && isOnOff )
	{
		UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: SetEffect") , *player->GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 5.0f);
	}*/
	
}

