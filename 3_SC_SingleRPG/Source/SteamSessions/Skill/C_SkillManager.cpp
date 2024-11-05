// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/C_SkillManager.h"
#include "Skill/C_Attack.h"
#include "AI/C_LOSPillar.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Skill/C_Attack.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/DecalComponent.h"
#include "C_TopDownCharacter.h"
#include "C_TopDownController.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
AC_SkillManager::AC_SkillManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->Activate(false);// 데칼 끄기
	Decal->SetHiddenInGame(true);

	attacks.Add(AttackInput::Q, nullptr);
	attacks.Add(AttackInput::W, nullptr);
	attacks.Add(AttackInput::E, nullptr);
	attacks.Add(AttackInput::A, nullptr);
}

void AC_SkillManager::StartAttack(AC_TopDownCharacter* Own, FAttackBaseC* attackBase, AttackInput attackInput)
{
	// 데칼 켜져있으면 끄기, 데칼 중 클릭 끄기 등, 스킬 스폰전 다른 스킬 사용시 초기세팅으로
	ResetSkillManager();

	if ((attacks[attackInput] == nullptr || attacks[attackInput]->isOnCoolDown == false) && canInput)
	{
		// 나중에 스폰에 필요한 값들 저장해두기
		tmpOwn = Own;
		tmpAttackBase = attackBase;
		tmpAttackInput = attackInput;
		switch (attackBase->SelAttackType)
		{
		case AttackType::SLASH:
			SpawnAttack(Own, attackBase, attackInput);
			break;
		case AttackType::FLOOR:
			decalClickOn = true;
			//canInput = false;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase->DecalMaterial);
			Decal->DecalSize = attackBase->DecalSize;
			break;
		case AttackType::PROJECTILE:
			SpawnAttack(Own, attackBase, attackInput);
			break;
		case AttackType::FLOOR_JUMP:
			decalClickOn = true;
			isJump = true;
			canInput = false;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase->DecalMaterial);
			Decal->DecalSize = attackBase->DecalSize;

			break;
		case AttackType::CHARGING_SLASH:
			chargingTriggeredOn = true;
			canInput = false;

			break;
		case AttackType::CHARGING_PROJECTILE:
			chargingTriggeredOn = true;
			canInput = false;

			break;
		case AttackType::METEOR:
			decalClickOn = true;
			delayAttackOn = true;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase->DecalMaterial);
			Decal->DecalSize = attackBase->DecalSize;
			break;
		case AttackType::SPAWN:
			decalClickOn = true;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase->DecalMaterial);
			Decal->DecalSize = attackBase->DecalSize;
			break;
		default:
			break;
		}
	}
	
}

void AC_SkillManager::SpawnAttack(AC_TopDownCharacter* Own, FAttackBaseC* attackBase, AttackInput attackInput)
{
	Own->GetController()->StopMovement();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Own;
	FRotator Rotation = Own->GetActorRotation();

	switch (attackBase->SelAttackType)
	{
	case AttackType::SLASH:
	{
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase->AttackDistance; // 베기 시작 위치 설정
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBase(attackBase);

	}
		break;
	case AttackType::FLOOR:
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
		}
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBase(attackBase);
		FVector WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		FRotator tmpRot;
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);
	}
		break;
	case AttackType::PROJECTILE:
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
		}
		FVector WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		FRotator tmpRot;
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);
		tmpRot = WorldDirection.Rotation();
		//spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase->AttackDistance; //시작 위치 설정, **캐릭터 소켓으로 수정하기
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase->AttackDistance; //시작 위치 설정, **캐릭터 소켓으로 수정하기
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, tmpRot, SpawnParams);
		attacks[attackInput]->SetAttackBase(attackBase);
	}
		break;
	case AttackType::FLOOR_JUMP:
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBase(attackBase);
		break;
	case AttackType::CHARGING_SLASH:
	{
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * 100.0f; //시작 위치 설정, 
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		// 차징 데미지 증가
		float tmpDamage = attackBase->Damage; // 차징 데미지 변경용, 기본 데미지 백업하기
		attackBase->Damage *= chargingTime;
		attacks[attackInput]->SetAttackBase(attackBase);
		attackBase->Damage = tmpDamage; // 스킬 데미지 원상복구
	}
		break;
	case AttackType::CHARGING_PROJECTILE:
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
		}
		FVector WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		FRotator tmpRot;
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * 100.0f; //시작 위치 설정, **캐릭터 소켓으로 수정하기
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		// 차징 데미지 증가
		float tmpDamage = attackBase->Damage; // 차징 데미지 변경용, 기본 데미지 백업하기
		attackBase->Damage *= chargingTime;
		attacks[attackInput]->SetAttackBase(attackBase);
		attackBase->Damage = tmpDamage; // 스킬 데미지 원상복구
	}
		break;
	case AttackType::METEOR:
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBase(attackBase);
		break;
	case AttackType::SPAWN:
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBase(attackBase);
		break;
	default:
		break;
	}

	switch (attackInput)
	{
	case AttackInput::Q:
		Own->PlayAnimMontage(Own->QMotion);
		break;
	case AttackInput::W:
		Own->PlayAnimMontage(Own->WMotion);
		break;
	case AttackInput::E:
		Own->PlayAnimMontage(Own->EMotion);

		break;
	case AttackInput::A:
		Own->PlayAnimMontage(Own->MeleeMotion);
		break;
	default:
		break;
	}

	attacks[attackInput]->SetActiveOn();
	canInput = true;
}

