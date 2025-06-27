// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/C_CharacterGenji.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Genji/C_PyoChang.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// 벽
#include "Engine/StaticMeshActor.h"

// 스킬
#include "Genji/GenjiSkill/C_GenjiSkill_LeftClick.h"
#include "Genji/GenjiSkill/C_GenjiSkill_Q.h"
#include "Genji/GenjiSkill/C_GenjiSkill_LeftShift.h"
#include "Genji/GenjiSkill/C_GenjiSkill_E.h"
#include "Genji/GenjiSkill/C_GenjiSkill_Reload.h"
#include "Genji/GenjiSkill/C_GenjiSkill_RightClick.h"
// 총알
#include "CharacterBase/C_BaseBullet.h"
// 위젯
#include "Blueprint/UserWidget.h"
#include "CharacterBase/C_BaseWidget.h"


// Sets default values
AC_CharacterGenji::AC_CharacterGenji()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	SAForSkillQ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SAForSkillQ"));
	SAForSkillQ->SetupAttachment(RootComponent);
	SAForSkillQ->bDoCollisionTest = false;
	// 버그 발생시 블루프린트 확인
	QCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("QCollider"));
	QCollider->SetupAttachment(SAForSkillQ);
	QCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	QCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn , ECollisionResponse::ECR_Ignore);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	DefaultMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DefaultMesh"));
	DefaultMesh->SetupAttachment(GetCapsuleComponent());
	Pyo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pyo"));
	Pyo->SetupAttachment(DefaultMesh);
	Long = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Long"));
	Long->SetupAttachment(DefaultMesh);
	Short = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Short"));
	Short->SetupAttachment(DefaultMesh);
	
	bThrowPyo = false;
	bPyoReload = false;
	bCanAirJump = false;
	//GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->ComponentTags.Add(FName("MainCol"));
	//for (FName tmp : GetCapsuleComponent()->ComponentTags)
	//{
	//	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: %s"), *GetActorNameOrLabel(), *tmp.ToString())
	//		, true, true, FColor::MakeRandomColor(), 10.0f);
	//}
	//if (GetCapsuleComponent()->ComponentHasTag(TEXT("MainCol")))
	//{
	//	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: HasTag"), *GetActorNameOrLabel())
	//		, true, true, FColor::MakeRandomColor(), 10.0f);
	//}
	/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: Test"), *GetCapsuleComponent()->GetFName().ToString())
		, true, true, FColor::MakeRandomColor(), 10.0f);*/

	if (HasAuthority())
	{
		SetReplicates(true);
	}
}

// Called when the game starts or when spawned
void AC_CharacterGenji::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	Pyo->AttachToComponent(DefaultMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Pyochang"));
	Long->AttachToComponent(DefaultMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LongSword"));
	Short->AttachToComponent(DefaultMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ShortSword"));

	JumpMaxCount = 2;
	curHp = maxHp;
	if (HasAuthority())
	{
		SetSkills();
		//CreatePyoChangs();
		LandedDelegate.AddDynamic(this , &AC_CharacterGenji::PlayLandSoundD);
	}
	leftPyoChangCount = maxPyoChangCount;

	AController* tmp = Cast<AController>(GetController());
	if ( tmp && tmp->IsLocalPlayerController() )
	{
		mainWidget = Cast<UC_BaseWidget>(CreateWidget(GetWorld(), mainWidgetClass));
		mainWidget->AddToViewport(1);
		mainWidget->SetWidget(this);
		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: SetWidget"), *GetActorNameOrLabel())
		,true, true, FColor::MakeRandomColor(), 10.0f);*/
	}

	// 발사하기 위한 기본 세팅
	// 최종 도착 거리 확인 위해 잠깐 총알 소환
	AC_PyoChang* tmp1 = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass);
	pyoDistance = tmp1->totalDistance; // 속력 * 지속시간
	tmp1->Destroy();
}

