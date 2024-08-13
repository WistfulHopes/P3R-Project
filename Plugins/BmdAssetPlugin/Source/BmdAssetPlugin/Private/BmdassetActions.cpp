// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "BmdassetActions.h"

UClass* FBmdAssetTypeActions::GetSupportedClass() const {
	return UBmdAsset::StaticClass();
}

FText FBmdAssetTypeActions::GetName() const {
	return FText::FromString("BMD (Atlus Message Script)");
}

FColor FBmdAssetTypeActions::GetTypeColor() const {
	return FColor(0xff, 0x87, 0xe7, 0xff);
}

uint32 FBmdAssetTypeActions::GetCategories() {
	return EAssetTypeCategories::Misc;
}

void FBmdAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	MakeShared<FBmdAssetEditorToolkit>()->InitEditor(InObjects);
}

#endif