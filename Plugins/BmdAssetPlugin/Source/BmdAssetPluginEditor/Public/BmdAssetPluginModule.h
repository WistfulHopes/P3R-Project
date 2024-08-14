#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "BmdassetActions.h"
#include "Styling/SlateStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "UnrealEd/Public/ClassIconFinder.h"
#include "BmdAssetStyle.h"
#include "BmdAssetSettings.h"
#include "Settings/Public/ISettingsModule.h"
#include "AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/Public/AssetRegistry/IAssetRegistry.h"

class FBmdAssetPluginEditorModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
private:
	TSharedPtr<FBmdAssetTypeActions> BmdAssetActions;
};