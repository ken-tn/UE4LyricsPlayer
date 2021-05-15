// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LyricsBlueprintFunctionLibrary.h"
#include "Sound/AmbientSound.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LyricActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStringDelegate, const FString, Word);

UCLASS()
class LYRICSPLAYER_API ALyricActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALyricActor();

	int LineCounter = 0;
	int WordCounter = 0;
	
	UFUNCTION()
		void OnWordReached(const FString Word);

	UPROPERTY(BlueprintAssignable)
		FStringDelegate OnWordReachedDelegate;

	UPROPERTY(BlueprintReadWrite)
		FLyricFileStruct LyricStruct;

	UPROPERTY(EditAnywhere, Category = "Lyrics")
		FString Lyrics;

	UPROPERTY(EditAnywhere, Category = "Audio")
		AAmbientSound* AmbientSound;

	UFUNCTION()
		void FOnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, const float PlaybackPercent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
