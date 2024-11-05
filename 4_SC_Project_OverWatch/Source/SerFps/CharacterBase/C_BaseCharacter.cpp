// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/C_BaseCharacter.h"
// 네트워크
#include "Net/UnrealNetwork.h"
// 데미지
#include "Kismet/GameplayStatics.h"
// 캡슐 컴포넌트
#include "Components/CapsuleComponent.h"
// 나이라가라
#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
// 위젯
#include "Blueprint/UserWidget.h"
#include "CharacterBase/C_ZoneWidget.h"
// 사운드 컴포넌트
#include "Components/AudioComponent.h"


// Sets default values
AC_BaseCharacter::AC_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	if ( HasAuthority() )
	{
		SetReplicates(true);
	}
}

// Called when the game starts or when spawned
void AC_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	AController* tmp = Cast<AController>(GetController());
	if ( tmp && tmp->IsLocalPlayerController() )
	{
		zoneWidget = Cast<UC_ZoneWidget>(CreateWidget(GetWorld() , zoneWidgetClass));
		//zoneWidget->AddToViewport();
	}
}

// Called every frame
void AC_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( bDie )
	{
		FRotator tmpRot = GetControlRotation();
		if (FMath::IsNearlyEqual(tmpRot.Pitch, 270.0f) )
		{
			return;
		}
		else if (tmpRot.Pitch >= 0.0f)
		{
			AddControllerPitchInput(1.0f);
		}
		else if ( (tmpRot.Pitch <= 90.0f) )
		{
			AddControllerPitchInput(-1.0f);
		}
		if ( bDestroy )
		{
			tmpDieTime += DeltaTime;
			if ( tmpDieTime >= dieTime )
			{
				Destroy();
				tmpDieTime = 0.0f;
				bDestroy = false;
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , FString::Printf(TEXT("P: %f") , tmpRot.Pitch));
	}
	
}

// Called to bind functionality to input
void AC_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AC_BaseCharacter , curHp);
	DOREPLIFETIME(AC_BaseCharacter , bDie);
	DOREPLIFETIME(AC_BaseCharacter , bDestroy);

}

float AC_BaseCharacter::TakeDamage(float DamageAmount , FDamageEvent const& DamageEvent , AController* EventInstigator , AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount , DamageEvent , EventInstigator , DamageCauser);
	float tmpDamage = DamageAmount; // + 쉴드, 방어력 등등 있으면 추가 작업
	curHp -= tmpDamage;
	if ( curHp <= 0.0f )
	{
		curHp = 0.0f;
		CharacterDie();
	}
	return tmpDamage;
}

void AC_BaseCharacter::CharacterDie()
{
	bDie = true;
	ClientAddDieWidget();
}

void AC_BaseCharacter::ClientRemoveZoneWidget_Implementation()
{
	AController* tmp = Cast<AController>(GetController());
	if ( tmp && tmp->IsLocalPlayerController() && zoneWidget )
	{
		zoneWidget->zoneSound->Stop();
		zoneWidget->RemoveFromParent();
	}
}

void AC_BaseCharacter::ClientAddZoneWidget_Implementation()
{
	AController* tmp = Cast<AController>(GetController());
	if ( tmp && tmp->IsLocalPlayerController() && zoneWidget )
	{
		zoneWidget->AddToViewport(0);
		zoneWidget->zoneSound->Play();
	}
}

void AC_BaseCharacter::ClientAddDieWidget_Implementation()
{
	AController* tmp = Cast<AController>(GetController());
	if ( tmp && tmp->IsLocalPlayerController() )
	{
		dieWidget = Cast<UUserWidget>(CreateWidget(GetWorld() , dieWidgetClass));
		dieWidget->AddToViewport(2);
		/*UKismetSystemLibrary::PrintString(GetWorld() ,
		FString::Printf(TEXT("%s: addDIe") , *GetActorNameOrLabel())
		, true , true , FColor::MakeRandomColor() , 5.0f);*/
	}
}

void AC_BaseCharacter::MulSpawnEffect_Implementation(UNiagaraSystem* SystemTemplate, FVector SpawnLocation, FRotator SpawnRotation, FVector Scale)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SystemTemplate,
		SpawnLocation, SpawnRotation, Scale);
}

void AC_BaseCharacter::MulPlaySound_Implementation(USoundBase* Sound, FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld() , Sound , Location , 1.0f , 1.0f , 0.0f , Attenuation);
}

