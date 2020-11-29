// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class MyProject9 : ModuleRules
{
	public MyProject9(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "OnlineSubsystem", "OnlineSubsystemUtils" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		PrivateDependencyModuleNames.Add("OnlineSubsystem");
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//PrivateDependencyModuleNames.Add("OnlineSubsystemNull");
		//if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Linux))
		//{
		//	if (UEBuildConfiguration.bCompileSteamOSS == true)
		//	{
		//		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//	}
		//}

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		//PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
