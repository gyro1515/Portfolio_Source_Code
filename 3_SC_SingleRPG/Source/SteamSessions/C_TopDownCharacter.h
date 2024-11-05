// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Item/CItemStrut.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CUW_CharacterOverHead.h"
#include "Skill/C_Attack.h"

#include "C_TopDownCharacter.generated.h"

UCLASS(Blueprintable)
class STEAMSESSIONS_API AC_TopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	AC_TopDownCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RPCRoll();

	
	UFUNCTION()
	void SetCharacterName(const FString& name);


	//UFUNCTION(Server, Reliable, BlueprintCallable)
	UFUNCTION()
	void TakeDamage(float damageamount);

	UFUNCTION()
	void RecoveryHP(float hp);
	UFUNCTION()
	void RecoveryMP(float mp);


	//UFUNCTION(NetMulticast, Reliable , BlueprintCallable)
	UFUNCTION(BlueprintCallable)
	void UpdateHpPercent(float curHp, float maxHp);

	//skills
	UFUNCTION()
	void RPCAttack(UAnimMontage* AttackMon);

protected:

public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* RollMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* MeleeMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* QMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* WMotion;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* EMotion;



	//attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class AC_SlashAttack> SlashAttackClass;

private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//
	//class UDecalComponent* Decal;

	// 미니맵

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MinimapBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* MinimapCam;



private:

	//Over Head UI
	//UPROPERTY()
	//TSubclassOf<UCUW_CharacterOverHead> OverHeadUIClass;
	//UCUW_CharacterOverHead* OverHeadUI;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* OverHeadUI;

	//위젯 빌보드용
	class AC_TopDownController* MainController;
	class AC_TopDownViewPawn* MainPawn;
public:

	UPROPERTY(VisibleAnywhere)
	FString CharacterName ;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float CharacterHp = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CharacterMaxHp = 100.0f;

public:	
	
	// 240529 스킬 형식 변경
	void UseSkill_Q();
	void UseSkill_E();
	void UseSkill_W();

	class AC_SkillManager* SkillManager;

	//class AC_Attack* Q;
	//class AC_Attack* W;
	//class AC_Attack* E;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* dataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<class AC_SkillManager> SkillManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName Q_AttackName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName W_AttackName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName E_AttackName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName A_AttackName;

	FAttackBaseC* q_AttackBase;
	FAttackBaseC* w_AttackBase;
	FAttackBaseC* e_AttackBase;
	FAttackBaseC* a_AttackBase;
	// 240611 포인터 구조체 말고 그냥 구조체 추가, uproperty()는 구조체 포인터 지원 안함
	UPROPERTY()
	FAttackBaseC q_AttackBaseU;
	UPROPERTY()
	FAttackBaseC w_AttackBaseU;
	UPROPERTY()
	FAttackBaseC e_AttackBaseU;
	UPROPERTY()
	FAttackBaseC a_AttackBaseU;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float AggroMult = 1.0f;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	//TSubclassOf<class AC_Attack> QSkill;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	//TSubclassOf<class AC_Attack> WSkill;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	//TSubclassOf<class AC_Attack> ESkill;

	bool isDecal = false;
	bool isQSkill = false;
	bool isWSkill = false;
	bool isESkill = false;
	FVector mouselocation;
	class AC_TopDownController* tmpC;
	FHitResult HitT;
	 
	// 스킬 테스트
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AC_Skill> Skill_Q_Class;
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AC_Skill> Skill_W_Class;
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AC_Skill> Skill_E_Class;
	//
	//class AC_Skill* skill_Q;
	//class AC_Skill* skill_W;
	//class AC_Skill* skill_E;
	//
	//void UseSkill_Q();
	//void UseSkill_E();
	//void UseSkill_W();
	// 
	// 얘만 컴파일때문에 살려둠
    bool canInput;
	//
	//// 세팅하기
	//UFUNCTION()
	//void SetTopDownCharacter();
	//
	//bool tmpssss = false;

};
