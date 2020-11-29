// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyProject9Target : TargetRules
{
	public MyProject9Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//UEBuildConfiguration.bCompileSteamOSS = true;
		ExtraModuleNames.AddRange( new string[] { "MyProject9" } );
	}
}
