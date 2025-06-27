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
	FVector CamPos = player->Camera->GetComponentLocation(); // 카메라 위치
	FVector CamForward = player->Camera->GetForwardVector(); // 카메라 앞 단위벡터
	FVector muzzlePos = SweepResult.Location; // 발사 위치 = 맞은 위치
	FVector tmpV = muzzlePos - CamPos; // 카메라에서 총구까지의 벡터
	float camToStartDistance = FVector::DotProduct(CamForward , tmpV); // 발사위치와 카메라의 깊이 구하기
	// 총구가 카메라 전방으로 얼마나 떨어져 있는지(깊이)를 구함

	FHitResult tmpHit;
	// 카메라 조준선 상의 총구 깊이 위치에 있는 점
	FVector start = CamPos + CamForward * camToStartDistance; // 발사 위치와 같은 깊이에서 시작
	// 총구와 Start 간의 거리
	//float startToMz = ( start - muzzlePos ).Length();
	float startToMz = FVector::Distance(start , muzzlePos);
	// 피타고라스의 정리로 표창이 날아갈 직선 거리 계산
	// 표창 비행 거리 = pyoDistance, 총구와 Start 간의 거리 = startToMz
	float pyoDistance = tmpBullet->totalDistance;
	float startToEndDistance = FMath::Sqrt(FMath::Square(pyoDistance) - FMath::Square(startToMz));
	// 조준선 상 최종 목표 지점 
	FVector end = CamPos + CamForward * ( startToEndDistance + camToStartDistance );

	FCollisionQueryParams tmpCP;
	tmpCP.AddIgnoredActor(player); // 자기 자신 제외하기, 3인칭이라 가끔 자기 자신 맞음
	bool btmpB = GetWorld()->LineTraceSingleByChannel(tmpHit , start , end , ECollisionChannel::ECC_Camera , tmpCP);
	if ( btmpB )
	{
		FVector direction = (tmpHit.Location - SweepResult.Location ).GetSafeNormal();
		//reflectBullet->FirePyoChang(direction);
		MulReflectPyo(tmpBullet->GetClass() , FTransform(FRotator(tmpBullet->GetActorRotation()) , muzzlePos , tmpBullet->GetActorScale()) , direction , 0);
		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: SkillE_Reflect_Hit__%s"), *GetActorNameOrLabel(), *tmpHit.GetActor()->GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
		
	}
	else
	{
		FVector direction = ( end - muzzlePos ).GetSafeNormal();
		//reflectBullet->FirePyoChang(direction);
		MulReflectPyo(tmpBullet->GetClass() , FTransform(FRotator(tmpBullet->GetActorRotation()) , muzzlePos , tmpBullet->GetActorScale()) , direction , 0);

		/*UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: SkillE_Reflect_NotHit"), *GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);*/
	}
	/*if ( reflectBullet->GetIsReplicated() )
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s: BulletRep"), *GetActorNameOrLabel())
			, true, true, FColor::MakeRandomColor(), 10.0f);
	}*/
	// 디버그용
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

