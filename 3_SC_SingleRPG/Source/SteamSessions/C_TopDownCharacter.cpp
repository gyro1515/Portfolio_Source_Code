// Fill out your copyright notice in the Description page of Project Settings.

#include "C_TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "CUW_CharacterOverHead.h"
#include "C_SlashAttack.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Animation/AnimMontage.h"
#include "Skill/C_Skill.h"
#include "Skill/C_FlooringSkill.h"
#include "Item/CItemStrut.h"
#include "Widget/C_Inventory.h"
#include "Widget/C_UI.h"
#include "C_TopDownController.h"
#include "Skill/C_Attack.h"
#include "Skill/C_SkillManager.h"
//#include "ProjectileAttack.h"
#include "Components/DecalComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "C_TopDownViewPawn.h"

// Sets default values
AC_TopDownCharacter::AC_TopDownCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	//CameraBoom->TargetArmLength = 800.f;
	CameraBoom->TargetArmLength = 1600.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("AttackDecal"));

	OverHeadUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadUI"));
	OverHeadUI->SetupAttachment(RootComponent);
	OverHeadUI->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


	// 스킬
	canInput = false;
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("?????????????????????????????????????????????????????")));

	// 미니맵

	// 미니맵

	MinimapBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MinimapBoom"));
	MinimapBoom->SetupAttachment(RootComponent);
	MinimapBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	
	MinimapBoom->TargetArmLength = 1500.f;
	MinimapBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.0f));
	MinimapBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	
	MinimapCam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MinimapCam"));
	MinimapCam->SetupAttachment(MinimapBoom);
	
	MinimapCam->OrthoWidth = 2000.0f;
	
}

// Called when the game starts or when spawned
void AC_TopDownCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("ChoseClass :  %d"), CharacterName));


	//240529 : 스킬 형식 현식님걸로
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SkillManager = GetWorld()->SpawnActor<AC_SkillManager>(SkillManagerClass, SpawnParams);
	q_AttackBase = dataTable->FindRow<FAttackBaseC>(Q_AttackName, Q_AttackName.ToString());
	w_AttackBase = dataTable->FindRow<FAttackBaseC>(W_AttackName, W_AttackName.ToString());
	e_AttackBase = dataTable->FindRow<FAttackBaseC>(E_AttackName, E_AttackName.ToString());
	a_AttackBase = dataTable->FindRow<FAttackBaseC>(A_AttackName, A_AttackName.ToString());
	// 240611 추가
	q_AttackBaseU = *(dataTable->FindRow<FAttackBaseC>(Q_AttackName, Q_AttackName.ToString()));
	w_AttackBaseU = *(dataTable->FindRow<FAttackBaseC>(W_AttackName, W_AttackName.ToString()));
	e_AttackBaseU = *(dataTable->FindRow<FAttackBaseC>(E_AttackName, E_AttackName.ToString()));
	a_AttackBaseU = *(dataTable->FindRow<FAttackBaseC>(A_AttackName, A_AttackName.ToString()));

	CharacterHp = CharacterMaxHp;
	
	MainController = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
	MainPawn = Cast<AC_TopDownViewPawn>(MainController->GetPawn());
}

// Called every frame
void AC_TopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator tmpRot = MainPawn->TopDownCameraComponent->GetComponentRotation();
	//tmpRot.Pitch *= -1;
	//tmpRot.Yaw -= 180.0;
	//
	//OverHeadUI->SetWorldRotation(tmpRot);
}

void AC_TopDownCharacter::RPCRoll()
{
	if (canInput) return;

	PlayAnimMontage(RollMotion);
}

void AC_TopDownCharacter::TakeDamage(float damageamount)
{
	CharacterHp -= damageamount;
	CharacterHp = FMath::Clamp(CharacterHp, 0.0f, CharacterMaxHp);
	UpdateHpPercent(CharacterHp, CharacterMaxHp);
}

void AC_TopDownCharacter::RecoveryHP(float hp)
{
	CharacterHp -= hp;
	CharacterHp = FMath::Clamp(CharacterHp, 0.0f, CharacterMaxHp);
	UpdateHpPercent(CharacterHp, CharacterMaxHp);
}

