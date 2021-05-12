// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LyricsBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLyricWord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Word;
};

USTRUCT(BlueprintType)
struct FLyricLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLyricWord> Words;
};

USTRUCT(BlueprintType)
struct FLyricTag
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Value;
};

USTRUCT(BlueprintType)
struct FLyricFileStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLyricTag> Tags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLyricLine> Lines;
};

/**
 * 
 */
UCLASS()
class LYRICSPLAYER_API ULyricsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION()
		static float LRCTimeToSeconds(FString Time);

	UFUNCTION()
		static FLyricLine FormatLyricLine(FString Line);

	UFUNCTION(BlueprintCallable)
		static void IsLyricHit(const USoundWave* PlayingSoundWave, const float PlaybackPercent, const FLyricFileStruct LyricStruct, UPARAM(ref) int& LineCounter, UPARAM(ref) int& WordCounter, bool& Hit, FString& WordString);

	UFUNCTION(BlueprintCallable, Category = "LyricsConverter")
		static void ParseLyrics(const FString ELRCFile, FLyricFileStruct &LyricStruct);

};
