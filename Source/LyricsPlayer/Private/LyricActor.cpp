// Fill out your copyright notice in the Description page of Project Settings.

#include "LyricActor.h"
#include "LyricsBlueprintFunctionLibrary.h"
#include "Components/AudioComponent.h"

// Sets default values
ALyricActor::ALyricActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALyricActor::BeginPlay()
{
	Super::BeginPlay();

	OnWordReachedDelegate.AddDynamic(this, &ALyricActor::OnWordReached);
}

// Called every frame
void ALyricActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALyricActor::Play()
{
	ULyricsBlueprintFunctionLibrary::ParseLyrics(Lyrics, LyricStruct);

	if (IsValid(AmbientSound))
	{
		bCanPlay = true;
		UAudioComponent* AudioComponent = AmbientSound->GetAudioComponent();
		AudioComponent->OnAudioPlaybackPercent.Clear();
		AudioComponent->OnAudioPlaybackPercent.AddDynamic(this, &ALyricActor::FOnAudioPlaybackPercent);
		AudioComponent->Play();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LYRICS ACTOR HAS INVALID SETTINGS"));
	}
}

// Bound to OnAudioPlaybackPercent
void ALyricActor::FOnAudioPlaybackPercent(const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
	// We've gone past the end of a song, reset if we start another one
	if (LyricStruct.Lines.Num() - 1 < LineCounter)
	{
		LineCounter = 0;
		bCanPlay = false;

		return;
	}
	else if (bCanPlay)
	{
		TArray<FLyricWord> Line = LyricStruct.Lines[LineCounter].Words;

		// We've reached the final word in a line
		if (Line.Num() - 1 < WordCounter)
		{
			WordCounter = 0;
			++LineCounter;

			return;
		}
		else
		{
			// Play a word
			float CurrentTime = PlayingSoundWave->Duration * PlaybackPercent;
			FLyricWord CurrentWord = Line[WordCounter];

			if (CurrentTime > CurrentWord.Time)
			{
				++WordCounter;
				OnWordReachedDelegate.Broadcast(CurrentWord.Word);
			}

			return;
		}
	}
}

// Called every time a word is reached
void ALyricActor::OnWordReached(const FString Word)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Word);
}
