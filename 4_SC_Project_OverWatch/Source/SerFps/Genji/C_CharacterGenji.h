// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterBase/C_BaseCharacter.h"

#include "C_CharacterGenji.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UENUM(BlueprintType)
enum class EActionState : uint8
{
	Sword,
	PyoChang,
	ItemSkill
};

UCLASS()
class AC_CharacterGenji : public AC_BaseCharacter
//class AC_CharacterGenji : public ACharacter
{
	GENERATED_BODY()

public: // 기본 틀
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, BlueprintReadWrite)
	USkeletalMeshComponent* DefaultMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	// 스킬 Q용 스프링 암, 콜라이더
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SAForSkillQ;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* QCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	//리플리케이트 필요 능력치들: hp 등등
	//UPROPERTY(EditAnywhere, Category = Stat)
	//float maxHp;
	//UPROPERTY(Replicated)
	//float curHp;

public: // 추가 캐릭터 특징
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, BlueprintReadWrite)
	USkeletalMeshComponent* Pyo;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, BlueprintReadWrite)
	USkeletalMeshComponent* Long;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, BlueprintReadWrite)
	USkeletalMeshComponent* Short;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftShiftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QAction;

	/*UPROPERTY(EditAnywhere)
	class UAnimMontage* LeftClickMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* RightClickMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* LeftShiftMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* EMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ReloadMotion;*/

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ClimbMotion;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* ClimbMotionQ;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* ClimbMotionFinish;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* ClimbMotionQFinish;
	// 스킬
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_GenjiSkill_LeftClick> skillLeftClickClass;
	UPROPERTY(Replicated)
	class AC_GenjiSkill_LeftClick* skillLeftClick;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_GenjiSkill_RightClick> skillRightClickClass;
	UPROPERTY(Replicated)
	class AC_GenjiSkill_RightClick* skillRightClick;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_GenjiSkill_Q> skillQClass;
	UPROPERTY(Replicated)
	class AC_GenjiSkill_Q* skillQ;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_GenjiSkill_E> skillEClass;
	UPROPERTY(Replicated)
	class AC_GenjiSkill_E* skillE;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_GenjiSkill_LeftShift> skillLeftShiftClass;
	UPROPERTY(Replicated)
	class AC_GenjiSkill_LeftShift* skillLeftShift;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_GenjiSkill_Reload> skillReloadClass;
	UPROPERTY(Replicated)
	class AC_GenjiSkill_Reload* skillReload;

	// 상태 관련
	UPROPERTY(BlueprintReadWrite)
	bool bThrowPyo;
	UPROPERTY(BlueprintReadWrite)
	bool bPyoReload;

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool bCanAirJump;

	UPROPERTY(BlueprintReadWrite, Replicated)
	EActionState actionState = EActionState::PyoChang;

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool bDrangonSowrd = false;

	bool bCanAttack = true;

	bool bCanPlayLandSound = false;
	// 벽타기
	UPROPERTY(BlueprintReadWrite, Replicated)
	bool bIsClimb = false;
	UPROPERTY(EditAnywhere, Category = Climb)
	float climbTime = 1.0f;
	float tmpClimbTime = 0.0f;
	UPROPERTY(BlueprintReadWrite, Replicated)
	bool bIsClimbFinish = false;
	UPROPERTY(EditAnywhere, Category = Climb)
	float climbFinishTime = 0.2f;
	float tmpClimbFinishTime = 0.0f;
	UPROPERTY(EditAnywhere, Category = Climb)
	float climeSpeed = 40.0f;
	UPROPERTY(EditAnywhere, Category = Climb)
	float climeFinishSpeed = 50.0f;
	UPROPERTY(EditAnywhere , Category = Climb)
	float climeDistance = 780.0f;
	UPROPERTY(EditAnywhere , Category = Climb)
	float climeFinishDistance = 300.0f;
	UPROPERTY(Replicated)
	FVector climbStartLocation;
	UPROPERTY(Replicated)
	float lerpAlpha = 0.0f;
	// 랜딩
	UPROPERTY(EditAnywhere)
	class USoundBase* LandSound;
	UPROPERTY(EditAnywhere)
	class USoundBase* DieSound;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class AC_PyoChang> PyoChangClass;
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<class AC_PyoChang*> PyoChangs;
	UPROPERTY(EditAnywhere, Category = Weapon)
	int32 maxPyoChangCount;
	UPROPERTY(Replicated)
	int32 leftPyoChangCount;
	
	// 머즐
	UPROPERTY(EditAnywhere)
	FVector pyoMuzzle;

	// 위젯
	UPROPERTY(EditAnywhere , Category = "Widget")
	TSubclassOf<UUserWidget> mainWidgetClass;
	UPROPERTY(VisibleAnywhere , Category = "Widget")
	class UC_BaseWidget* mainWidget;

public:
	// Sets default values for this character's properties
	AC_CharacterGenji();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSkills();
	void CreatePyoChangs();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
	// 죽을시
	virtual void CharacterDie() override;
	UFUNCTION(NetMulticast , Reliable)
	void MulGenjiDie();

	void PlayLandSound();
	UFUNCTION()
	void PlayLandSoundD(const FHitResult& Hit);

	void GenjiClimb(float _Delta);

	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	// 표창 위치 리셋
	void ResetPyoLocation();
	UFUNCTION(Server, Reliable)
	void LeftClick();
	UFUNCTION(Server, Reliable)
	void RightClick();
	UFUNCTION(Server, Reliable)
	void ESkill();
	UFUNCTION(Server, Reliable)
	void LeftShift();
	UFUNCTION(Server, Reliable)
	void Reload();

	void ClientReload();
	UFUNCTION(Server, Reliable)
	void QSkill();
	// 벽타기
	void GenjiJump();
	UFUNCTION(Server, Reliable)
	void GenjiClimb();
	UFUNCTION(Server, Reliable)
	void GenjiClimbStop();
	UFUNCTION(NetMulticast, Reliable)
	void MulGenjiClimbStop();
	UFUNCTION(NetMulticast, Reliable)
	void MulGenjiClimbStopWithMovement();
	UFUNCTION(NetMulticast , Reliable)
	void MulGenjiClimbStopWithMovementEnd();
	// 더블 점프
	UFUNCTION(Server, Reliable)
	void SetGenjiAirJump();
	// 멀티캐스트 몽타주
	UFUNCTION(NetMulticast, Reliable)
	void MulPlayMontage(UAnimMontage* MontageToPlay, float InPlayRate = 1.0f);
	UFUNCTION(NetMulticast, Reliable)
	void MulStopMontage(float _OutTime = 0.0f);
	// 게이지 세팅용도, Q게이지 가져오기
	float GetQGauge();
	// 위젯 세팅용 클라이언트 함수, 
	UFUNCTION(Client , Reliable)
	void ClientSetLeftPyoChang(int32 _leftPyoChangCount);
	UFUNCTION(Client , Reliable)
	void ClientSetCurHp(float _curHp, float _maxHp);
	// 애님 그래프 2단 점프용
	bool IsCanAirJump() { return bCanAirJump; }
	// 클라마다 총알 소환 및 발사
	FVector FireReady();
	void FirePyoForClient();
	void FirePyoForClientR();
	// 불렛 발사시 클라에서 서버로 전달하는 함수
	UFUNCTION(Server , Reliable)
	void SerFIrePyo(const FVector& _Location, const FRotator& _Rotator, const FVector& _Direction);
	UFUNCTION(NetMulticast , Reliable)
	void MulFIrePyo(const FVector& _Location , const FRotator& _Rotator , const FVector& _Direction);
};
