// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SomethingLikeChess : ModuleRules
{
	public SomethingLikeChess(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", /*"HeadMountedDisplay",*/ "AIModule", "UMG", "Slate", "SlateCore" });
	}
}