void AC_CharacterGenji::SetSkills()
{
	FActorSpawnParameters actorParam;
	actorParam.Owner = this;

	skillLeftClick = GetWorld()->SpawnActor<AC_GenjiSkill_LeftClick>(skillLeftClickClass, actorParam);
	skillRightClick = GetWorld()->SpawnActor<AC_GenjiSkill_RightClick>(skillRightClickClass , actorParam);
	skillQ = GetWorld()->SpawnActor<AC_GenjiSkill_Q>(skillQClass, actorParam);
	QCollider->OnComponentBeginOverlap.AddDynamic(skillQ, &AC_GenjiSkill_Q::OnHitBeginOverlap);
	skillLeftShift = GetWorld()->SpawnActor<AC_GenjiSkill_LeftShift>(skillLeftShiftClass, actorParam);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(skillLeftShift, &AC_GenjiSkill_LeftShift::OnHitBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(skillLeftShift, &AC_GenjiSkill_LeftShift::OnCollisionHit);
	skillE = GetWorld()->SpawnActor<AC_GenjiSkill_E>(skillEClass, actorParam);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(skillE, &AC_GenjiSkill_E::OnHitBeginOverlap);
	skillReload = GetWorld()->SpawnActor<AC_GenjiSkill_Reload>(skillReloadClass , actorParam);
	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: SetSkill_"), *GetActorNameOrLabel())
	//	,true, true, FColor::MakeRandomColor(), 10.0f);
	//skillLeftClick = GetWorld()->SpawnActor<AC_PyoChang>(skillLeftClickClass, actorParam);
}

void AC_CharacterGenji::CreatePyoChangs()
{
	for (int32 i = 0; i < maxPyoChangCount; i++)
	{
		FActorSpawnParameters actorParam;
		actorParam.Owner = this;

		AC_PyoChang* tmp = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass, actorParam);
		//tmp->SetActive(false);
		PyoChangs.Add(tmp);
	}
	leftPyoChangCount = maxPyoChangCount;
}

// Called every frame
void AC_CharacterGenji::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( bDie )
	{
		if ( SpringArm->SocketOffset.Y > 0.0f )
		{
			SpringArm->SocketOffset.Y -= 3.0f;
		}
		else if ( SpringArm->SocketOffset.Y <= 0.0f )
		{
			SpringArm->SocketOffset.Y = 0.0f;
		}
		
	}
	GenjiClimb(DeltaTime);
	//PlayLandSound();

	
}

// Called to bind functionality to input
void AC_CharacterGenji::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AC_CharacterGenji::GenjiJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_CharacterGenji::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_CharacterGenji::Look);

		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AC_CharacterGenji::LeftClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Triggered, this, &AC_CharacterGenji::LeftClick);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &AC_CharacterGenji::RightClick);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Triggered , this, &AC_CharacterGenji::RightClick);
		EnhancedInputComponent->BindAction(EAction, ETriggerEvent::Started, this, &AC_CharacterGenji::ESkill);
		EnhancedInputComponent->BindAction(LeftShiftAction, ETriggerEvent::Started, this, &AC_CharacterGenji::LeftShift);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AC_CharacterGenji::Reload);
		//EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AC_CharacterGenji::ClientReload); // 테스트 용
		EnhancedInputComponent->BindAction(QAction, ETriggerEvent::Started, this, &AC_CharacterGenji::QSkill);
	}
}

void AC_CharacterGenji::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AC_CharacterGenji, PyoChangs);
	DOREPLIFETIME(AC_CharacterGenji, leftPyoChangCount);
	DOREPLIFETIME(AC_CharacterGenji, skillLeftClick);
	DOREPLIFETIME(AC_CharacterGenji, skillRightClick);
	DOREPLIFETIME(AC_CharacterGenji, skillLeftShift);
	DOREPLIFETIME(AC_CharacterGenji, skillQ);
	DOREPLIFETIME(AC_CharacterGenji, skillE);
	DOREPLIFETIME(AC_CharacterGenji, skillReload);
	DOREPLIFETIME(AC_CharacterGenji, bCanAirJump);
	DOREPLIFETIME(AC_CharacterGenji, bDrangonSowrd);
	DOREPLIFETIME(AC_CharacterGenji, bIsClimb);
	DOREPLIFETIME(AC_CharacterGenji, bIsClimbFinish);
	DOREPLIFETIME(AC_CharacterGenji, climbStartLocation);
	DOREPLIFETIME(AC_CharacterGenji, lerpAlpha);
	DOREPLIFETIME(AC_CharacterGenji, actionState);
	
}

