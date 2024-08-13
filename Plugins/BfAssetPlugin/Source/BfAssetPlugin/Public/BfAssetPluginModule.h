#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#if WITH_EDITORONLY_DATA

#include "BfAssetStyle.h"
#include "BfAssetActions.h"

class FBfAssetPluginEditorModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
private:
	TSharedPtr<FBfAssetTypeActions> AssetActions;
};

#endif