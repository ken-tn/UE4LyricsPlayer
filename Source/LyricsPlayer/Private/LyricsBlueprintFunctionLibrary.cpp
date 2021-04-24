// Fill out your copyright notice in the Description page of Project Settings.


#include "LyricsBlueprintFunctionLibrary.h"

FLyricLines ULyricsBlueprintFunctionLibrary::FormatLyricLine(FString line)
{
	FRegexMatcher* TimeMatch = new FRegexMatcher(FRegexPattern("%<(.-)%>"), line);
	FRegexMatcher* WordMatch = new FRegexMatcher(FRegexPattern("%>(.-)%<"), line);

	return FLyricLines();
}

void ULyricsBlueprintFunctionLibrary::ParseLyrics(const FString& ELRCFile)
{
	FLyricFileStruct LyricStruct;
	TArray<FString> LineArray;
	ELRCFile.ParseIntoArray(LineArray, TEXT("\n"), false);
	const FRegexPattern TagPattern("\\[([a-z]+)\\:(.+)\\]");
	
	for (auto& Line : LineArray) {
		FRegexMatcher TagValueMatch(TagPattern, Line);

		while (TagValueMatch.FindNext()) {
			FLyricTag NewTag;
			NewTag.Tag = TagValueMatch.GetCaptureGroup(1);
			NewTag.Value = TagValueMatch.GetCaptureGroup(2);
			LyricStruct.Tags.Add(NewTag);
		}
	}
}
