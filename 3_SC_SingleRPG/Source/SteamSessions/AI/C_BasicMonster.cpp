// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_BasicMonster.h"
#include "C_TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "CUW_CharacterOverHead.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Skill/C_SkillManager.h"
#include "Skill/C_Attack.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AC_BasicMonster::AC_BasicMonster()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	OverHeadUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadUI"));
	OverHeadUI->SetupAttachment(RootComponent);
	OverHeadUI->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));




 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AC_BasicMonster::BeginPlay()
{
	Super::BeginPlay();

	ResetSer();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SkillManager = GetWorld()->SpawnActor<AC_SkillManager>(SkillManagerClass, SpawnParams);
	Skill_0_Base = dataTable->FindRow<FAttackBaseC>(Skill_0_Name, Skill_0_Name.ToString());
	Skill_1_Base = dataTable->FindRow<FAttackBaseC>(Skill_1_Name, Skill_1_Name.ToString());
	Skill_2_Base = dataTable->FindRow<FAttackBaseC>(Skill_2_Name, Skill_2_Name.ToString());
	Skill_3_Base = dataTable->FindRow<FAttackBaseC>(Skill_3_Name, Skill_3_Name.ToString());


	Skill_0_BaseU = *(dataTable->FindRow<FAttackBaseC>(Skill_0_Name, Skill_0_Name.ToString()));
	Skill_1_BaseU = *(dataTable->FindRow<FAttackBaseC>(Skill_1_Name, Skill_1_Name.ToString()));
	Skill_2_BaseU = *(dataTable->FindRow<FAttackBaseC>(Skill_2_Name, Skill_2_Name.ToString()));
	Skill_3_BaseU = *(dataTable->FindRow<FAttackBaseC>(Skill_3_Name, Skill_3_Name.ToString()));
	//Skill_3_BaseU = dataTable->FindRow<FAttackBaseC>(Skill_3_Name, Skill_3_Name.ToString()) ? *(dataTable->FindRow<FAttackBaseC>(Skill_3_Name, Skill_3_Name.ToString())) : FAttackBaseC();

}



void AC_BasicMonster::ResetSer()
{
	//ResetMul();
	SetMonsterName(MonsterName);
	UpdateHpPercent(100.0f, 100.0f);

}

void AC_BasicMonster::ResetMul_Implementation()
{
	//SetMonsterName(MonsterName);
	//UpdateHpPercent(100.0f, 100.0f);
}


void AC_BasicMonster::SetMonsterName_Implementation(const FString& name)
{
	UCUW_CharacterOverHead* tmp = Cast<UCUW_CharacterOverHead>(OverHeadUI->GetWidget());
	tmp->SetName(name);
}

void AC_BasicMonster::SerTakeDamage_Implementation(float damageamount)
{
	MonsterHp -= damageamount;
	UpdateHpPercent(MonsterHp, MonsterMaxHp);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("TakeDamage")));

}

void AC_BasicMonster::UpdateHpPercent_Implementation(float curHp, float maxHp)
{
	UCUW_CharacterOverHead* tmp = Cast<UCUW_CharacterOverHead>(OverHeadUI->GetWidget());
	tmp->SetHP(curHp, maxHp);
	HpPercent = curHp / maxHp;
}

void AC_BasicMonster::SerAttack_Implementation(UAnimMontage* attack)
{
}

void AC_BasicMonster::MulRPCAttack_Implementation(UAnimMontage* attack)
{
}


void AC_BasicMonster::MonsterSkill0(AC_TopDownCharacter* target)
{
	SkillManager->MonsterAttack(this, Skill_0_BaseU, AttackInput::Q,target);
	PlayAnimMontage(Attack0);
}

void AC_BasicMonster::MonsterSkill1(AC_TopDownCharacter* target , FVector location)
{
	SkillManager->MonsterAttack(this, Skill_1_BaseU, AttackInput::W,target , location);
	//GetWorld()->SpawnActor<AC_LOSPillar>(PillarClass, target->GetActorLocation(), GetActorRotation());
	PlayAnimMontage(Attack1);

}

void AC_BasicMonster::MonsterSkill2(AC_TopDownCharacter* target)
{
	SkillManager->MonsterAttack(this, Skill_2_BaseU, AttackInput::E, target);
	PlayAnimMontage(Attack2);
}

void AC_BasicMonster::MonsterSkill3(AC_TopDownCharacter* target)
{
	SkillManager->MonsterAttack(this, Skill_3_BaseU, AttackInput::A, target);
	PlayAnimMontage(Attack3);
}

void AC_BasicMonster::DeathParticle()
{

}

void AC_BasicMonster::Die()
{
	isDead = true;

	USkeletalMeshComponent* SkeletalMesh = GetMesh(); // 또는 해당 액터의 Skeletal Mesh 컴포넌트를 얻어옵니다.

	if (SkeletalMesh)
	{
		SkeletalMesh->SetSimulatePhysics(true); // 래그돌로 설정
		SkeletalMesh->SetCollisionProfileName(TEXT("Ragdoll")); // 래그돌이 적용될 때의 충돌 프로필 설정
	}
}

// Called every frame
//void AC_BasicMonster::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