void AC_TopDownCharacter::RecoveryMP(float mp)
{
	//CharacterHp -= mp;
	//CharacterHp = FMath::Clamp(CharacterHp, 0.0f, 100.0f);
	//UpdateHpPercent(CharacterHp, 100.0f);
}

void AC_TopDownCharacter::UpdateHpPercent(float curHp, float maxHp)
{
	Cast<UCUW_CharacterOverHead>(OverHeadUI->GetUserWidgetObject())->SetHP(curHp,maxHp);
	if (MainController->PMain_UI)
	{
		MainController->PMain_UI->SetHpBar();
	}
}

void AC_TopDownCharacter::SetCharacterName(const FString& name)
{
	CharacterName = name;
	Cast<UCUW_CharacterOverHead>(OverHeadUI->GetUserWidgetObject())->SetName(CharacterName);
}



// Called to bind functionality to input
//void AC_TopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
//

void AC_TopDownCharacter::RPCAttack(UAnimMontage* AttackMon)
{
	if (canInput) return;
	//SkillManager->StartAttack(this, a_AttackBase, AttackInput::A);
	SkillManager->StartAttackU(this, a_AttackBaseU, AttackInput::A);
}

// 기존
void AC_TopDownCharacter::UseSkill_Q()
{
	if (canInput) return;
	//SkillManager->StartAttack(this, q_AttackBase, AttackInput::Q);
	SkillManager->StartAttackU(this, q_AttackBaseU, AttackInput::Q);
	

}

void AC_TopDownCharacter::UseSkill_W()
{
	if (canInput) return;
	//SkillManager->StartAttack(this, w_AttackBase, AttackInput::W);
	SkillManager->StartAttackU(this, w_AttackBaseU, AttackInput::W);
	
}

void AC_TopDownCharacter::UseSkill_E()
{
	//if (SkillManager->CanInput())
	{
		//SkillManager->StartAttack(this, e_AttackBase, AttackInput::E);
		SkillManager->StartAttackU(this, e_AttackBaseU, AttackInput::E);
	}

	// ***************스킬 독립 구현시*****************
	//if (canInput) return;
	////skill_E->FireSkill();
	//if (skill_E == nullptr || !skill_E->IsCoolTime())
	//{
	//	FActorSpawnParameters SpawnParams;
	//	SpawnParams.Owner = this;
	//
	//	skill_E = Cast<AC_Skill>(GetWorld()->SpawnActor<AC_Skill>(Skill_E_Class, SpawnParams));
	//	if (skill_E)
	//	{
	//		skill_E->SetPlayer(this);
	//		skill_E->SkillMotion = EMotion;
	//		skill_E->FireSkill();
	//		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Q")));
	//
	//	}
	//}
}

//void AC_TopDownCharacter::SetTopDownCharacter()
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("zzzzzzzzzzzzzzzzzzzzzzzzzzz")));
//
//	// 스킬 세팅
//	//FActorSpawnParameters SpawnParams;
//	//SpawnParams.Owner = this;
//	//
//	//skill_Q = Cast<AC_Skill>(GetWorld()->SpawnActor<AC_Skill>(Skill_Q_Class, SpawnParams));
//	//if (skill_Q)
//	//{
//	//	skill_Q->SetPlayer(this);
//	//	skill_Q->SkillMotion = QMotion;
//	//	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Q")));
//	//
//	//}
//	//skill_W = Cast<AC_Skill>(GetWorld()->SpawnActor<AC_Skill>(Skill_W_Class, SpawnParams));
//	//if (skill_W)
//	//{
//	//	skill_W->SetPlayer(this);
//	//	skill_W->SkillMotion = WMotion;
//	//
//	//	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("W")));
//	//}
//	//skill_E = Cast<AC_Skill>(GetWorld()->SpawnActor<AC_Skill>(Skill_E_Class, SpawnParams));
//	//if (skill_E)
//	//{
//	//	skill_E->SetPlayer(this);
//	//	skill_E->SkillMotion = EMotion;
//	//	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("E")));
//	//}
//	//
//	//
//	//if (skill_Q && skill_W && skill_E)
//	//{
//	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("SkillSetting!")));
//	//}
//}
