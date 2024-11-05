// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SerFps : ModuleRules
{
	public SerFps(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", 
			"AnimGraphRuntime", "Slate", "SlateCore", "UMG", "Niagara" });
        PublicIncludePaths.Add(ModuleDirectory);
        PrivateDependencyModuleNames.Add("OnlineSubsystem");
        PrivateDependencyModuleNames.Add("OnlineSubsystemSteam");

    }
}
