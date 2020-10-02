// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class CKSimProtoSpec : ModuleRules
{
	public CKSimProtoSpec(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "CKSimProtoSpecLib", "Release", "CKSimProtoSpecLib.lib"));

        }
	}
}
