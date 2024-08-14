// (C)ATLUS. (C)SEGA. :3
#pragma once

#include "CoreMinimal.h"
#include "BmdAsset.h"
#include "SlateCore/Public/Styling/SlateIconFinder.h"
#include "SlateCore/Public/Widgets/Images/SImage.h"
#include "AssetTypeActions_Base.h"
#include "BmdAssetEditorToolkit.h"

/**
 * 
 */
class FBmdAssetTypeActions : public FAssetTypeActions_Base
{
public:
	// implemented from IAssetTypeActions
	UClass* GetSupportedClass() const override;
	FText GetName() const override;
	FColor GetTypeColor() const override;
	uint32 GetCategories() override;
	void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor) override;
};