void AC_SkillManager::StartAttackU(AC_TopDownCharacter* Own, FAttackBaseC attackBase, AttackInput attackInput)
{
	// 데칼 켜져있으면 끄기, 데칼 중 클릭 끄기 등, 스킬 스폰전 다른 스킬 사용시 초기세팅으로
	ResetSkillManager();

	if ((attacks[attackInput] == nullptr || attacks[attackInput]->isOnCoolDown == false) && canInput)
	{
		// 나중에 스폰에 필요한 값들 저장해두기
		tmpOwn = Own;
		tmpAttackBaseU = attackBase;
		tmpAttackInput = attackInput;
		switch (attackBase.SelAttackType)
		{
		case AttackType::SLASH:
			SpawnAttackU(Own, attackBase, attackInput);
			break;
		case AttackType::FLOOR:
			decalClickOn = true;
			//canInput = false;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase.DecalMaterial);
			Decal->DecalSize = attackBase.DecalSize;
			break;
		case AttackType::PROJECTILE:
			SpawnAttackU(Own, attackBase, attackInput);
			break;
		case AttackType::FLOOR_JUMP:
			decalClickOn = true;
			isJump = true;
			canInput = false;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase.DecalMaterial);
			Decal->DecalSize = attackBase.DecalSize;

			break;
		case AttackType::CHARGING_SLASH:
			chargingTriggeredOn = true;
			canInput = false;

			break;
		case AttackType::CHARGING_PROJECTILE:
			chargingTriggeredOn = true;
			canInput = false;

			break;
		case AttackType::METEOR:
			decalClickOn = true;
			delayAttackOn = true;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase.DecalMaterial);
			Decal->DecalSize = attackBase.DecalSize;
			break;
		case AttackType::SPAWN:
			decalClickOn = true;
			Decal->Activate(true);// 데칼 보이기
			Decal->SetHiddenInGame(false);
			Decal->SetDecalMaterial(attackBase.DecalMaterial);
			Decal->DecalSize = attackBase.DecalSize;
			break;
		default:
			break;
		}
	}
}

