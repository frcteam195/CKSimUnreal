// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CKSimPlugin : ModuleRules
{
	public CKSimPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"..\\Source\\ThirdParty\\CKlibzmq\\include",
				"..\\Source\\ThirdParty\\CKSimProtoSpec\\CKSimProtoSpecLib",
				"..\\Source\\ThirdParty\\CKprotobuf\\src"
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CKlibzmq",
				"Projects",
				"CoreUObject",
				"Engine",	
				"CKprotobuf",
				"CKSimProtoSpec"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
