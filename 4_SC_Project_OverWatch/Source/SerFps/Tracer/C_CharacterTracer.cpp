#include "C_CharacterTracer.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AC_CharacterTracer::AC_CharacterTracer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GunR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightGun"));
	GunR->SetupAttachment(GetMesh());
	GunL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftGun"));
	GunL->SetupAttachment(GetMesh());

	GetCapsuleComponent()->ComponentTags.Add(FName("MainCol"));

	if ( HasAuthority() )
	{
		SetReplicates(true);
	}

}

// Called when the game starts or when spawned
void AC_CharacterTracer::BeginPlay()
{
	Super::BeginPlay();
	
	if ( APlayerController* PlayerController = Cast<APlayerController>(Controller) )
	{
		if ( UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()) )
		{
			Subsystem->AddMappingContext(DefaultMappingContext , 0);
		}
	}

	//GunL->AttachToComponent(GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , TEXT("bone_001C"));
	//GunR->AttachToComponent(GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , TEXT("bone_003A"));

	GunL->AttachToComponent(GetMesh() , FAttachmentTransformRules::SnapToTargetNotIncludingScale , TEXT("bone_001C"));
	GunR->AttachToComponent(GetMesh() , FAttachmentTransformRules::SnapToTargetNotIncludingScale , TEXT("bone_003A"));

}

// Called every frame
void AC_CharacterTracer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Recall Ability
	RecallRecord(DeltaTime);
}

// Called to bind functionality to input
void AC_CharacterTracer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if ( UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction , ETriggerEvent::Started , this , &AC_CharacterTracer::TracerJump);
		EnhancedInputComponent->BindAction(JumpAction , ETriggerEvent::Completed , this , &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction , ETriggerEvent::Triggered , this , &AC_CharacterTracer::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction , ETriggerEvent::Triggered , this , &AC_CharacterTracer::Look);

		//Skills
		EnhancedInputComponent->BindAction(LeftClickAction , ETriggerEvent::Started , this , &AC_CharacterTracer::LeftClick);
		EnhancedInputComponent->BindAction(RightClickAction , ETriggerEvent::Started , this , &AC_CharacterTracer::RightClick);
		EnhancedInputComponent->BindAction(EAction , ETriggerEvent::Started , this , &AC_CharacterTracer::ESkill);
		EnhancedInputComponent->BindAction(LeftShiftAction , ETriggerEvent::Started , this , &AC_CharacterTracer::LeftClick);
		//EnhancedInputComponent->BindAction(ReloadAction , ETriggerEvent::Started , this , &AC_CharacterGenji::Reload);
		EnhancedInputComponent->BindAction(QAction , ETriggerEvent::Started , this , &AC_CharacterTracer::QSkill);
	}

}

void AC_CharacterTracer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

float AC_CharacterTracer::TakeDamage(float DamageAmount , FDamageEvent const& DamageEvent , AController* EventInstigator , AActor* DamageCauser)
{
	return 0.0f;
}

void AC_CharacterTracer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if ( Controller != nullptr )
	{
		// add movement 
		AddMovementInput(GetActorForwardVector() , MovementVector.Y);
		AddMovementInput(GetActorRightVector() , MovementVector.X);

		ActionValueX = MovementVector.X;
		ActionValueY = MovementVector.Y;
	}

}

void AC_CharacterTracer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if ( Controller != nullptr )
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}

}

void AC_CharacterTracer::TracerJump()
{
	Jump();
}

void AC_CharacterTracer::RecallRecord(float DeltaTime)
{
	if ( isRecalling )
	{
		if ( RecallIndex >= 0 )
		{
			SetActorTransform(RecallArray[ RecallIndex ]);
			RecallIndex--;
		}
		else
		{
			isRecalling = false;
			RecallArray.Empty();
		}
	}
	else
	{
		if ( SaveTerm < 0.2f )
		{
			SaveTerm += DeltaTime;
			RecallArray.Add(GetActorTransform());
			SaveTerm = 0.0f;

			if ( RecallArray.Num() > MaxRecallIndex )
			{
				RecallArray.RemoveAt(0);
			}
		}
	}

}

void AC_CharacterTracer::RightClick()
{
	FVector tmp = ( GetActorRightVector() * ActionValueX ) + ( GetActorForwardVector() * ActionValueY );
	tmp.Normalize();
	tmp *= BlinkDistance;

	tmp = GetActorLocation() + tmp;

	SetActorLocation(tmp , true);
}

void AC_CharacterTracer::LeftClick()
{
}

void AC_CharacterTracer::ESkill()
{
	isRecalling = true;
	RecallIndex = RecallArray.Num() - 1;
}

void AC_CharacterTracer::QSkill()
{
}

