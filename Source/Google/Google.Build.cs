// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Google : ModuleRules
{
    public Google(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {

            });


        PrivateIncludePaths.AddRange(
            new string[] {
            });


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            });


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "JSON",
                "GoogleSDK",
            });


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {

            });

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
        }
    }
}
