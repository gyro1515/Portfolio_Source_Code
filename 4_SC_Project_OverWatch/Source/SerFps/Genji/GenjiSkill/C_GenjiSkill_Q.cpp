// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_GenjiSkill_Q.h"
#include "Genji/C_CharacterGenji.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
// 위젯 관련
#include "CharacterBase/C_BaseWidget.h"

AC_GenjiSkill_Q::AC_GenjiSkill_Q()
{
	coolTime = 1.0f;
	Damage = 110.0f;
}

void AC_GenjiSkill_Q::BeginPlay()
{
	Super::BeginPlay();

}

void AC_GenjiSkill_Q::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( !HasAuthority() ) return;
	if (bDrangonSowrd)
	{
		tmpSkillDuration += DeltaTime;
		if (tmpSkillDuration >= skillDuration)
		{
			tmpSkillDuration = 0;
			bDrangonSowrd = false;
			player->bDrangonSowrd = bDrangonSowrd;
			player->bCanAttack = false;
			//player->actionState = EActionState::PyoChang;
			//player->MulStopMontage();
			MulPlayMontage(QEndMotion);
		}
	}
}

void AC_GenjiSkill_Q::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor == Owner || !bDrangonSowrd || !HasAuthority()) return;
	AC_CharacterGenji* tmpPlayer = Cast<AC_CharacterGenji>(OtherActor);
	if (!tmpPlayer) return;
	if (tmpPlayer->GetCapsuleComponent() != OtherComp)
	{
		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: NotMainCol"), *OtherComp->GetFName().ToString())
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
		return;
	}
	TSubclassOf<UDamageType> DamageType;
	FRotator tmpRot = player->GetActorRotation();
	switch ( skilMotionNum )
	{
	case 1:
		MulPlaySound(HitSound1, SweepResult.Location);
		//GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , TEXT("H1"));
		tmpRot.Roll += 120.0f;
		break;
	case 2:
		MulPlaySound(HitSound2, SweepResult.Location);
		tmpRot.Roll += 45.0f;
		//GEngine->AddOnScreenDebugMessage(-1 , 3.0f , FColor::MakeRandomColor() , TEXT("H2"));
		break;
	default:
		break;
	}
	MulSpawnEffect(HitEffectN , OtherActor->GetActorLocation() , tmpRot , FVector(1.0f , 1.0f , 1.0f));

	UGameplayStatics::ApplyDamage(OtherActor, Damage,
		player->GetController(), player, DamageType);
}

void AC_GenjiSkill_Q::UseSkill()
{
	if (gauge != 100.0f) return;
	gauge = 0.0f;
	ClientSetWidgetGauge(gauge);
	ClientSetWidgetGaugeIcon(false);
	MulPlayMontage(QStartMotion);
	bDrangonSowrd = true;
	player->bDrangonSowrd = bDrangonSowrd;
	isCoolTime = true;
	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("useQ")));

}

void AC_GenjiSkill_Q::DragonSlash()
{
	if (isCoolTime) return;
	isCoolTime = true;
	skilMotionNum %= 2;
	
	switch (skilMotionNum)
	{
	case 0:
		MulPlayMontage(QSlash1Motion);
		break;
	case 1:
		MulPlayMontage(QSlash2Motion);

		break;
	default:
		break;
	}
	skilMotionNum++;
}

void AC_GenjiSkill_Q::AddGauge(float addGauge)
{
	if ( bDrangonSowrd ) return;
	
	gauge += addGauge;
	if (gauge >= 100.0f)
	{
		gauge = 100.0f;
		ClientSetWidgetGaugeIcon(true);
	}
	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: Gauge_%f"), *GetActorNameOrLabel(), gauge));
	ClientSetWidgetGauge(gauge);
}

void AC_GenjiSkill_Q::SpawnSlash1N()
{
	FVector tmpL = player->GetActorLocation();
	tmpL.Z -= 87.0f;
	FRotator tmpR = player->GetActorRotation();
	tmpR.Yaw -= 90.0f;
	MulSpawnEffect(Slash1N , tmpL , tmpR, FVector(1.0f, 1.0f, 1.0f));
}

void AC_GenjiSkill_Q::SpawnSlash2N()
{
	FVector tmpL = player->GetActorLocation();
	tmpL.Z -= 87.0f;
	FRotator tmpR = player->GetActorRotation();
	tmpR.Yaw -= 90.0f;
	MulSpawnEffect(Slash2N , tmpL , tmpR , FVector(1.0f , 1.0f , 1.0f));
}

void AC_GenjiSkill_Q::ClientSetWidgetGaugeIcon_Implementation(bool iconOnOff)
{
	if ( !IsValid(player) ) return;
	player->mainWidget->SetQGaugeIcon(iconOnOff);
}

void AC_GenjiSkill_Q::ClientSetWidgetGauge_Implementation(float _gauge)
{
	if ( !IsValid(player) ) return;
	player->mainWidget->SetQGauge(_gauge);
}
