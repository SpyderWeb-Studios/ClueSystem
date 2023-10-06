using UnrealBuildTool;

public class TamperSystemEditor : ModuleRules
{
    public TamperSystemEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UMG",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "AssetTools",
                "ToolMenus",
                "BlueprintGraph",
                "KismetCompiler"
       

            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", "TamperSystem"
            }
        );
    }
}