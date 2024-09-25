// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CryptRaiderTarget : TargetRules
{
	public CryptRaiderTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		BuildEnvironment = TargetBuildEnvironment.Unique;
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.Add("CryptRaider");
	}
}