float AC_CharacterGenji::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if ( !HasAuthority() ) return 0;
	
	AC_BaseBullet* tmpBullet = Cast<AC_BaseBullet>(DamageCauser);
	if ( tmpBullet && skillE && skillE->bESkillOn ) return 0; // 총알 반사시 리턴
	
	float tmpDam = Super::TakeDamage(DamageAmount , DamageEvent , EventInstigator , DamageCauser);
	ClientSetCurHp(curHp, maxHp);
	return tmpDam;
}

void AC_CharacterGenji::CharacterDie()
{
	Super::CharacterDie();
	/*UKismetSystemLibrary::PrintString(GetWorld() ,
		FString::Printf(TEXT("%s: GenjiDie") , *GetActorNameOrLabel())
		, true , true , FColor::MakeRandomColor() , 5.0f);*/
	MulGenjiDie();
}

void AC_CharacterGenji::MulGenjiDie_Implementation()
{
	bDie = true;
	DefaultMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DefaultMesh->SetSimulatePhysics(true);
	DefaultMesh->SetCollisionProfileName(TEXT("Ragdoll"));
	DefaultMesh->SetNotifyRigidBodyCollision(true);
	Pyo->SetHiddenInGame(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpringArm->bDoCollisionTest = false;
	UGameplayStatics::PlaySoundAtLocation(GetWorld() , DieSound, GetActorLocation() , 1.0f , 1.0f , 0.0f , Attenuation);

	/*UKismetSystemLibrary::PrintString(GetWorld() ,
		FString::Printf(TEXT("%s: GenjiDie") , *GetActorNameOrLabel())
		, true , true , FColor::MakeRandomColor() , 5.0f);*/
}

void AC_CharacterGenji::PlayLandSound()
{
	if ( GetMovementComponent()->IsFalling() )
	{
		bCanPlayLandSound = true;
	}
	else if ( bCanPlayLandSound == true)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LandSound, GetActorLocation(), 1.0f, 1.0f, 0.0f, Attenuation);
		bCanPlayLandSound = false;
	}
	
}

void AC_CharacterGenji::PlayLandSoundD(const FHitResult& Hit)
{
	if ( !HasAuthority() ) return;
	
	MulPlaySound(LandSound , GetActorLocation());
	/*UGameplayStatics::PlaySoundAtLocation(GetWorld() , LandSound , GetActorLocation() , 0.5f , 1.0f , 0.0f , Attenuation);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: LandSound"), *GetActorNameOrLabel())
					, true, true, FColor::MakeRandomColor(), 10.0f);*/
}

