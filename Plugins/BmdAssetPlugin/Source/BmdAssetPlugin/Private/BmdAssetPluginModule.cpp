#include "BmdAssetPluginModule.h"

#if WITH_EDITORONLY_DATA

#define LOCTEXT_NAMESPACE "BmdAssetPluginEditor"

DEFINE_LOG_CATEGORY_STATIC(LogBmdAssetPlugin, Log, All);

void FBmdAssetPluginEditorModule::StartupModule()
{
	// Initialize BMD style
	FBmdAssetStyle::Initialize();
	FBmdAssetStyle::ReloadTextures();

	// Setup BMD asset type
	BmdAssetActions = MakeShared<FBmdAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(BmdAssetActions.ToSharedRef());

}

void FBmdAssetPluginEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools")) {
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(BmdAssetActions.ToSharedRef());
	}
}

IMPLEMENT_MODULE(FBmdAssetPluginEditorModule, BmdAssetPlugin);
#undef LOCTEXT_NAMESPACE
#else
IMPLEMENT_MODULE(FDefaultGameModuleImpl, BmdAssetPlugin);
#endif
