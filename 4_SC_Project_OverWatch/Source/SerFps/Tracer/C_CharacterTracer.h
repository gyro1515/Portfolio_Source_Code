#pragma once
#include "CharacterBase/C_BaseCharacter.h"
#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

#include "C_CharacterTracer.generated.h"

UCLASS()
class SERFPS_API AC_CharacterTracer : public AC_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_CharacterTracer();

	UPROPERTY(VisibleDefaultsOnly , BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly , BlueprintReadWrite)
	class UCameraComponent* Camera;

	/** MappingContext */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* LookAction;

public:
	//Tracer

	UPROPERTY(VisibleDefaultsOnly , Category = Mesh , BlueprintReadWrite)
	USkeletalMeshComponent* GunR;

	UPROPERTY(VisibleDefaultsOnly , Category = Mesh , BlueprintReadWrite)
	USkeletalMeshComponent* GunL;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* RightClickAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* LeftShiftAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* EAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = Input , meta = ( AllowPrivateAccess = "true" ))
	class UInputAction* QAction;


	//for Ult Ability
	float UltGauge = 0.0f;

	//for Blink Ability

	float ActionValueX;
	float ActionValueY;

	//for Recall Ability

	TArray<FTransform> RecallArray;

	int RecallIndex;
	float SaveTerm;

	UPROPERTY(BlueprintReadOnly)
	bool isRecalling;

	UPROPERTY(EditDefaultsOnly , Category = "Skill")
	int MaxRecallIndex = 300;

	UPROPERTY(EditDefaultsOnly , Category = "Skill")
	float BlinkDistance = 500.0f;


	//for basefire??
	bool isFiring;

	UPROPERTY(EditAnywhere , Category = Weapon)
	int32 maxBullet = 40;

	int32 curBullet = 40;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float TakeDamage(float DamageAmount , struct FDamageEvent const& DamageEvent ,
		class AController* EventInstigator , AActor* DamageCauser) override;

	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void TracerJump();

	//for Recall Ability
	void RecallRecord(float DeltaTime);

	void RightClick();

	void LeftClick();

	void ESkill();

	void QSkill();
};
