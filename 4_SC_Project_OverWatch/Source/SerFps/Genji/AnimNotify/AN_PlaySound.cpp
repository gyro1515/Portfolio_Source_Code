// Fill out your copyright notice in the Description page of Project Settings.


#include "Genji/AnimNotify/AN_PlaySound.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundWaveProcedural.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/AudioComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AN_PlaySound)

#if WITH_EDITOR
#include "Logging/MessageLog.h"
#include "Misc/UObjectToken.h"
#endif

UAN_PlaySound::UAN_PlaySound() : Super()
{
	VolumeMultiplier = 1.f;
	PitchMultiplier = 1.f;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(196 , 142 , 255 , 255);
	bPreviewIgnoreAttenuation = false;
#endif // WITH_EDITORONLY_DATA
}



void UAN_PlaySound::Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation)
{
}

void UAN_PlaySound::Notify(USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference)
{
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
		Notify(MeshComp , Animation);
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
		// Don't call super to avoid call back in to blueprints
		if ( Sound && MeshComp )
		{
			if ( !Sound->IsOneShot() )
			{
				UE_LOG(LogAudio , Warning , TEXT("PlaySound notify: Anim %s tried to play a sound asset which is not a one-shot: '%s'. Spawning suppressed.") , *GetNameSafe(Animation) , *GetNameSafe(Sound));
				return;
			}

#if WITH_EDITORONLY_DATA
			UWorld* World = MeshComp->GetWorld();
			if ( bPreviewIgnoreAttenuation && World && World->WorldType == EWorldType::EditorPreview )
			{
				UGameplayStatics::PlaySound2D(World , Sound , VolumeMultiplier , PitchMultiplier);
			}
			else
#endif
			{
				if ( bFollow )
				{
					UGameplayStatics::SpawnSoundAttached(Sound , MeshComp , AttachName , FVector(ForceInit) , EAttachLocation::SnapToTarget , false , VolumeMultiplier , PitchMultiplier, 0.0f, Attenuation);
				}
				else
				{
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld() , Sound , MeshComp->GetComponentLocation() , VolumeMultiplier , PitchMultiplier, 0.0f);
				}
			}
		}
}

FString UAN_PlaySound::GetNotifyName_Implementation() const
{
	if ( Sound )
	{
		return Sound->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
}

#if WITH_EDITOR
void UAN_PlaySound::ValidateAssociatedAssets()
{
	static const FName NAME_AssetCheck("AssetCheck");

	if ( Sound != nullptr && !Sound->IsOneShot() )
	{
		UObject* ContainingAsset = GetContainingAsset();

		FMessageLog AssetCheckLog(NAME_AssetCheck);

		const FText MessageLooping = FText::Format(
			NSLOCTEXT("AnimNotify" , "Sound_ShouldNotLoop" , "Sound {0} used in anim notify for asset {1} is set to looping, but the slot is a one-shot (it won't be played to avoid leaking an instance per notify).") ,
			FText::AsCultureInvariant(Sound->GetPathName()) ,
			FText::AsCultureInvariant(ContainingAsset->GetPathName()));
		AssetCheckLog.Warning()
			->AddToken(FUObjectToken::Create(ContainingAsset))
			->AddToken(FTextToken::Create(MessageLooping));

		if ( GIsEditor )
		{
			AssetCheckLog.Notify(MessageLooping , EMessageSeverity::Warning , /*bForce=*/ true);
		}
	}
}
#endif
