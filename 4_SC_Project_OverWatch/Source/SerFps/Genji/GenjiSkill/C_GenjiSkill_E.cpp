// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/GenjiSkill/C_GenjiSkill_E.h"
#include "Genji/C_CharacterGenji.h"
#include "Genji/C_PyoChang.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterBase/C_BaseWidget.h"


// 테스트 추후 삭제
//#include "NiagaraComponent.h"


// Sets default values
AC_GenjiSkill_E::AC_GenjiSkill_E()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_GenjiSkill_E::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GenjiSkill_E::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( useSkill )
	{
		ClientSetWidgetECoolTime(coolTime - tmpCoolTime + 1.0f);
		if ( !isCoolTime )
		{
			ClientSetWidgetEIcon(false);
			useSkill = false;
		}
	}
	if (!bESkillOn) return;

	tmpDuration += DeltaTime;
	if (tmpDuration >= duration)
	{
		tmpDuration = 0.0f;
		bESkillOn = false;
	}
	
}

void AC_GenjiSkill_E::OnHitBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || !bESkillOn ||  !player || OtherActor->Owner == player ||  OtherActor == player  || !player->HasAuthority()) return;

	// 총알이 아니면 리턴
	AC_PyoChang* tmpBullet = Cast<AC_PyoChang>(OtherActor);
	if (!tmpBullet) return;
	// 뒤쪽에서 맞았으면 리턴	
	if ( player )
	{
		
		FVector tmpLocation = ( SweepResult.Location - player->GetActorLocation() ).GetSafeNormal();
		float tmpDot = FVector::DotProduct(tmpLocation , player->GetActorForwardVector());
		
		if ( tmpDot <= 0.0f ) return;
	}
	// 맞은 위치에서 히트, 반사 이펙트 소환
	/*UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld() , SkillEffectN , 
		SweepResult.Location, player->GetActorRotation(),skillScale);*/
	MulSpawnEffect(SkillEffectN , SweepResult.Location , player->GetActorRotation() , skillScale);
	// 맞은 총알 그대로 소환
	/*FActorSpawnParameters actorParam;
	actorParam.Owner = player;
	AC_PyoChang* reflectBullet = GetWorld()->SpawnActor<AC_PyoChang>(tmpBullet->GetClass(), tmpBullet->GetActorTransform(), actorParam);*/
	//reflectBullet->SetActive(false);
	
	// 카메라와 발사위치까지의 거리 구하기
	FVector CamPos = player->Camera->GetComponentLocation();
	FVector AcPos = SweepResult.Location;
	FVector tmpV = AcPos - CamPos;
	float tmpDistance = ( FVector::DotProduct(tmpV , player->Camera->GetForwardVector()) );

	/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("Dot: %f") , tmpDistance)
		, true , true , FColor::MakeRandomColor() , 10.0f);*/

	/*UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld() , SkillEffectN , 
		SweepResult.Location, player->GetActorRotation(),skillScale);*/
	float tmpTotalDistance = tmpBullet->totalDistance;
	// 조준점으로 반사하기
	FHitResult tmpHit;
	FVector start = player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * tmpDistance;
	FVector end = player->Camera->GetComponentLocation() + player->Camera->GetForwardVector() * ( tmpTotalDistance + tmpDistance );
	//GetWorld()->LineTraceSingleByChannel(tmpHit, start, end, ECollisionChannel::ECC_Camera);
	//if (tmpHit.bBlockingHit)
	// 
	FCollisionQueryParams tmpCP;
	tmpCP.AddIgnoredActor(player);
	if ( GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera , tmpCP))
	{
		FVector direction = (tmpHit.Location - SweepResult.Location ).GetSafeNormal();
		//reflectBullet->FirePyoChang(direction);
		MulReflectPyo(tmpBullet->GetClass() , FTransform(FRotator(tmpBullet->GetActorRotation()) , SweepResult.Location , tmpBullet->GetActorScale()) , direction , tmpDistance);
		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: SkillE_Reflect_Hit__%s"), *GetActorNameOrLabel(), *tmpHit.GetActor()->GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
		
	}
	else
	{
		FVector direction = ( end - SweepResult.Location ).GetSafeNormal();
		//reflectBullet->FirePyoChang(direction);
		MulReflectPyo(tmpBullet->GetClass() , FTransform(FRotator(tmpBullet->GetActorRotation()) , SweepResult.Location, tmpBullet->GetActorScale()) , direction , tmpDistance);

		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: SkillE_Reflect_NotHit"), *GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
	}
	/*if ( reflectBullet->GetIsReplicated() )
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: BulletRep"), *GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);
	}*/
	
	switch ( hitCount %= 3 )
	{
	case 0:
		MulPlaySound(HitSound1 , SweepResult.Location);
		break;
	case 1:
		MulPlaySound(HitSound1 , SweepResult.Location);
		break;
	case 2:
		MulPlaySound(HitSound1 , SweepResult.Location);
		break;
	default:
		break;
	}
	hitCount++;

}

void AC_GenjiSkill_E::UseSkill()
{
	if (isCoolTime) return;
	isCoolTime = true;
	tmpCoolTime = 0.0f;
	bESkillOn = true;
	tmpDuration = 0.0f;
	MulPlayMontage(ESkillMotion);
	ClientSetWidgetEIcon(true);
	useSkill = true;
}

void AC_GenjiSkill_E::MulReflectPyo_Implementation(UClass* _Uclass , const FTransform& _Transform , const FVector& _direction , float _tmpDistance)
{
	FActorSpawnParameters actorParam;
	if ( player && player->HasAuthority() )
	{
		actorParam.Owner = player;
		/*UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s: Bullet") , *GetActorNameOrLabel())
			, true , true , FColor::MakeRandomColor() , 10.0f);*/
	}
	AC_PyoChang* reflectBullet = GetWorld()->SpawnActor<AC_PyoChang>(_Uclass , _Transform , actorParam);
	reflectBullet->FirePyoChang(_direction);
	
}

void AC_GenjiSkill_E::ClientSetWidgetECoolTime_Implementation(float _tmpCoolTime)
{
	player->mainWidget->SetIconCoolTimeTmp(SkillState::Skill_E , _tmpCoolTime);
}

void AC_GenjiSkill_E::ClientSetWidgetEIcon_Implementation(bool _isCoolTime)
{
	player->mainWidget->SetIconCoolTime(SkillState::Skill_E , _isCoolTime);
}