void AC_CharacterGenji::GenjiClimb(float _Delta)
{
	if ( bThrowPyo )
	{
		//Pyo->SetWorldLocation(DefaultMesh->GetBoneLocation(TEXT("bone_003A")));
		//Pyo->SetWorldRotation(DefaultMesh->GetBoneQuaternion(TEXT("bone_003A")));
		Pyo->SetWorldLocation(DefaultMesh->GetSocketLocation(TEXT("RightHandPyo")));
		Pyo->SetWorldRotation(DefaultMesh->GetSocketRotation(TEXT("RightHandPyo")));

	}
	else if ( bPyoReload )
	{
		Pyo->SetWorldLocation(DefaultMesh->GetSocketLocation(TEXT("RArmPyo")));
		Pyo->SetWorldRotation(DefaultMesh->GetSocketRotation(TEXT("RArmPyo")));
	}
	else if ( bIsClimb )
	{
		// 서버에서만 체크
		if ( HasAuthority() )
		{
			tmpClimbTime += _Delta;
			if ( tmpClimbTime >= climbTime )
			{
				tmpClimbTime = 0.0f;
				bIsClimb = false;
				MulGenjiClimbStopWithMovement();
				/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: ClimbStop_Duration"), *GetActorNameOrLabel())
					, true, true, FColor::MakeRandomColor(), 10.0f);*/
				return;
			}

			// 벽 끝자락 도달
			FHitResult tmpHitResult;
			FVector start = GetActorLocation();
			start.Z += 80.0f;
			FVector end = start + GetActorForwardVector() * 53.0f;
			GetWorld()->LineTraceSingleByChannel(tmpHitResult , start , end , ECollisionChannel::ECC_Visibility);
			if ( !tmpHitResult.bBlockingHit )
			{
				bIsClimbFinish = true;

				tmpClimbTime = 0.0f;
				bIsClimb = false;
				MulGenjiClimbStop();

				// 벽 끝자락에서 위로 올라가기
				lerpAlpha = 0.0f;
				climbStartLocation = GetActorLocation();
				// 다음 틱 전에, 한 번 올라가기(여기서 안올라가면 한 틱 가만히 있기 때문)
				lerpAlpha += _Delta * 5.0f; // 지속 시간 만큼
				FVector tmpLocation = FMath::Lerp(climbStartLocation , climbStartLocation + FVector(0.0f , 0.0f , 1.0f) * climeFinishDistance , lerpAlpha);
				SetActorLocation(tmpLocation);
				return;
			}
			// 머리 위 장애물
			FVector lastPos = GetActorLocation();
			start = GetActorLocation();
			end = start;
			end.Z += 90.0f;
			FHitResult tmpHitResult2;
			GetWorld()->LineTraceSingleByChannel(tmpHitResult2 , start , end , ECollisionChannel::ECC_Visibility);
			if ( tmpHitResult2.bBlockingHit )
			{
				tmpClimbTime = 0.0f;
				bIsClimb = false;
				MulGenjiClimbStopWithMovement();
				/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: ClimbStop_Head"), *GetActorNameOrLabel())
					, true, true, FColor::MakeRandomColor(), 10.0f);*/
				return;
			}
		}

		// 충돌 없으면 위치 증가 -> Set으로 변경
		//AddActorWorldOffset(FVector(0.0f, 0.0f, climeSpeed));
		lerpAlpha += _Delta; // 지속 시간 만큼
		if ( lerpAlpha >= 1.0f )
		{
			lerpAlpha = 1.0f;
		}
		FVector tmpLocation = FMath::Lerp(climbStartLocation , climbStartLocation + FVector(0.0f , 0.0f , 1.0f) * climeDistance , lerpAlpha);
		SetActorLocation(tmpLocation);
		return;

	}
	else if ( bIsClimbFinish )
	{
		// 서버에서만 체크
		if ( HasAuthority() )
		{
			tmpClimbFinishTime += _Delta;
			if ( tmpClimbFinishTime >= climbFinishTime )
			{
				bIsClimbFinish = false;
				tmpClimbFinishTime = 0.0f;
				//MulGenjiClimbStopWithMovement();
				MulGenjiClimbStopWithMovementEnd(); // 끝자락 도달하고 올라간뒤 알아서 앞으로
				return;
			}
			// 머리 위 장애물
			FVector lastPos = GetActorLocation();
			FVector start = GetActorLocation();
			FVector end = start;
			end.Z += 90.0f;
			FHitResult tmpHitResult2;
			GetWorld()->LineTraceSingleByChannel(tmpHitResult2 , start , end , ECollisionChannel::ECC_Visibility);
			if ( tmpHitResult2.bBlockingHit )
			{
				tmpClimbFinishTime = 0.0f;
				bIsClimbFinish = false;
				MulGenjiClimbStopWithMovement();
				return;
			}
		}

		// 충돌 없으면 위치 증가
		lerpAlpha += _Delta * 5; // 지속 시간 만큼
		if ( lerpAlpha >= 1.0f )
		{
			lerpAlpha = 1.0f;
		}
		FVector tmpLocation = FMath::Lerp(climbStartLocation , climbStartLocation + FVector(0.0f , 0.0f , 1.0f) * climeFinishDistance , lerpAlpha);
		SetActorLocation(tmpLocation);
		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: AlphaTime = %f"), *GetActorNameOrLabel(), lerpAlpha)
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
	}
}

