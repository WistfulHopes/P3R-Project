#include "BfAssetPluginModule.h"

#if WITH_EDITORONLY_DATA

void FBfAssetPluginEditorModule::StartupModule()
{
	FBfAssetStyle::Initialize();
	FBfAssetStyle::ReloadTextures();

	// Setup BMD asset type
	AssetActions = MakeShared<FBfAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AssetActions.ToSharedRef());

}

void FBfAssetPluginEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools")) {
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AssetActions.ToSharedRef());
	}
}

IMPLEMENT_MODULE(FBfAssetPluginEditorModule, BfAssetPlugin);
#else
IMPLEMENT_MODULE(FDefaultGameModuleImpl, BfAssetPlugin);
#endif
