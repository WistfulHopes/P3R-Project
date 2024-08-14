using UnrealBuildTool;

public class BmdAssetPluginEditor : ModuleRules {
    public BmdAssetPluginEditor(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Warning;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "BmdAssetPlugin",
            "Core",
            "CoreUObject",
            "Engine",
        });
        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "AssetRegistry",
                    "AssetTools",
                    "DesktopPlatform",
                    "EditorStyle",
                    "InputCore",
                    "Projects",
                    "Slate",
                    "SlateCore",
                    "UnrealEd"
                }
            );
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Slate",
                    "SlateCore"
                }
            );
        }
    }
}
