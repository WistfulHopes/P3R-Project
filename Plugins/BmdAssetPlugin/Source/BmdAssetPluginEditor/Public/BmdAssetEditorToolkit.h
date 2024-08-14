// (C)ATLUS. (C)SEGA. : 3
#pragma once

#include "CoreMinimal.h"
#include "BmdAsset.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Slate/Public/Framework/Docking/TabManager.h"
#include "Slate/Public/Widgets/Text/SRichTextBlock.h"
#include "Slate/Public/Widgets/Layout/SScrollBox.h"
#include "Modules/ModuleManager.h"
#include "BmdAssetStyle.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "UnrealEd/Public/EditorDirectories.h"
#include "Core/Public/Misc/FileHelper.h"

class FBmdAssetEditorToolkit : public FAssetEditorToolkit
{
public:
	// implement FAssetEditorToolkit
	void InitEditor(const TArray<UObject*>& InObjects);

	void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	FName GetToolkitFName() const override { return "BmdAssetEditor"; }
	FText GetBaseToolkitName() const override { return INVTEXT("Bmd Asset Editor"); }
	FString GetWorldCentricTabPrefix() const override { return "Bmd Asset"; }
	FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
private:
	UBmdAsset* Asset;

	BmdData CurrentBmdData;
	bool bCurrentBmdDataLoaded;
	TSharedPtr<SBox> DialogListBox;
private:
	void SetSyncFile();
	void UpdateAssetBySyncFile();
	TSharedRef<SWidget> CreateBmdDialogList();
	TSharedRef<SWidget> CreateSetFileSection();
	void LoadTargetBmd();
};