void AC_SkillManager::SpawnAttackU(AC_TopDownCharacter* Own, FAttackBaseC attackBase, AttackInput attackInput)
{
	Own->GetController()->StopMovement();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Own;
	FRotator Rotation = Own->GetActorRotation();

	FHitResult Hit;
	bool bHitSuccessful = false;
	FVector WorldDirection;
	FRotator tmpRot;

	switch (attackBase.SelAttackType)
	{
	case AttackType::SLASH:
	{
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase.AttackDistance; // 베기 시작 위치 설정
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);

	}
	break;
	case AttackType::FLOOR:
	{
		//FHitResult Hit;
		//bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
		}
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		
	}
	break;
	case AttackType::PROJECTILE:
	{
		//FHitResult Hit;
		//bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
			// 타겟 위치보다 살짝 높게
			spawnLocation.Z += 100.0;
		}
		WorldDirection = spawnLocation - Own->GetActorLocation();
		WorldDirection = WorldDirection.GetSafeNormal();
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);

		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase.AttackDistance; //시작 위치 설정, **캐릭터 소켓으로 수정하기
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, WorldDirection.Rotation(), SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		attacks[attackInput]->worldDicrec = WorldDirection;
		tmpWorldDirection = WorldDirection;

	}
	break;
	case AttackType::FLOOR_JUMP:
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		break;
	case AttackType::CHARGING_SLASH:
	{
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * 100.0f; //시작 위치 설정, 
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		// 차징 데미지 증가
		float tmpDamage = attackBase.Damage; // 차징 데미지 변경용, 기본 데미지 백업하기
		attackBase.Damage *= chargingTime;
		attacks[attackInput]->SetAttackBaseU(attackBase);
		attackBase.Damage = tmpDamage; // 스킬 데미지 원상복구
	}
	break;
	case AttackType::CHARGING_PROJECTILE:
	{
		//FHitResult Hit;
		//bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
		}
		WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * 100.0f; //시작 위치 설정, **캐릭터 소켓으로 수정하기
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		// 차징 데미지 증가
		float tmpDamage = attackBase.Damage; // 차징 데미지 변경용, 기본 데미지 백업하기
		attackBase.Damage *= chargingTime;
		attacks[attackInput]->SetAttackBaseU(attackBase);
		attackBase.Damage = tmpDamage; // 스킬 데미지 원상복구
	}
	break;
	case AttackType::METEOR:
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		break;
	case AttackType::SPAWN:
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		break;
	default:
		break;
	}

	switch (attackInput)
	{
	case AttackInput::Q:
		Own->PlayAnimMontage(Own->QMotion);
		break;
	case AttackInput::W:
		Own->PlayAnimMontage(Own->WMotion);
		break;
	case AttackInput::E:
		Own->PlayAnimMontage(Own->EMotion);

		break;
	case AttackInput::A:
		Own->PlayAnimMontage(Own->MeleeMotion);
		break;
	default:
		break;
	}

	attacks[attackInput]->SetActiveOn();
	canInput = true;
}

