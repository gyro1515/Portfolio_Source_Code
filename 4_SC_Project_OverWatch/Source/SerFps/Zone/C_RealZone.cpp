// Fill out your copyright notice in the Description page of Project Settings.


#include "C_RealZone.h"
#include "Math/UnrealMathUtility.h"
#include "CharacterBase/C_BaseCharacter.h"
#include "Genji/C_CharacterGenji.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



AC_RealZone::AC_RealZone()
{
	RootSphere->OnComponentBeginOverlap.AddDynamic(this, &AC_RealZone::OnBeginOverlap);
	RootSphere->OnComponentEndOverlap.AddDynamic(this, &AC_RealZone::OnEndOverlap);
	zoneCount = 0;
	bIsStart = false;
	
}

void AC_RealZone::BeginPlay()
{
	Super::BeginPlay();
	bReplicates = true;
	SetReplicateMovement(true);

	SetActorScale3D(FVector(StartScale));
	OriginalT = GetActorTransform();
	SmallT = GetActorTransform();
	SetActive(false);
}

void AC_RealZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( !HasAuthority() ) return;
	if ( !bIsStart ) return;
	if ( !bRealStart )
	{
		tmpStartTime += DeltaTime;
		if ( tmpStartTime >= startTime )
		{
			bRealStart = true;
			tmpStartTime = 0.0f;
			SetActorHiddenInGame(false);
			SetActorEnableCollision(true);
			MulSetActive(true);
		}
		return;
	}
	
	for ( AC_BaseCharacter* tmpChar : characters )
	{
		if ( tmpChar->bDie ) continue;
		
		tmpChar->curHp -= damage * DeltaTime;
		AC_CharacterGenji* tmpGen = Cast<AC_CharacterGenji>(tmpChar);
		if ( tmpGen )
		{
			/*UKismetSystemLibrary::PrintString(GetWorld() ,
		FString::Printf(TEXT("%s: BlueZone") , *tmpGen->GetActorNameOrLabel())
		, true , true , FColor::MakeRandomColor() , 5.0f);*/
			if ( tmpGen->curHp <= 0.0f )
			{
				tmpGen->curHp = 0.0f;
				tmpGen->CharacterDie();
			}
			tmpGen->ClientSetCurHp(tmpGen->curHp , tmpGen->maxHp);
		}
	}

	FString DebugText = FString::Printf(TEXT("Timer: % f"), Timer);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, DebugText);
	}

	FString DebugText2 = FString::Printf(TEXT("Alpha: % f"), Alpha);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, DebugText2);
	}

	Timer += DeltaTime;

	if (Timer > StableTime && !Indicator)
	{
		SmallT = GenerateSmallTransform(OriginalT);
		Indicator = GetWorld()->SpawnActor<AC_BlueZone>(IndicatorClass, SmallT);
	}
	else if (Timer > StableTime + ReadyTime)
	{
		Alpha += DeltaTime / UnStableTime;

		if (Alpha > 1.0f)
		{
			OriginalT = SmallT;
			Timer = 0.0f;
			Alpha = 0.0f;
			Indicator->Destroy();
			Indicator = nullptr;
		}
		else
		{
			FRotator NewRotator;
			FVector NewLocation = FMath::Lerp(OriginalT.GetLocation(), SmallT.GetLocation(), Alpha);
			FVector NewScale = FMath::Lerp(OriginalT.GetScale3D(), SmallT.GetScale3D(), Alpha);
			//SetActorTransform(FTransform(NewRotator,NewLocation,NewScale));
			MulSetActorTransform(FTransform(NewRotator,NewLocation,NewScale), true);
		}
	}
}

FTransform AC_RealZone::GenerateSmallTransform(FTransform original)
{
	FVector SmallLocation;
	FRotator SmallRotation;
	FVector SmallScale;

	SmallScale = FVector(original.GetScale3D() * SmallerPercent);

	float randomR = FMath::FRandRange(0.0f, (original.GetScale3D().X-SmallScale.X) * 100.0f);
	
	//float randomT = FMath::FRandRange(0.0f, 3.14f);
	float randomT = FMath::FRandRange(0.0f, 360.0f);

	//SmallLocation = original.GetLocation() + FVector(randomR * cos(randomT), randomR * sin(randomT), 0.0f);
	SmallLocation = original.GetLocation() + FVector(randomR * FMath::Cos(FMath::DegreesToRadians(randomT)) , randomR * FMath::Sin(FMath::DegreesToRadians(randomT)) , 0.0f);

	UKismetSystemLibrary::PrintString(GetWorld() , FString::Printf(TEXT("%s_Radian: %f") , *GetActorNameOrLabel(), randomT)
			, true , true , FColor::MakeRandomColor() , 10.0f);

	return FTransform(SmallRotation, SmallLocation, SmallScale);
}

void AC_RealZone::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	if ( OtherActor == this ) return;
	AC_BaseCharacter* tmpChar = Cast<AC_BaseCharacter>(OtherActor);
	if ( tmpChar )
	{
		int tmpIndex = characters.Find(tmpChar);
		if ( tmpIndex == -1 ) return;
		AC_CharacterGenji* tmpGen = Cast<AC_CharacterGenji>(tmpChar);
		if ( tmpGen )
		{
			tmpGen->ClientRemoveZoneWidget();
		}
		characters.RemoveAt(tmpIndex);
	}

}

void AC_RealZone::OnEndOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex)
{
	if ( OtherActor == this ) return;
	AC_BaseCharacter* tmpChar = Cast<AC_BaseCharacter>(OtherActor);
	if ( tmpChar && !tmpChar->bDie )
	{
		int tmpIndex = characters.Find(tmpChar);
		if ( tmpIndex != -1 ) return;
		characters.Add(tmpChar);
		AC_CharacterGenji* tmpGen = Cast<AC_CharacterGenji>(tmpChar);
		if ( tmpGen && !tmpGen->bDie )
		{
			//tmpGen->zoneWidget->AddToViewport(0);
			tmpGen->ClientAddZoneWidget();
		}
	}
}

void AC_RealZone::SetActive(bool _IsStart)
{
	MulSetActive(_IsStart);
}

void AC_RealZone::SerSetActive_Implementation(bool _IsStart)
{
	MulSetActive(_IsStart);
}

void AC_RealZone::MulSetActive_Implementation(bool _IsStart)
{
	if ( _IsStart )
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		//SetActorTickEnabled(true);
		bIsStart = _IsStart;
		
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		//SetActorTickEnabled(false);
		bIsStart = _IsStart;
	}
	
}

void AC_RealZone::MulSetActorTransform_Implementation(const FTransform& NewTransform , bool bSweep)
{
	SetActorTransform(NewTransform , bSweep);
}