void AC_CharacterGenji::Move(const FInputActionValue& Value)
{
	if ( (skillLeftShift && skillLeftShift->skillOn) || bIsClimb || bDie ) return;
	
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

float AC_CharacterGenji::GetQGauge()
{
	if ( skillQ )
	{
		return skillQ->gauge;
	}
	return 0;
}

FVector AC_CharacterGenji::FireReady()
{
	// 카메라와 발사위치까지의 거리 구하기
	FVector CamPos = Camera->GetComponentLocation(); // 카메라 위치
	FVector CamForward = Camera->GetForwardVector(); // 카메라 앞 단위벡터
	FVector muzzlePos = GetActorTransform().TransformPosition(pyoMuzzle); // 발사 위치 = 총구의 월드 위치
	FVector tmpV = muzzlePos - CamPos; // 카메라에서 총구까지의 벡터
	float camToStartDistance = FVector::DotProduct(CamForward , tmpV); // 발사위치와 카메라의 깊이 구하기
	// 총구가 카메라 전방으로 얼마나 떨어져 있는지(깊이)를 구함

	FHitResult tmpHit;
	// 카메라 조준선 상의 총구 깊이 위치에 있는 점
	FVector start = CamPos + CamForward * camToStartDistance; // 발사 위치와 같은 깊이에서 시작
	// 총구와 Start 간의 거리
	//float startToMz = ( start - muzzlePos ).Length();
	float startToMz = FVector::Distance(start, muzzlePos);
	// 피타고라스의 정리로 표창이 날아갈 직선 거리 계산
	// 표창 비행 거리 = pyoDistance, 총구와 Start 간의 거리 = startToMz
	float startToEndDistance = FMath::Sqrt(FMath::Square(pyoDistance) - FMath::Square(startToMz));
	// 조준선 상 최종 목표 지점 
	FVector end = CamPos + CamForward * ( startToEndDistance + camToStartDistance );

	FCollisionQueryParams tmpCP;
	tmpCP.AddIgnoredActor(this); // 자기 자신 제외하기, 3인칭이라 가끔 자기 자신 맞음
	GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera , tmpCP);
	//// 디버그용
	//bool btmpB = GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera , tmpCP);
	//float debugTime = 6.0f;
	//if ( btmpB ) // 맞았으면 디버그 라인 2개
	//{
	//	DrawDebugLine(GetWorld(), start, tmpHit.Location, FColor::Red, false, debugTime, 0, 1.0f);
	//	DrawDebugLine(GetWorld(), tmpHit.Location, end, FColor::Green, false, debugTime, 0, 1.0f);
	//}
	//else
	//{
	//	DrawDebugLine(GetWorld(), start, end, FColor::Green, false, debugTime , 0, 1.0f);
	//}
	//// 카메라와 발사 위치까지의 거리
	//DrawDebugLine(GetWorld(), CamPos, muzzlePos , FColor::Black, false , debugTime , 0 , 1.0f);
	//// 발사위치와 카메라의 깊이 거리
	//DrawDebugLine(GetWorld(), start , CamPos, FColor::Emerald , false , debugTime , 0 , 1.0f);
	//// 레이 캐스트 시작 위치와 발사 위치 거리
	//DrawDebugLine(GetWorld() , start , muzzlePos , FColor::Cyan , false , debugTime , 0 , 1.0f);
	//// 발사 위치부터 레이 캐스트 맞은 위치까지
	//DrawDebugLine(GetWorld() , muzzlePos , btmpB ? tmpHit.Location : end , FColor::Blue , false , debugTime , 0 , 1.0f);
	
	FVector direction;
	if ( tmpHit.bBlockingHit )
	{
		direction = ( tmpHit.Location - muzzlePos ).GetSafeNormal();
	}
	else
	{
		direction = ( end - muzzlePos ).GetSafeNormal();
	}
	return direction;
}

