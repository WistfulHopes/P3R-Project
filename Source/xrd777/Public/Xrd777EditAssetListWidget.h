// (C)ATLUS. (C)SEGA.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

struct FXrd777EditAssetListEntry {
public:
	FString Path;
private:
	bool CreateAsset;
	bool AlreadyExists;
public:
	FXrd777EditAssetListEntry(const FString& InPath)
		: Path(InPath)
		, CreateAsset(true)
		, AlreadyExists(false)
	{}

	FXrd777EditAssetListEntry(const FString& InPath, bool bAlreadyExists)
		: Path(InPath)
		, AlreadyExists(bAlreadyExists)
	{
		CreateAsset = bAlreadyExists ? false : true;
	}
//private:
	void UpdateCreateAssetToggle() {
		// TODO: Check if file was created during this time.
		if (!AlreadyExists) {
			CreateAsset = !CreateAsset;
		}
	}
	bool GetCreateAsset() const {
		return CreateAsset;
	}
	void SetCreateAsset(bool bNewBool) {
		CreateAsset = bNewBool;
	}
	bool GetAlreadyExists() const {
		return AlreadyExists;
	}
};

DECLARE_DELEGATE_OneParam(FOnCreateAssets, FXrd777EditAssetListEntry&)


class SXrd777EditAssetListWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SXrd777EditAssetListWidget) 
		: _InList(nullptr)
		, _InitToggleMode(true)
		{}
		SLATE_ARGUMENT(TArray<TSharedRef<FXrd777EditAssetListEntry>>*, InList)
		SLATE_ARGUMENT(bool, InitToggleMode)
		SLATE_EVENT(FOnCreateAssets, CreateAsset)
	SLATE_END_ARGS()

	void Construct(const FArguments& In);
private:
	TArray<TSharedRef<FXrd777EditAssetListEntry>>* List;
	TSharedPtr<SListView<TSharedRef<FXrd777EditAssetListEntry>>> ListWidget;

	FOnCreateAssets CreateAsset;

	bool bToggleMode;

	TSharedRef<ITableRow> MakeModelListItemWidget(TSharedRef<FXrd777EditAssetListEntry> Item, const TSharedRef<STableViewBase>& InOwnerTable);
public:
	void UpdateAssetList(FString& InGamePath, FString& InPath, FString& InWildcard, IAssetRegistry& InAssetRegistry);
};
