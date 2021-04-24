// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LyricsBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLyricWord {
	GENERATED_BODY()

	UPROPERTY()
		float Time;

	UPROPERTY()
		FString Word;
};

USTRUCT(BlueprintType)
struct FLyricLines {
	GENERATED_BODY()

	UPROPERTY()
		int32 LineNumber;

	UPROPERTY()
		TArray<FLyricWord> Words;
};

USTRUCT(BlueprintType)
struct FLyricTag {
	GENERATED_BODY()

	UPROPERTY()
		FString Tag;

	UPROPERTY()
		FString Value;
};

USTRUCT(BlueprintType)
struct FLyricFileStruct {
	GENERATED_BODY()

	UPROPERTY()
		TArray<FLyricTag> Tags;

	UPROPERTY()
		FLyricLines Lines;
};

/**
 * 
 */
UCLASS()
class LYRICSPLAYER_API ULyricsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION()
		FLyricLines FormatLyricLine(FString line);

	UFUNCTION(BlueprintCallable, Category = "LyricsConverter")
		static void ParseLyrics(const FString& ELRCFile);
};