void AC_CharacterGenji::FirePyoForClient()
{
	if ( leftPyoChangCount == 0 ) return;
	/*FActorSpawnParameters actorParam;
	actorParam.Owner = this;

	AC_PyoChang* tmp = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass , actorParam);
	tmp->FirePyoChangQuick();
	leftPyoChangCount--;
	if ( !HasAuthority() ) return;
	ClientSetLeftPyoChang(leftPyoChangCount);*/
	/*FVector tmpV = DefaultMesh->GetSocketLocation(FName("RightHandPyo"));
	SerFIrePyo(tmpV, GetControlRotation(), FireReady());*/

	//FVector muzzle = GetActorTransform().TransformPosition(FVector(75.0f , 10.0f , 10.0f));
	FVector muzzle = GetActorTransform().TransformPosition(pyoMuzzle);

	SerFIrePyo(muzzle, GetControlRotation(), FireReady());
}
void AC_CharacterGenji::FirePyoForClientR()
{
	if ( leftPyoChangCount == 0 ) return;
	//FActorSpawnParameters actorParam;
	//actorParam.Owner = this;

	//AC_PyoChang* tmp1 = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass , GetActorLocation() + GetActorForwardVector() * 100.0f , GetControlRotation() , actorParam);
	//AC_PyoChang* tmp2 = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass , GetActorLocation() + GetActorForwardVector() * 100.0f , GetControlRotation() , actorParam);
	//AC_PyoChang* tmp3 = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass , GetActorLocation() + GetActorForwardVector() * 100.0f , GetControlRotation() , actorParam);

	//// 카메라와 발사위치까지의 거리 구하기
	//FVector CamPos = Camera->GetComponentLocation();
	//FVector AcPos = GetActorLocation() + GetActorForwardVector() * 100.0f;
	//FVector tmpV = AcPos - CamPos;

	//float tmpDistance = ( FVector::DotProduct(tmpV , Camera->GetForwardVector()) );

	//FHitResult tmpHit;
	//FVector start = Camera->GetComponentLocation() + Camera->GetForwardVector() * tmpDistance;
	//FVector end = Camera->GetComponentLocation() + Camera->GetForwardVector() * 10000.0f; // 추후 아래에 있는 거리로 바꿀 수 있음

	//FCollisionQueryParams tmpCP;
	//tmpCP.AddIgnoredActor(this);
	//GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera , tmpCP);

	//FVector direction;
	//if ( tmpHit.bBlockingHit )
	//{
	//	direction = ( tmpHit.Location - tmp1->GetActorLocation() ).GetSafeNormal();
	//}
	//else
	//{
	//	//direction = player->Camera->GetForwardVector();
	//	direction = ( ( Camera->GetComponentLocation() + Camera->GetForwardVector() * ( tmp1->totalDistance + tmpDistance ) ) - tmp1->GetActorLocation() ).GetSafeNormal();
	//	//direction = ( ( GetActorLocation() + Camera->GetForwardVector() * tmp1->totalDistance ) - GetActorLocation() ).GetSafeNormal();
	//	//direction = ( ( GetActorLocation() + Camera->GetForwardVector() * tmp1->totalDistance ) - GetActorLocation() ).GetSafeNormal();
	//}
	//tmp1->FirePyoChang(direction);

	//FRotator tmpRot = direction.Rotation();
	//tmpRot.Yaw += 7.0f;
	//direction = tmpRot.Vector();
	//tmp2->FirePyoChang(direction);

	//tmpRot.Yaw -= 14.0f;
	//direction = tmpRot.Vector();
	//tmp3->FirePyoChang(direction);

	//leftPyoChangCount -= 3;
	//if ( !HasAuthority() ) return;
	//ClientSetLeftPyoChang(leftPyoChangCount);

	//FVector muzzle = GetActorTransform().TransformPosition(FVector(75.0f, 10.0f, 10.0f));
	FVector muzzle = GetActorTransform().TransformPosition(pyoMuzzle);

	FVector direction = FireReady();
	//SerFIrePyo(GetActorLocation() + GetActorForwardVector() * 75.0f , GetControlRotation() , direction);
	SerFIrePyo(muzzle, GetControlRotation() , direction);
	FRotator tmpRot = direction.Rotation();
	tmpRot.Yaw += 7.0f;
	direction = tmpRot.Vector();
	//SerFIrePyo(GetActorLocation() + GetActorForwardVector() * 75.0f , GetControlRotation() , direction);
	SerFIrePyo(muzzle, GetControlRotation() , direction);

	tmpRot.Yaw -= 14.0f;
	direction = tmpRot.Vector();
	//SerFIrePyo(GetActorLocation() + GetActorForwardVector() * 75.0f , GetControlRotation() , direction);
	SerFIrePyo(muzzle, GetControlRotation() , direction);

	
}

void AC_CharacterGenji::SerFIrePyo_Implementation(const FVector& _Location , const FRotator& _Rotator , const FVector& _Direction)
{
	//FActorSpawnParameters actorParam;
	//actorParam.Owner = this;

	//AC_PyoChang* tmpPyo = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass , _Location , _Rotator , actorParam);
	//tmpPyo->MulSetActive(true, _Direction);
	////tmpPyo->SerFirePyoChang(_Direction);
	//leftPyoChangCount--;
	//if ( !HasAuthority() ) return;
	//ClientSetLeftPyoChang(leftPyoChangCount);

	////////// 아래 원본
	MulFIrePyo(_Location , _Rotator , _Direction);

}

