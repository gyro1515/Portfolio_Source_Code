// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_GenjiSkill_LeftClick.h"
#include "Kismet/GameplayStatics.h"
#include "Genji/C_CharacterGenji.h"
#include "Animation/AnimInstance.h"
#include "Genji/GenjiSkill/C_GenjiSkill_Q.h"

//Test
#include "Genji/C_PyoChang.h"


// Sets default values
AC_GenjiSkill_LeftClick::AC_GenjiSkill_LeftClick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//if (HasAuthority())
	//{
	//	SetReplicates(true);
	//}
}

// Called when the game starts or when spawned
void AC_GenjiSkill_LeftClick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GenjiSkill_LeftClick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (isCoolTime)
	//{
	//	tmpCoolTime += DeltaTime;
	//	if (tmpCoolTime >= coolTime)
	//	{
	//		tmpCoolTime -= coolTime;
	//		isCoolTime = false;
	//	}
	//}
}

void AC_GenjiSkill_LeftClick::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (!HasAuthority()) return;
	if (OtherActor == this || OtherActor == Owner || OtherActor->Owner == Owner || !HasAuthority() ) return;

	//TSubclassOf<UDamageType> DamageType;
	//
	//UGameplayStatics::ApplyDamage(OtherActor, Damage,
	//	player->GetController(), player, DamageType);
	AC_BaseCharacter* tmpChar = Cast<AC_BaseCharacter>(OtherActor);
	if ( tmpChar )
	{
		player->skillQ->AddGauge(Damage);
	}

	//FTransform transform = OtherActor->GetTransform();
	//transform.AddToTranslation(SkillEffectOffset);
	//transform.SetRotation(player->GetActorRotation().Quaternion());
	//
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, transform);
}

void AC_GenjiSkill_LeftClick::UseSkill()
{
	if (isCoolTime) return;
	isCoolTime = true;
	//UAnimInstance* AnimInstance = player->DefaultMesh->GetAnimInstance();
	//if (player->LeftClickMotion && AnimInstance)
	//AnimInstance->Montage_Play(player->LeftClickMotion, 1.2f);
	MulPlayMontage(AttackMotion);
}



