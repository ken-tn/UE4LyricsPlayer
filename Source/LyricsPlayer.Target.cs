// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LyricsPlayerTarget : TargetRules
{
	public LyricsPlayerTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
        ExtraModuleNames.Add("LyricsPlayer");
	}
}