void AC_CharacterGenji::MulFIrePyo_Implementation(const FVector& _Location , const FRotator& _Rotator , const FVector& _Direction)
{
	FActorSpawnParameters actorParam;
	actorParam.Owner = this;

	AC_PyoChang* tmpPyo = GetWorld()->SpawnActor<AC_PyoChang>(PyoChangClass , _Location , _Rotator , actorParam);
	tmpPyo->FirePyoChang(_Direction);
	leftPyoChangCount--;
	//if ( !Controller->IsLocalPlayerController() ) return;
	if ( !HasAuthority() ) return;
	ClientSetLeftPyoChang(leftPyoChangCount);

}

void AC_CharacterGenji::ClientSetCurHp_Implementation(float _curHp , float _maxHp)
{
	mainWidget->SetHp(_curHp , _maxHp);
}

void AC_CharacterGenji::ClientSetLeftPyoChang_Implementation(int32 _leftPyoChangCount)
{
	mainWidget->SetBullet(_leftPyoChangCount);
}

void AC_CharacterGenji::Look(const FInputActionValue& Value)
{
	if ( (skillLeftShift && skillLeftShift->skillOn) || bIsClimb || bDie ) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		SAForSkillQ->SetWorldRotation(GetControlRotation());
	}
}

void AC_CharacterGenji::ResetPyoLocation()
{
	Pyo->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Pyo->SetRelativeRotation(FRotator(0.0f , 0.0f , 0.0f));
}

void AC_CharacterGenji::LeftClick_Implementation()
{
	if ((leftPyoChangCount == 0 && !bDrangonSowrd ) || !bCanAttack || bIsClimb || skillRightClick->isCoolTime || bDie ) return;
	
	if (bDrangonSowrd)
	{
		skillQ->DragonSlash();
		return;
	}
	/*else
	{
		UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
		if ( AnimInstance->Montage_IsPlaying(skillQ->QEndMotion) ) return;
	}*/
	/*UKismetSystemLibrary::PrintString(GetWorld() ,
		FString::Printf(TEXT("%s: %d") , *GetActorNameOrLabel(), bCanAttack)
		, true , true , FColor::MakeRandomColor() , 5.0f);*/
	skillLeftClick->UseSkill();

}

void AC_CharacterGenji::RightClick_Implementation()
{
	if ( ( leftPyoChangCount == 0 && !bDrangonSowrd ) || !bCanAttack || bIsClimb || skillLeftClick->isCoolTime || bDie ) return;
	if (bDrangonSowrd)
	{
		skillQ->DragonSlash();
		return;
	}
	/*else
	{
		UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
		if ( AnimInstance->Montage_IsPlaying(skillQ->QEndMotion) ) return;
	}*/
	skillRightClick->UseSkill();
}

void AC_CharacterGenji::ESkill_Implementation()
{
	if (!bCanAttack || bIsClimb || bDie ) return;
	/*if ( !bDrangonSowrd )
	{
		UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
		if ( AnimInstance->Montage_IsPlaying(skillQ->QEndMotion) ) return;
	}*/
	skillE->UseSkill();
}

void AC_CharacterGenji::LeftShift_Implementation()
{
	if (!bCanAttack || bIsClimb || bDie ) return;
	/*if ( !bDrangonSowrd )
	{
		UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
		if ( AnimInstance->Montage_IsPlaying(skillQ->QEndMotion) ) return;
	}*/
	bIsClimbFinish = false;
	tmpClimbFinishTime = 0.0f;
	skillLeftShift->UseSkill();
}

void AC_CharacterGenji::Reload_Implementation()
{
	if (!bCanAttack || bIsClimb || bDrangonSowrd || bDie ) return;
	/*if ( !bDrangonSowrd )
	{
		UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
		if ( AnimInstance->Montage_IsPlaying(skillQ->QEndMotion) ) return;
	}*/
	skillReload->UseSkill();
}

void AC_CharacterGenji::QSkill_Implementation()
{
	if (!bCanAttack || bDrangonSowrd || bIsClimb || bDie ) return;
	skillQ->UseSkill();

}

void AC_CharacterGenji::ClientReload()
{
	if ( !skillReload ) return;
	UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: Reload") , *GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 10.0f);
	skillReload->SerTestUseSkill();
}