void AC_SkillManager::MonsterAttack(AC_BasicMonster* Own, FAttackBaseC attackBase, AttackInput attackInput, AC_TopDownCharacter* target, FVector location)
{
	ResetSkillManager();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Own;
	FRotator Rotation = Own->GetActorRotation();

	switch (attackBase.SelAttackType)
	{
	case AttackType::SLASH:
	{
		//spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase.AttackDistance; // 베기 시작 위치 설정
		//attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, target->GetActorLocation(), Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
	}
	break;
	case AttackType::FLOOR:
	{
		spawnLocation = target->GetActorLocation();

		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		FVector WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		FRotator tmpRot;
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);
	}
	break;
	case AttackType::PROJECTILE:
	{
		FRotator tmpRot;
		tmpRot.Yaw = Own->GetActorRotation().Yaw;
		spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase.AttackDistance;//시작 위치 설정, **캐릭터 소켓으로 수정하기
		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, tmpRot, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
	}
	break;
	case AttackType::FLOOR_JUMP:
		break;
	case AttackType::CHARGING_SLASH:
	{
	}
	break;
	case AttackType::CHARGING_PROJECTILE:
	{
	}
	break;
	case AttackType::METEOR:
		break;
	case AttackType::SPAWN:
	{
		spawnLocation = location;
		//spawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * 200; // 베기 시작 위치 설정

		attacks[attackInput] = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, spawnLocation, Rotation, SpawnParams);
		attacks[attackInput]->SetAttackBaseU(attackBase);
		FVector WorldDirection = (spawnLocation - Own->GetActorLocation()).GetSafeNormal();
		FRotator tmpRot;
		tmpRot.Pitch = 0;
		tmpRot.Roll = 0;
		tmpRot.Yaw = WorldDirection.Rotation().Yaw;
		Own->SetActorRotation(tmpRot);

		{
			AC_LOSPillar* tmpPil = GetWorld()->SpawnActor<AC_LOSPillar>(PillarClass, spawnLocation, Rotation, SpawnParams);

			// 밑은 테스트용 삭제 필요
			//if (tmpPil)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Spawn X: %f, Y: %f, Z: %f"), spawnLocation.X, spawnLocation.Y, spawnLocation.Z));
			//
			//	//spawnLocation = target->GetActorLocation();
			//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Target X: %f, Y: %f, Z: %f"), spawnLocation.X, spawnLocation.Y, spawnLocation.Z));
			//
			//	AC_TopDownController* tmpCont = Cast<AC_TopDownController>(GetWorld()->GetFirstPlayerController());
			//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Tank X: %f, Y: %f, Z: %f"), tmpCont->Tank->GetActorLocation().X, tmpCont->Tank->GetActorLocation().Y, tmpCont->Tank->GetActorLocation().Z));
			//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("DPS X: %f, Y: %f, Z: %f"), tmpCont->DPS->GetActorLocation().X, tmpCont->DPS->GetActorLocation().Y, tmpCont->DPS->GetActorLocation().Z));
			//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Heal X: %f, Y: %f, Z: %f"), tmpCont->Heal->GetActorLocation().X, tmpCont->Heal->GetActorLocation().Y, tmpCont->Heal->GetActorLocation().Z));
			//}
		}
	}
		break;
	default:
		break;
	}

	switch (attackInput)
	{
	case AttackInput::Q:
		Own->PlayAnimMontage(Own->Attack0);
		break;
	case AttackInput::W:
		Own->PlayAnimMontage(Own->Attack1);
		break;
	case AttackInput::E:
		Own->PlayAnimMontage(Own->Attack2);

		break;
	case AttackInput::A:
		Own->PlayAnimMontage(Own->Attack3);
		break;
	default:
		break;
	}

	attacks[attackInput]->SetActiveOn();
	canInput = true;

}

void AC_SkillManager::SpawnAttackDPS(AC_TopDownCharacter* Own, FAttackBaseC attackBase)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Own;
	FRotator Rotation = tmpWorldDirection.Rotation();
	FVector tmpSpawnLocation;
	tmpSpawnLocation = Own->GetActorLocation() + Own->GetActorForwardVector() * attackBase.AttackDistance; //시작 위치 설정, **캐릭터 소켓으로 수정하기
	AC_Attack* tmpAttack = GetWorld()->SpawnActor<AC_Attack>(BaseSkill, tmpSpawnLocation, Rotation, SpawnParams);
	tmpAttack->SetAttackBaseU(attackBase);
	tmpAttack->SetActiveOn();
}


void AC_SkillManager::Click()
{
	if (!decalClickOn) return;
	if (isJump) return;
	decalClickOn = false;
	//SpawnAttack(tmpOwn, tmpAttackBase, tmpAttackInput);
	SpawnAttackU(tmpOwn, tmpAttackBaseU, tmpAttackInput);
	Decal->Activate(false);// 데칼 끄기
	Decal->SetHiddenInGame(true);
}

void AC_SkillManager::ResetSkillManager()
{
	decalClickOn = false;
	Decal->Activate(false);// 데칼 끄기
	Decal->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void AC_SkillManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	//APlayerController* PlayerController = Cast<APlayerController>(player->GetController());

	if (PlayerController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Controller0")));

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(SkillMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(SkillSpawnAction, ETriggerEvent::Started, this, &AC_SkillManager::Click);
		}

	}
	Decal->Activate(false);// 데칼 끄기
	Decal->SetHiddenInGame(true);
}

// Called every frame
void AC_SkillManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (decalClickOn)
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		//APlayerController* tmpCont = Cast<APlayerController>(player->GetController());
		APlayerController* tmpCont = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (tmpCont)
		{
			bHitSuccessful = tmpCont->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::MakeRandomColor(), FString::Printf(TEXT("Decal")));
		}
		if (bHitSuccessful)
		{
			spawnLocation = Hit.Location;
		}
		Decal->SetWorldLocation(spawnLocation);
	}
}

