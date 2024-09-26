// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptRaider : ModuleRules
{
	public CryptRaider(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] { "CryptRaider/Public" }
		);
		PrivateIncludePaths.AddRange(
			new string[] { "CryptRaider/Private" }
		);

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Paper2D",
			"FieldSystemEngine", "Slate", "SlateCore", "AIModule", "NavigationSystem"
		});
	}
}