void AC_CharacterGenji::GenjiJump()
{
	if (bIsClimb || bIsClimbFinish || bDie ) return;
	// 벽타기
	FHitResult tmpHit;
	FVector start = GetActorLocation();
	start.Z -= 45.0f;
	FVector end = GetActorLocation() + GetActorForwardVector() * 53.0f;
	GetWorld()->LineTraceSingleByChannel(tmpHit, start, end, ECollisionChannel::ECC_Visibility);
	//if (tmpHit.bBlockingHit && Cast<AStaticMeshActor>(tmpHit.GetActor()))
	if (tmpHit.bBlockingHit)
	{
		//if ( !bDrangonSowrd )
		//{
		//	UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
		//	if ( AnimInstance->Montage_IsPlaying(skillQ->QEndMotion) ) return;
		//	else
		//	{
		//		Jump();

		//		if ( JumpCurrentCount == 1 ) // 컴터에 따라 점프 카운트 달라질 수 있다???
		//			//if (JumpCurrentCount > 1) // 컴터에 따라 점프 카운트 달라질 수 있다???
		//		{
		//			SetGenjiAirJump();
		//			FVector tmpVel = GetCharacterMovement()->Velocity;
		//			if ( tmpVel.Z < 0.0f )
		//			{
		//				tmpVel.Z = 0.0f;
		//			}
		//			GetCharacterMovement()->Velocity = tmpVel;
		//		}
		//	}
		//}
		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: Climb--- %s"), *GetActorNameOrLabel(), *tmpHit.GetActor()->GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
		GetCharacterMovement()->bApplyGravityWhileJumping = false;
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
		climbStartLocation = GetActorLocation();
		lerpAlpha = 0.0f;
		GenjiClimb();
	}
	else
	{
		Jump();
		
		if (JumpCurrentCount == 1) // 컴터에 따라 점프 카운트 달라질 수 있다???
		//if (JumpCurrentCount > 1) // 컴터에 따라 점프 카운트 달라질 수 있다???
		{
			SetGenjiAirJump();
			FVector tmpVel = GetCharacterMovement()->Velocity;
			if ( tmpVel.Z < 0.0f )
			{
				tmpVel.Z = 0.0f;
			}
			GetCharacterMovement()->Velocity = tmpVel;
		}
	}
}
void AC_CharacterGenji::MulGenjiClimbStopWithMovementEnd_Implementation()
{
	UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
	AnimInstance->Montage_Stop(0.0f);
	FVector tmp = GetActorForwardVector() * 200.0f;
	GetCharacterMovement()->Velocity = tmp;
	GetCharacterMovement()->bApplyGravityWhileJumping = true;
	GetCharacterMovement()->GravityScale = 3.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
}
void AC_CharacterGenji::MulGenjiClimbStopWithMovement_Implementation()
{
	UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
	AnimInstance->Montage_Stop(0.0f);
	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, -1.0f);
	GetCharacterMovement()->bApplyGravityWhileJumping = true;
	GetCharacterMovement()->GravityScale = 3.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
}

void AC_CharacterGenji::MulGenjiClimbStop_Implementation()
{
	UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
	AnimInstance->Montage_Stop(0.0f);
}

void AC_CharacterGenji::GenjiClimbStop_Implementation()
{
	MulGenjiClimbStop();
}

void AC_CharacterGenji::GenjiClimb_Implementation()
{
	GetCharacterMovement()->bApplyGravityWhileJumping = false;
	GetCharacterMovement()->GravityScale = 0.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	climbStartLocation = GetActorLocation();
	lerpAlpha = 0.0f;
	switch (actionState)
	{
	case EActionState::Sword:
		MulPlayMontage(ClimbMotionQ);
		break;
	case EActionState::PyoChang:
		MulPlayMontage(ClimbMotion);
		break;
	default:
		break;
	}
	bIsClimb = true;
}

void AC_CharacterGenji::MulPlayMontage_Implementation(UAnimMontage* MontageToPlay, float InPlayRate)
{
	UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
	if (MontageToPlay && AnimInstance)
		AnimInstance->Montage_Play(MontageToPlay, InPlayRate);
}

void AC_CharacterGenji::SetGenjiAirJump_Implementation()
{
	bCanAirJump = true;
	FVector tmpVel = GetCharacterMovement()->Velocity;
	if ( tmpVel.Z < 0.0f )
	{
		tmpVel.Z = 0.0f;
	}
	GetCharacterMovement()->Velocity = tmpVel;
}

void AC_CharacterGenji::MulStopMontage_Implementation(float _OutTime)
{
	UAnimInstance* AnimInstance = DefaultMesh->GetAnimInstance();
	AnimInstance->Montage_Stop(_OutTime);
}


