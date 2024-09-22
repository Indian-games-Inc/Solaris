// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CryptRaiderEditorTarget : TargetRules
{
	public CryptRaiderEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		BuildEnvironment = TargetBuildEnvironment.Unique;
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.Add("CryptRaider");
	}
}
